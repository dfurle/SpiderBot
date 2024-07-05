#pragma once
#include "leg.h"
#include "global.h"
#include "vec.h"
#include <vector>

class Body{
public:

  std::vector<Leg*> legs;
  Vec3f plane_rotation;

  Body();

  // WARNING, CAUSES MEMORY LEAK WHEN RAN MULTIPLE TIMES!!!
  void initialize();

  void set_plane(Vec3f plane_rotation);

  // Returns pointer to Leg located at bitmask
  // @param bits the bitmask given in global.h (only cares about leg bits)
  Leg* getLeg(int bits);

  // Returns pointer to Servo located at bitmask
  // @param bits the bitmask given in global.h
  Servo* getServo(int bits);

  template<typename Func>
  // Runs inputted lambda function for all servos
  // @param f function takes "Servo" class as parameter that is provided to it
  // @param bits the masking bit string to select leg/servo '000 000000' with mapping/constants seen in global.h
  void runForServos(Func f, int bits);

  template<typename Func>
  // Runs inputted lambda function for all legs
  // @param f function takes "Leg" class as parameter that is provided to it
  // @param bits the masking bit string to select leg/servo '000 000000' with mapping/constants seen in global.h
  void runForLegs(Func f, int bits);

  // Sets limits on the servos with given bits as seen in global.h
  // @param min minimum angle in degrees for initialization for servo (it will never go below this value, and the mathematical 0 is this value)
  // @param max maximum angle in degrees for initialization for servo (it will never go above this value, thus may not reach 180 deg)
  // @param bits the bitmask given in global.h
  void setLimits(int min, int max, int bits);

  // Sets the angle on servos given by the bit mask
  // @param angle the angle in degrees to set the servos
  // @param bits the bitmask given in global.h
  void setServos(int angle, int bits);

  // Sets the XYZ inverse kinematics for servos given by bit mask
  // @param pos the Vec3f of the coordinates
  // @param bits the bitmask given in global.h (only cares about legs)
  void setXYZ(Vec3f pos, int bits);

  // Moves by XYZ using inverse kinematics for servos given by bit mask
  // @param pos the Vec3f to move the current position by
  // @param bits the bitmask given in global.h (only cares about legs)
  void moveXYZ(Vec3f pos, int bits);

  // Moves by XYZ using inverse kinematics for servos given by bit mask with a slowed down speed
  // @param pos the Vec3f to move the current position by
  // @param speed this is technically "time_to_complete" in ms
  // @param bits the bitmask given in global.h (only cares about legs)
  void moveXYZ_speed(Vec3f pos, float speed, int leg_bits);

  // Sets the scaling of angle on servos;
  //  Basically if mathematically input angle is 90deg, it is scaled by "scaling" to input further into servo
  // @param scaling the multiplier
  // @param bits the bitmask given in global.h
  void setScaling(float scaling, int bits);
};
