#pragma once
#include "global.h"
#include "debuggable.h"

class Servo: public Debuggable{
public:
  int part;
  int bits;
  int id;
  float currentAngle;
  int a, ad;
  float scaling = 1;

  int limits[2];

  // float targetAngle;
  // float speed;

  Servo(int side_leg_servo_bits);

  // Sets the hard limits of the servo
  // @param low minimum angle in degrees for initialization for servo (it will never go below this value, and the mathematical 0 is this value)
  // @param high maximum angle in degrees for initialization for servo (it will never go above this value, thus may not reach 180 deg)
  void setLimits(int low, int high);

  // Converts the angle from degrees to PWM length
  // @param angle angle in degrees from the Servo's respective 0 position
  float convert_angle(float angle);

  // Overrides the hard limits to set the angle of the servo (used for testing)
  // @param angle angle in degrees from the Servo's respective 0 position
  void directDrive(float angle);

  // Sets the angle on the servo, making sure the limits are abided
  // @param angle angle in degrees from the Servo's respective 0 position
  void set(float angle);
};
