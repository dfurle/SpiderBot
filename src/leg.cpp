#include "leg.h"
// #include "globals.h"
// #include "debuggable.h"
#include "servo.h"



Leg::Leg(int leg_bits, Vec3f* plane_rotation):
i(leg_bits | PART::INNER),
m(leg_bits | PART::MIDDLE),
o(leg_bits | PART::OUTER)
{
  this->plane_rotation = plane_rotation;

  switch(leg_bits){
    case LEG::FRONT_RIGHT:
      name = "FR"; break;
    case LEG::MIDDLE_RIGHT:
      name = "MR"; break;
    case LEG::REAR_RIGHT:
      name = "RR"; break;
    case LEG::FRONT_LEFT:
      name = "FL"; break;
    case LEG::MIDDLE_LEFT:
      name = "ML"; break;
    case LEG::REAR_LEFT:
      name = "RL"; break;
  }
};

void Leg::set_debug(int new_debug_level){
  debug_level = new_debug_level;
  i.set_debug(debug_level);
  m.set_debug(debug_level);
  o.set_debug(debug_level);
}

// void Leg::set_offsets(float rot, float offx, float offy, bool flip){
//   this->isFlipped = flip;
//   this->cartesian_rotation = rot * DEG_TO_RAD;
//   this->offset.x = offx;
//   this->offset.y = offy * (isFlipped ? -1 : 1);
// }

void Leg::set_offsets(float rotation, Vec3f centerOffset, Vec3f zeroOffset, bool flip){
  this->isFlipped = flip;

  // centerOffset.y *= (isFlipped ? -1 : 1);
  zeroOffset.y   *= (isFlipped ? -1 : 1);

  this->centerOffset = centerOffset;
  this->zeroOffset = zeroOffset;
  this->rotation = rotation * DEG_TO_RAD;
}


// (old) https://www.desmos.com/calculator/pxnzvg15nf
// (old) https://www.desmos.com/calculator/zwpvstzazw
// https://www.desmos.com/calculator/yvtlskfmwz
// idk if link will be dead after a while or not...
// void calcAngles(float theta, float r, float height, float& innerA, float& middleA, float& outerA){
void Leg::calcAngles(float theta, float r, float height){
  r = r - INN_L;
  float r2 = r*r;
  // this is the height from middle servo to base (in this case lowest point of my leg)
  // height += 38; // TODO: define somewhere;
  float height2 = height*height;
  float innerA = theta;
  if(debug(4))
    printf("t r h: %f %f %f\n",theta, r, height);
  // float middleA = RAD_TO_DEG*(M_PI-atan(r/height)-acos((MID_L2+r2+height2-OUT_L2)/(2*MID_L*sqrt(r2+height2))));
  float middleA = RAD_TO_DEG*(M_PI-atan2(r,height)-acos((MID_L2+r2+height2-OUT_L2)/(2*MID_L*sqrt(r2+height2))));
  float outerA  = RAD_TO_DEG*(M_PI-acos((MID_L2+OUT_L2-r2-height2)/(2*MID_L*OUT_L)));
  if(debug(4))
    printf("i m o: %f %f %f\n",innerA, middleA, outerA);

  // TODO: Make this prettier
  if(debug(-1,-1)){
    printf("Calculated Pt:  \n");
    int mx = MID_L * sin(middleA*DEG_TO_RAD);
    int my = MID_L * cos(middleA*DEG_TO_RAD);

    int ox = mx + OUT_L * sin(DEG_TO_RAD*(180-middleA-outerA));
    int oy = my - OUT_L * cos(DEG_TO_RAD*(180-middleA-outerA));

    int exp_x = r;
    int exp_y = height;

    printf("x: %d == %d\n", ox, exp_x);
    printf("y: %d == %d\n", oy, exp_y);
    printf("\n");
  }
  set_angles(innerA, middleA, outerA);
}
// void Leg::convert(Vec3f& pos){
//   pos.y = pos.y * (isFlipped ? -1 : 1);
//   Vec3f tmp = pos + offset;
//   if(debug(4))
//     printf("cartesian: %4.0f %4.0f %4.0f\n", tmp.x, tmp.y, tmp.z);

//   pos.x = tmp.x*cos(cartesian_rotation) - tmp.y*sin(cartesian_rotation);
//   pos.y = tmp.x*sin(cartesian_rotation) + tmp.y*cos(cartesian_rotation);
//   if(debug(4))
//     printf("cartesian: %4.0f %4.0f %4.0f\n", pos.x, pos.y, pos.z);
// }

