#include "mservo.h"
#include "globals.h"
#include "debuggable.h"

extern Global g;

MServo::MServo(SIDE side, LEG leg, PART part){
  this->part = part;
  this->id = (int) int(side)*(4*4) + int(leg)*4 + int(part);
  this->currentAngle = 0; // TODO figure out best defaulting angle
  set(currentAngle);
}

float MServo::convert_angle(float angle){
  int hLim0 = g.hard_limits[int(part)][0];
  int hLim1 = g.hard_limits[int(part)][1];
  int diff = hLim1 - hLim0;
  switch(part){
  case PART::INNER:
    debug(3, "  Original : ", angle);
    angle = g.constrain(int(angle), -diff/2, diff/2);
    debug(3, "  Constrain: ", angle);
    angle = g.map(angle, -diff/2, diff/2, hLim0, hLim1);
    debug(3, "  Map      : ", angle);
    return angle;
  case PART::MIDDLE:
    debug(3, "  Original : ", angle);
    angle = g.constrain(int(angle), 0, diff);
    debug(3, "  Constrain: ", angle);
    angle = g.map(angle, 0, diff, hLim1, hLim0); // THIS ONE IS FLIPPED!
    debug(3, "  Map      : ", angle);
    return angle;
  case PART::OUTER:
    debug(3, "  Original : ", angle);
    angle *= 80./90;
    debug(3, "  Adjusted : ", angle);
    angle = g.constrain(int(angle), 0, diff);
    debug(3, "  Constrain: ", angle);
    angle = g.map(angle, 0, diff, hLim0, hLim1);
    debug(3, "  Map      : ", angle);
    return angle;
  default:
    return angle;
  }
}

void MServo::set(float angle){
  angle = convert_angle(angle);
  this->currentAngle = angle;
  int val = g.map(angle,0,180,LMIN,LMAX);
  debug(4, " PWM      :", val);
  g.pwm.set_pwm(id,0,val);
}
