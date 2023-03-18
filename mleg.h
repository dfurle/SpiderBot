#ifndef MLEG_H
#define MLEG_H
#include "globals.h"
#include "mservo.h"

#define INN_L 35.
#define MID_L 60.
#define OUT_L 80.
#define MID_L2 MID_L*MID_L
#define OUT_L2 OUT_L*OUT_L

class MLeg{
public:
  MServo i, m, o;

  int debug_level = 0;

  MLeg(SIDE side, LEG leg):
  i(side, leg, PART::INNER),
  m(side, leg, PART::MIDDLE),
  o(side, leg, PART::OUTER)
  {
    
  };

  bool debug(int min, int max = 1e3){
    return min <= debug_level && debug_level <= max;
  }
  // TODO: figure out way to add max value too
  bool debug(int min, char* str, float val = -1){
    bool ret = debug_level >= min;
    if(ret && strlen(str) != 0 && val == -1){
      Serial.println(str);
    } else if(ret && strlen(str) != 0){
      Serial.print(str);
      Serial.println(val);
    }
    return ret;
  }

  void set_debug(int new_debug_level){
    debug_level = new_debug_level;
    i.set_debug(debug_level);
    m.set_debug(debug_level);
    o.set_debug(debug_level);
  }


  // https://www.desmos.com/calculator/pxnzvg15nf
  // idk if link will be dead after a while or not...
  // void calcAngles(float theta, float r, float height, float& innerA, float& middleA, float& outerA){
  void calcAngles(float theta, float r, float height){
    r = r - INN_L;
    float r2 = r*r;
    // this is the height from middle servo to base (in this case lowest point of my leg)
    height += 38; // TODO: define somewhere;
    float height2 = height*height;
    float innerA = theta;
    float middleA = RAD_TO_DEG*(M_PI-atan(r/height)-acos((MID_L2+r2+height2-OUT_L2)/(2*MID_L*sqrt(r2+height2))));
    float outerA  = RAD_TO_DEG*(M_PI-acos((MID_L2+OUT_L2-r2-height2)/(2*MID_L*OUT_L)));

    // TODO: Make this prettier
    if(debug(-1,-1)){
      Serial.println("Calculated Pt: ");
      int mx = MID_L * sin(middleA*DEG_TO_RAD);
      int my = MID_L * cos(middleA*DEG_TO_RAD);

      int ox = mx + OUT_L * sin(DEG_TO_RAD*(180-middleA-outerA));
      int oy = my - OUT_L * cos(DEG_TO_RAD*(180-middleA-outerA));

      int exp_x = r;
      int exp_y = height;

      Serial.print("x: ");
      Serial.print(ox);
      Serial.print(" == ");
      Serial.print(exp_x);
      Serial.println();

      Serial.print("y: ");
      Serial.print(oy);
      Serial.print(" == ");
      Serial.print(exp_y);
      Serial.println();
      Serial.println();
    }

    set_angles(innerA, middleA, outerA);
  }

  void set_catesian(float x, float y, float height){
    float r = sqrt(x*x + y*y);
    float theta = atan2(y,x) * RAD_TO_DEG;

    debug(5, " catesian      r = ", r);
    debug(5, " cartesian theta = ", theta);
    
    // Could just set inside calcAngles so can reduce to 1 line
    // float innerA, middleA, outerA;
    // calcAngles(theta, r, height, innerA, middleA, outerA);
    // set_angles(innerA, middleA, outerA);

    calcAngles(theta, r, height);
  }

  void test_set_r(float r, float height){

    if(debug(3)){
      Serial.print("Angles: r=");
      Serial.println(r);
    }

    // Could just set inside calcAngles so can reduce to 1 line
    // float innerA, middleA, outerA;
    // calcAngles(0, r, height, innerA, middleA, outerA);
    // set_angles(innerA, middleA, outerA);

    calcAngles(0, r, height);
  }

  void set_angles(float innerA, float middleA, float outerA){
    if(debug(2))
      Serial.println(" Inner");
    i.set(innerA);

    if(debug(2))
      Serial.println(" Middle");
    m.set(middleA);

    if(debug(2))
      Serial.println(" Outer");
    o.set(outerA);
  }
};


#endif