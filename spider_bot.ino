#include <Servo.h>
#include <Adafruit_PWMServoDriver.h>

#define MAX 460
#define MIN 93

#define LMAX 460
#define LMIN 80


#define SPEED 10 // degrees per 10 milliseconds

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

int getID(int LEG, int PART){
  return LEG*4 + PART;
}

enum ID{
  FL = 0,
  FR = 1,
  RR = 2,
  RL = 3,
  INNER = 0,
  MIDDLE = 1,
  OUTER = 2
};

class SServo{
public:
  int id;
  int minPulse;
  int maxPulse;
  double angle;
  double prevAngle;
  SServo(){
    this->id = -1;
    this->minPulse = 0;
    this->maxPulse = 0;
    angle = 0;
    prevAngle = 0;
  };
  SServo(int id, int minPulse, int maxPulse){
    this->id = id;
    this->minPulse = minPulse;
    this->maxPulse = maxPulse;
    angle = 0;
    prevAngle = 0;
  };
  void init(int id, int minPulse, int maxPulse){
    this->id = id;
    this->minPulse = minPulse;
    this->maxPulse = maxPulse;
    angle = 0;
    prevAngle = 0;
  }
  void set(int angle){
    if(this->id%4 == ID::INNER){
      angle = min(angle,135);
      if(this->id/4 == ID::FL || this->id/4 == ID::RR){
        angle = 180 - angle;
      }
    }
    if(this->id%4 == ID::MIDDLE){
      angle = min(angle,125);
      if(this->id/4 == ID::FL || this->id/4 == ID::RR){
        angle = 180 - angle;
      }
    }
    if(this->id%4 == ID::OUTER){
      // angle = max(angle,5);
      angle = min(angle,135);
      if(this->id == getID(ID::FL,ID::OUTER)){
        angle = 0.00122782*angle*angle+0.653217*angle-0.454094;
      } else if(this->id == getID(ID::RR,ID::OUTER)){
        angle = angle - 5;
      }
      if(this->id/4 == ID::FR || this->id/4 == ID::RL){ // DIFFERENT!!
        angle = 180 - angle;
      }
    }
    int val = map(angle,0,180,minPulse,maxPulse);

    this->angle = angle;
    if(this->id == 0) // since one connection is shifted
      pwm.setPWM(3, 0, val);
    else
      pwm.setPWM(id, 0, val);
  }


  void moveSpeed(int angle, double speed){
    double angleDiff = angle - this->angle;
    this->speed = speed * (angleDiff/abs(angleDiff));
    this->maxTime = abs(angleDiff / speed); // number of 10 milliseconds intervals
    this->time = 0;
    this->prevAngle = this->angle;
    this->done = false;
  }

  void waitUntilFinish(){
    while(!this->done){
      update();
      delay(10);
    }
  }

  int time;
  int maxTime;
  double speed;
  bool done;

  void update(){
    if(!this->done){
      set(prevAngle+speed);
      prevAngle = prevAngle + speed;
      this->time++;
      Serial.println(prevAngle);
      Serial.println(this->angle);
      Serial.println("--------");
      if(this->time >= this->maxTime){
        this->done = true;
      }
    }
  }

};



#define INN_L 35
#define MID_L 62
#define MID_L2 3844
#define OUT_L 85
#define OUT_L2 7225
#define TODEG 57.2957795131

#define MINHEIGHT 45

#define MINR 10
#define MAXR (INN_L+MID_L+OUT_L)



class Leg{
public:
  SServo inner;
  SServo middle;
  SServo outer;
  ID leg;
  double xPos;
  double yPos;
  double height;
  double height2;



  Leg(){}

  Leg(ID leg):
  inner(getID(leg,INNER),LMIN,LMAX),
  middle(getID(leg,MIDDLE),LMIN,LMAX),
  outer(getID(leg,OUTER),LMIN,LMAX)
  {
    this->leg = leg;
  }

