#pragma once

#include <vector>
#include "global.h"
#include "servo.h"
#include "debuggable.h"
#include "vec.h"

extern Global g;

class Leg: public Debuggable{
public:
  Servo i, m, o;
  Vec3f pos, lpos, centerOffset, zeroOffset;
  Vec3f* plane_rotation;
  std::string name;
  bool isFlipped = false;
  float rotation = 0;
  float t_offset = 0;
  std::vector<Vec3f> pts;

  void set_debug(int new_debug_level);

  Leg(int leg_bits, Vec3f* plane_rotation);

  void set_offsets(float rotation, Vec3f centerOffset, Vec3f zeroOffset, float t_offset, bool flip=false);
  void set_plane(Vec3f plane_rotation);
  // void set_offsets(float rot, float offx, float offy, bool flip = false);
  
  // Sets the offsets required to calculate various positions;
  // @param rot counter clockwise rotation from "forward" direction of spider of each servo pointing
  // @param offx forward, X offset where to say the "0" is when using inverse kinematics (XYZ positioning)
  // @param offy sideways (does not depend on side, flips by "flip" param), Y offset where to say the "0" is when using inverse kinematics (XYZ positioning)
  // @param flip default=false, whether it is on the left side, meaning the y axis is flipped
  // void set_offsets(float rot, float offx, float offy, bool flip = false);

  // Converts from relative, global XYZ position to Servo orientation to do IK
  // @param pos the reference to Vec3f vector (position in relative coordinates, the offsetted 0,0)
  void convert(Vec3f& pos);

  // // Converts from Servo orientation to relative, global XYZ position; to add XYZ Move Offsets
  // // @param pos the reference to Vec3f vector (position in Servo coordinates)
  // void convert_back(Vec3f& pos);

  // TODO: can probably be made private;
  // Main Inverse Kinematic Function:
  // See: https://www.desmos.com/calculator/yvtlskfmwz for more info on how the functions look like
  // @param theta angle from servo "forward"
  // @param r distance on flat plane, from inner servo
  // @param height distance from the flat plane, down (down is positive)
  void calcAngles(float theta, float r, float height);

  // Sets XYZ coordinates of the Leg using IK
  // @param pos the XYZ Vec3f
  void set_cartesian(Vec3f pos);

  // Moves the XYZ coordinates of the Leg from current using IK
  // @param pos the XYZ Vec3f to move by
  void move_cartesian(Vec3f pos);

  // Moves the XYZ coordinates of the Leg from current using IK with a speed
  // @param pos the XYZ Vec3f to move by
  // void move_cartesian_speed(Vec3f pos, float speed);

  // Test function to initialize with 0 theta and given R and height
  void test_set_r(float r, float height);

  // Sets the angles of the servos to their values; Used by IK
  void set_angles(float innerA, float middleA, float outerA);

  void set_loop(std::vector<Vec3f> pts){
    this->pts = pts;
  }

  void update(float t);

  // Sets the specific servo's angle
  // void setByIndex(int index, int angle);
};

