#ifndef MSERVO_H
#define MSERVO_H
#include "globals.h"

class MServo{
public:
  PART part;
  int id;
  float currentAngle;
  // float targetAngle;
  // float speed;

  
  int debug_level = 0;

  bool debug(int min, int max = 1e3){
    return min <= debug_level && debug_level <= max;
  }

  // TODO: figure out way to add max value too
  bool debug(int min, char* str, float val = -1){
    bool ret = min <= debug_level;
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
  }

  MServo(SIDE side, LEG leg, PART part){
    this->part = part;
    this->id = (int) int(side)*(4*4) + int(leg)*4 + int(part);
    this->currentAngle = 0; // TODO figure out best defaulting angle
    set(currentAngle);
  }

  float convert_angle(float angle){
    int hLim0 = hard_limits[int(part)][0];
    int hLim1 = hard_limits[int(part)][1];
    int diff = hLim1 - hLim0;
    switch(part){
    case PART::INNER:
      debug(3, "  Original : ", angle);
      angle = constrain(angle, -diff/2, diff/2);
      debug(3, "  Constrain: ", angle);
      angle = map(angle, -diff/2, diff/2, hLim0, hLim1);
      debug(3, "  Map      : ", angle);
      return angle;
    case PART::MIDDLE:
      debug(3, "  Original : ", angle);
      angle = constrain(angle, 0, diff);
      debug(3, "  Constrain: ", angle);
      angle = map(angle, 0, diff, hLim1, hLim0); // THIS ONE IS FLIPPED!
      debug(3, "  Map      : ", angle);
      return angle;
    case PART::OUTER:
      debug(3, "  Original : ", angle);
      angle *= 80./90;
      debug(3, "  Adjusted : ", angle);
      angle = constrain(angle, 0, diff);
      debug(3, "  Constrain: ", angle);
      angle = map(angle, 0, diff, hLim0, hLim1);
      debug(3, "  Map      : ", angle);
      return angle;
    default:
      return angle;
    }
  }

  void set(float angle){
    angle = convert_angle(angle);
    this->currentAngle = angle;
    int val = map(angle,0,180,LMIN,LMAX);
    debug(4, " PWM      :", val);
    pwm.setPWM(id,0,val);
  }
};

#endif