// void Leg::convert_back(Vec3f& pos){
//   Vec3f tmp;
//   tmp.x = pos.x*cos(-cartesian_rotation) - pos.y*sin(-cartesian_rotation);
//   tmp.y = pos.x*sin(-cartesian_rotation) + pos.y*cos(-cartesian_rotation);
//   tmp.z = pos.z;
//   if(debug(4))
//     printf("cartesian: %4.0f %4.0f %4.0f\n", tmp.x, tmp.y, tmp.z);


//   pos = tmp - offset;
//   pos.y = pos.y * (isFlipped ? -1 : 1);
//   pos.z = tmp.z;
//   if(debug(4))
//     printf("cartesian: %4.0f %4.0f %4.0f\n", pos.x, pos.y, pos.z);
// }



void Leg::convert(Vec3f& pos){
  Vec3f zeroPos = centerOffset + zeroOffset;
  Vec3f rotPos = zeroPos;
  // if(debug(0))
  //   printf(" cartesian: %4.0f %4.0f %4.0f\n", rotPos.x, rotPos.y, rotPos.z);
  rotPos = rotPos.rotate(plane_rotation->y, 'y');
  rotPos = rotPos.rotate(plane_rotation->x, 'x');
  // if(debug(0))
  //   printf(" rotated cartesian: %4.0f %4.0f %4.0f\n", rotPos.x, rotPos.y, rotPos.z);
  Vec3f difference = zeroPos - rotPos;
  difference.y = difference.y  * (isFlipped ? -1 : 1);
  // if(debug(0))
  //   printf(" flip diff: %4.0f %4.0f %4.0f\n", difference.x, difference.y, difference.z);
  // Vec3f difference = Vec3f::zero();


  // pos.y = pos.y * (isFlipped ? -1 : 1); // TODO: reenable?
  Vec3f tmp = pos + zeroOffset + difference;
  tmp = tmp.rotate(rotation, 'z');
  pos = tmp;
}

void Leg::convert_back(Vec3f& pos){
  Vec3f zeroPos = centerOffset + zeroOffset;
  Vec3f rotPos = zeroPos;
  rotPos = rotPos.rotate(plane_rotation->y, 'y');
  rotPos = rotPos.rotate(plane_rotation->x, 'x');
  Vec3f difference = zeroPos - rotPos;
  difference.y = difference.y  * (isFlipped ? -1 : 1);

  Vec3f tmp = pos;
  tmp = tmp.rotate(-rotation, 'z');
  pos = tmp - zeroOffset - difference;
  // pos.y = pos.y * (isFlipped ? -1 : 1);
}

void Leg::set_cartesian(Vec3f pos){
  if(debug(0))
    printf("%s (%4.0f %4.0f %4.0f)\n", name.c_str(), pos.x, pos.y, pos.z);
  convert(pos);

  if(debug(0))
    printf("set xyz %4.0f %4.0f %4.0f\n",pos.x, pos.y, pos.z);

  this->pos = pos;
  
  float r = sqrt(pos.x*pos.x + pos.y*pos.y);
  float theta = atan2(-pos.y,pos.x) * RAD_TO_DEG;

  debug(5, " catesian      r = ", r);
  debug(5, " cartesian theta = ", theta);
  
  // Could just set inside calcAngles so can reduce to 1 line
  // float innerA, middleA, outerA;
  // calcAngles(theta, r, height, innerA, middleA, outerA);
  // set_angles(innerA, middleA, outerA);

  calcAngles(theta, r, pos.z);
}

void Leg::move_cartesian(Vec3f pos){
  Vec3f tmp = this->pos;
  convert_back(tmp);
  if(debug(4))
    printf("tmp: xyz %f %f %f\n",tmp.x, tmp.y, tmp.z);
  tmp += pos;
  set_cartesian(tmp);
}

// Gonna try to implement this in Body class first
// void Leg::move_cartesian_speed(Vec3f target, float time_to_complete){
//   float current_time = 0;
//   Vec3f delta = target * (10 / time_to_complete); // get delta per iteration
  
//   while(current_time < time_to_complete){
//     move_cartesian(delta);
//     usleep(10000); // 10ms
//     current_time += 10; // experiment, maybe it doesnt sleep for 10ms or something?
//   }
// }

void Leg::test_set_r(float r, float height){

  if(debug(3)){
    printf("Angles: r=%f\n",r);
  }

  // Could just set inside calcAngles so can reduce to 1 line
  // float innerA, middleA, outerA;
  // calcAngles(0, r, height, innerA, middleA, outerA);
  // set_angles(innerA, middleA, outerA);

  calcAngles(0, r, height);
}

void Leg::set_angles(float innerA, float middleA, float outerA){
  if(debug(2))
    printf(" Inner\n");
  i.set(innerA);

  if(debug(2))
    printf(" Middle\n");
  m.set(middleA);

  if(debug(2))
    printf(" Outer\n");
  o.set(outerA);
}
