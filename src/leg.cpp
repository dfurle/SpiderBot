#include "leg.h"
// #include "globals.h"
// #include "debuggable.h"
#include "servo.h"


void Leg::set_debug(int new_debug_level){
  debug_level = new_debug_level;
  i.set_debug(debug_level);
  m.set_debug(debug_level);
  o.set_debug(debug_level);
}

void Leg::set_offsets(float rot, float offx, float offy, bool flip){
  this->isFlipped = flip;
  this->cartesian_rotation = rot * DEG_TO_RAD;
  this->cartesian_xoffset = offx;
  this->cartesian_yoffset = offy * (isFlipped ? -1 : 1);
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
  printf("t r h: %f %f %f\n",theta, r, height);
  // float middleA = RAD_TO_DEG*(M_PI-atan(r/height)-acos((MID_L2+r2+height2-OUT_L2)/(2*MID_L*sqrt(r2+height2))));
  float middleA = RAD_TO_DEG*(M_PI-atan2(r,height)-acos((MID_L2+r2+height2-OUT_L2)/(2*MID_L*sqrt(r2+height2))));
  float outerA  = RAD_TO_DEG*(M_PI-acos((MID_L2+OUT_L2-r2-height2)/(2*MID_L*OUT_L)));
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

void Leg::convert(Vec3f& pos){
  pos.y = pos.y * (isFlipped ? -1 : 1);
  Vec3f tmp = pos + offset;
  printf("cartesian: %4.0f %4.0f %4.0f\n", tmp.x, tmp.y, tmp.z);

  pos.x = tmp.x*cos(cartesian_rotation) - tmp.y*sin(cartesian_rotation);
  pos.y = tmp.x*sin(cartesian_rotation) + tmp.y*cos(cartesian_rotation);
  printf("cartesian: %4.0f %4.0f %4.0f\n", pos.x, pos.y, pos.z);
}

void Leg::convert_back(Vec3f& pos){
  Vec3f tmp;
  tmp.x = pos.x*cos(-cartesian_rotation) - pos.y*sin(-cartesian_rotation);
  tmp.y = pos.x*sin(-cartesian_rotation) + pos.y*cos(-cartesian_rotation);
  tmp.z = pos.z;
  printf("cartesian: %4.0f %4.0f %4.0f\n", tmp.x, tmp.y, tmp.z);


  pos = tmp - offset;
  pos.y = pos.y * (isFlipped ? -1 : 1);
  pos.z = tmp.z;
  printf("cartesian: %4.0f %4.0f %4.0f\n", pos.x, pos.y, pos.z);
}

void Leg::set_cartesian(float x, float y, float z){
  printf("cartesian: %4.0f %4.0f %4.0f\n", x, y, z);
  convert(x,y,z);

  printf("set xyz %4.0f %4.0f %4.0f\n",x,y,z);

  this->x = x;
  this->y = y;
  this->z = z;
  
  float r = sqrt(x*x + y*y);
  float theta = atan2(-y,x) * RAD_TO_DEG;

  debug(5, " catesian      r = ", r);
  debug(5, " cartesian theta = ", theta);
  
  // Could just set inside calcAngles so can reduce to 1 line
  // float innerA, middleA, outerA;
  // calcAngles(theta, r, height, innerA, middleA, outerA);
  // set_angles(innerA, middleA, outerA);

  calcAngles(theta, r, z);
}

void Leg::move_cartesian(float x, float y, float z){
  float tmpx = this->x;
  float tmpy = this->y;
  float tmpz = this->z;
  convert_back(tmpx, tmpy, tmpz);
  printf("tmp: xyz %f %f %f\n",tmpx, tmpy, tmpz);
  tmpx += x;
  tmpy += y;
  tmpz += z;
  set_cartesian(tmpx, tmpy, tmpz);
}

void Leg::move_cartesian_speed(float x, float y, float z, float speed){
  float curr_x = x;
  float curr_y = y;
  float curr_z = z;
  move_cartesian(x, y, z);
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
