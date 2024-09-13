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

  // this->set_debug(5);
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

void Leg::set_offsets(float rotation, Vec3f centerOffset, Vec3f zeroOffset, float t_offset, bool flip){
  this->isFlipped = flip;

  // centerOffset.y *= (isFlipped ? -1 : 1);
  // zeroOffset.y   *= (isFlipped ? -1 : 1);
  // zeroOffset.y

  this->centerOffset = centerOffset;
  this->zeroOffset = zeroOffset;
  this->rotation = rotation * DEG_TO_RAD;

  this->t_offset = t_offset;
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

void Leg::update(float t){
  t = (t + this->t_offset);
  t = (t >= 1 ? t-1 : t);
  Vec3f pos = g.multi_lerp(this->pts, t);
  // printf("%s - lerping: (%4.0f %4.0f %4.0f)\n", this->name.c_str(), pos.x, pos.y, pos.z);
  this->set_cartesian(pos);
}

void Leg::convert(Vec3f& pos){
  this->pos = pos;
  if(debug(4))
    printf(" pos in   (%4.0f %4.0f %4.0f)\n", pos.x, pos.y, pos.z);
  Vec3f newPos = pos + this->centerOffset + this->zeroOffset;
  if(debug(4))
    printf(" pos add  (%4.0f %4.0f %4.0f)\n", newPos.x, newPos.y, newPos.z);
  newPos = newPos.rotate(this->plane_rotation->x, 'x');
  newPos = newPos.rotate(this->plane_rotation->y, 'y');
  newPos = newPos.rotate(this->plane_rotation->z, 'z');
  if(debug(4))
    printf(" pos rot1 (%4.0f %4.0f %4.0f)\n", newPos.x, newPos.y, newPos.z);
  Vec3f local = newPos - this->centerOffset;
  if(debug(4))
    printf(" pos sub  (%4.0f %4.0f %4.0f)\n", local.x, local.y, local.z);
  local = local.rotate(-rotation, 'z');
  if(debug(4))
    printf(" pos rot2 (%4.0f %4.0f %4.0f)\n", local.x, local.y, local.z);
  this->lpos = local;
  pos = local;
}

// void Leg::convert_back(Vec3f& pos){
//   Vec3f zeroPos = centerOffset + zeroOffset;
//   Vec3f rotPos = zeroPos;
//   rotPos = rotPos.rotate(plane_rotation->y, 'y');
//   rotPos = rotPos.rotate(plane_rotation->x, 'x');
//   Vec3f difference = zeroPos - rotPos;
//   difference.y = difference.y  * (isFlipped ? -1 : 1);

//   Vec3f tmp = pos;
//   tmp = tmp.rotate(-rotation, 'z');
//   pos = tmp - zeroOffset - difference;
//   // pos.y = pos.y * (isFlipped ? -1 : 1);
// }

void Leg::set_cartesian(Vec3f pos){
  if(debug(1))
    printf("%s (%4.0f %4.0f %4.0f)\n", name.c_str(), pos.x, pos.y, pos.z);
  convert(pos);
  if(debug(1))
    printf(" set xyz %4.0f %4.0f %4.0f\n",pos.x, pos.y, pos.z);

  // this->pos = pos;
  
  float r = sqrt(pos.x*pos.x + pos.y*pos.y);
  // float theta = atan2(-pos.y,pos.x) * RAD_TO_DEG;
  float theta = atan2(-pos.x,pos.y) * RAD_TO_DEG;

  // if(this->isFlipped){
  //   theta *= -1;
  // }

  debug(5, " catesian      r = ", r);
  debug(5, " cartesian theta = ", theta);
  
  // Could just set inside calcAngles so can reduce to 1 line
  // float innerA, middleA, outerA;
  // calcAngles(theta, r, height, innerA, middleA, outerA);
  // set_angles(innerA, middleA, outerA);

  calcAngles(theta, r, pos.z);
}

void Leg::move_cartesian(Vec3f pos){
  pos = this->pos + pos;
  if(debug(4))
    printf("tmp: xyz %f %f %f\n",pos.x, pos.y, pos.z);
  set_cartesian(pos);
}

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