  void init(ID leg, double height = MINHEIGHT){
    xPos = 0;
    yPos = 0;
    this->leg = leg;
    this->height = height;
    this->height2 = height*height;
    inner.init(getID(leg,INNER),LMIN,LMAX);
    middle.init(getID(leg,MIDDLE),LMIN,LMAX);
    outer.init(getID(leg,OUTER),LMIN,LMAX);
  }

  void setHeight(double height){
    this->height = height;
    this->height2 = height*height;
    double r = sqrt(xPos*xPos+yPos*yPos);
    double theta = atan2(yPos,xPos) * TODEG;
    setPolar(theta,r);
  }

  void setTheta(double theta){
    double r = sqrt(xPos*xPos+yPos*yPos);
    setPolar(theta,r);
  }
  void moveTheta(double thetaA){
    double r = sqrt(xPos*xPos+yPos*yPos);
    double theta = atan2(yPos,xPos) * TODEG;
    theta += thetaA;
    setPolar(theta,r);
  }

  void move(double x, double y, double speed = 0){
    xPos += x;
    yPos += y;
    double r = sqrt(xPos*xPos+yPos*yPos);
    double theta = atan2(yPos,xPos) * TODEG;
    setPolar(theta,r,speed);
  }

  void set(double x, double y, double speed = 0){
    xPos = x;
    yPos = y;
    double r = sqrt(xPos*xPos+yPos*yPos);
    double theta = atan2(yPos,xPos) * TODEG;
    setPolarRaise(theta,r,speed);
  }


  void calcAngles(double theta, double r, double& innerA, double& middleA, double& outerA){
    r = r - INN_L;
    double r2 = r*r;
    innerA = theta + 45;
    middleA = TODEG*(M_PI-atan(r/height)-acos((MID_L2+r2+height2-OUT_L2)/(2*MID_L*sqrt(r2+height2))));
    outerA  = TODEG*(M_PI-acos((MID_L2+OUT_L2-r2-height2)/(2*MID_L*OUT_L)));
  }

  void waitLegFinish(){
    while(!inner.done || !middle.done || !outer.done){
      inner.update();
      middle.update();
      outer.update();
      delay(10);
    }
  }

  void setPolarRaise(double theta, double r, double speed=0){
    if(theta < 0 || theta > 90){
      return;
    } else if(r < INN_L){
      return;
    }
    double innerA, middleA, outerA;
    calcAngles(theta, r, innerA, middleA, outerA);

    if(speed == 0){
      middle.set(45);
      delay(75);
      inner.set(innerA);
      delay(40);
      middle.set(middleA);
      outer.set(outerA);
    } else {
      middle.set(45);
      delay(500);
      inner.moveSpeed(innerA,1);
      inner.waitUntilFinish();
      middle.moveSpeed(middleA,1);
      outer.moveSpeed(outerA,1);
      // waitLegFinish();
    }
  }


  void setPolar(double theta, double r, double speed = 0){
    if(theta < 0 || theta > 90){
      return;
    } else if(r < INN_L){
      return;
    }
    double innerA, middleA, outerA;
    calcAngles(theta, r, innerA, middleA, outerA);

    if(speed == 0){
      inner.set(innerA);
      middle.set(middleA);
      outer.set(outerA);
    } else {
      inner.moveSpeed(innerA,1);
      middle.moveSpeed(middleA,1);
      outer.moveSpeed(outerA,1);
      // waitLegFinish();
    }
  }
};

class Spider{
public:
  Leg leg[4];
  double height;

  int msx;
  double ymin, ymid, ymax;

  Spider(){
    height = 45;
    leg[ID::FL].init(ID::FL);
    leg[ID::FR].init(ID::FR);
    leg[ID::RL].init(ID::RL);
    leg[ID::RR].init(ID::RR);
    recalculate();
  }

  void mirror(double x, double y){
    for(int i = 0; i < 4; i++){
      leg[i].set(x,y);
    }
  }


  void waitAllFinish(){
    int flag = 0;
    for(int i = 0; i < 4; i++){
      if(leg[i].inner.done && leg[i].middle.done && leg[i].outer.done){
        flag++;
      }
      leg[i].inner.update();
      leg[i].middle.update();
      leg[i].outer.update();
      delay(10);
      if(flag == 4){
        return;
      }
      flag = 0;
    }
  }

