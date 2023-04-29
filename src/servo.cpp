#include "servo.h"
#include "global.h"
#include "debuggable.h"

extern Global g;

Servo::Servo(int bits){
  this->bits = bits;
  this->part = bits & PART::ALL;
  int _leg = g.findSetBit(((bits & LEG::ALL)>>LEG::MIN)) - 1;
  int _part = g.findSetBit((part>>PART::MIN)) - 1;
  printf("leg: %d\n",_leg);
  this->id = (int) ((_leg)*4 + _part);
  printf("id1: %d\n",this->id);
  if(_leg >= 3){
    this->id = (int) (16 + (_leg-3)*4 + _part);
    // this->id += 4*4; // if right side, switch to other PWM board;
    printf("id2: %d\n",this->id);
  }
  printf("\n");
  this->currentAngle = 0; // TODO: figure out best defaulting angle
  this->a = currentAngle;
  this->ad = currentAngle;
  // set(currentAngle);
}

void Servo::setLimits(int low, int high){
  limits[0] = low;
  limits[1] = high;
}

float Servo::convert_angle(float angle){
  float hLim0 = limits[0];
  float hLim1 = limits[1];
  float diff = hLim1 - hLim0;
  if(part == PART::OUTER){
    angle += 15;
  }
  switch(part){
  case PART::INNER:
    debug(3, "  Original : ", angle);
    angle = g.constrain(angle, -diff/2, diff/2);
    debug(3, "  Constrain: ", angle);
    angle = g.map(angle, -diff/2, diff/2, hLim0, hLim1);
    debug(3, "  Map      : ", angle);
    return angle;
  case PART::MIDDLE:
    debug(3, "  Original : ", angle);
    angle = g.constrain(angle, 0.f, diff);
    debug(3, "  Constrain: ", angle);
    angle = g.map(angle, 0.f, diff, hLim1, hLim0); // THIS ONE IS FLIPPED!
    debug(3, "  Map      : ", angle);
    return angle;
  case PART::OUTER:
    debug(3, "  Original : ", angle);
    angle *= 80./90;
    debug(3, "  Adjusted : ", angle);
    angle = g.constrain(angle, 0.f, diff);
    debug(3, "  Constrain: ", angle);
    angle = g.map(angle, 0.f, diff, hLim0, hLim1);
    debug(3, "  Map      : ", angle);
    return angle;
  default:
    return angle;
  }
}

void Servo::directDrive(float angle){
  this->ad = angle;
  this->currentAngle = angle;
  this->a = angle;
  float val = g.map(angle, 0.f, 180.f, LMIN, LMAX);
  if(id < 16){
    g.left.set_pwm_ms(id,val);
  } else {
    g.right.set_pwm_ms(id%16,val);
  }
}


void Servo::set(float angle){
  this->ad = angle;
  printf("angle %f\n",angle);
  angle = convert_angle(angle);
  this->currentAngle = angle;
  this->a = angle;
  // int val = g.map(angle,0.f,180.f,LMIN,LMAX);
  float val = g.map(angle,0.f,180.f,LMIN,LMAX);
  debug(4, " PWM      :", val);
  // g.pwm.set_pwm(id,0,val);
  // printf("angle : %f\n",angle); // debug
  // printf("pwm_ms: %f\n",val);   // debug
  if(id < 16){
    g.left.set_pwm_ms(id,val);
  } else {
    g.right.set_pwm_ms(id%16,val);
  }
}