  void setHeight(double height){
    this->height = height;
    for(int i = 0; i < 4; i++){
      leg[i].setHeight(height);
    }
    recalculate(this->msx);
  }

  void recalculate(int msx = 85){
    this->msx = msx;
    double rmax = sqrt((MID_L+OUT_L)*(MID_L+OUT_L)-this->height*this->height) + INN_L;
    double ymax_true = sqrt(rmax*rmax - msx*msx);

    this->ymax = int(ymax_true/10) * 10 - 10;
    this->ymid = ymax/2;
    this->ymin = 0;
  }

  void initMove(){
    leg[ID::FR].set(msx,ymin);
    leg[ID::FL].set(msx,ymid);
    leg[ID::RL].set(msx,ymid);
    leg[ID::RR].set(msx,ymin);
  }

  void stepForward(int msx = 85, int sleep = 300){
    if(msx != this->msx){
      recalculate(msx);
    }
    leg[ID::FR].set(msx,ymax);
    delay(sleep);
    leg[ID::FL].move(0,-ymid);
    leg[ID::FR].move(0,-ymid);
    leg[ID::RL].move(0, ymid);
    leg[ID::RR].move(0, ymid);
    // waitAllFinish();
    
    delay(sleep);
    leg[ID::RL].set(msx,ymin);
    delay(sleep);
    leg[ID::FL].set(msx,ymax);
    delay(sleep);
    leg[ID::FL].move(0,-ymid);
    leg[ID::FR].move(0,-ymid);
    leg[ID::RL].move(0, ymid);
    leg[ID::RR].move(0, ymid);
    // waitAllFinish();
    delay(sleep);
    leg[ID::RR].set(msx,ymin);
    delay(sleep);
  }

  void stepBackward(int msx = 85, int sleep = 300){
    if(msx != this->msx){
      recalculate(msx);
    }
    leg[ID::RR].set(msx,ymax);
    delay(sleep);
    leg[ID::FL].move(0, ymid);
    leg[ID::FR].move(0, ymid);
    leg[ID::RL].move(0,-ymid);
    leg[ID::RR].move(0,-ymid);
    delay(sleep);
    leg[ID::FL].set(msx,ymin);
    delay(sleep);
    leg[ID::RL].set(msx,ymax);
    delay(sleep);
    leg[ID::FL].move(0, ymid);
    leg[ID::FR].move(0, ymid);
    leg[ID::RL].move(0,-ymid);
    leg[ID::RR].move(0,-ymid);
    delay(sleep);
    leg[ID::FR].set(msx,ymin);
    delay(sleep);
  }

  void twist(int angle){
    leg[ID::FR].moveTheta(angle);
    leg[ID::FL].moveTheta(-angle);
    leg[ID::RL].moveTheta(angle);
    leg[ID::RR].moveTheta(-angle);
  }
};

Spider spider;

void setup() {
  Serial.begin(9600);

  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(50);

  spider.initMove();
  delay(1000);
  spider.setHeight(MINHEIGHT+40);
  delay(1000);


  spider.stepForward();
  spider.stepForward();
  spider.stepForward();
  spider.stepForward();


  spider.leg[ID::FR].middle.set(0);
  spider.leg[ID::FR].outer.set(0);
  spider.leg[ID::FR].inner.set(90);
  delay(1000);
  spider.leg[ID::FR].outer.set(45);
  delay(400);
  spider.leg[ID::FR].outer.set(0);
  delay(400);
  spider.leg[ID::FR].outer.set(45);
  delay(1000);

  spider.initMove();
  // spider.setHeight(MINHEIGHT+40);

  // spider.twist(30);

  // spider.mirror(80,80);

  // spider.leg[ID::RL].setHeight(MINHEIGHT+10);
  // spider.leg[ID::RR].setHeight(MINHEIGHT+10);
  // spider.leg[ID::FL].setHeight(MINHEIGHT+50);
  // spider.leg[ID::FR].setHeight(MINHEIGHT+50);

}




void loop(){
  // spider.stepForward();
}
