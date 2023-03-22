#include "mleg.h"
// #include "globals.h"
// #include "debuggable.h"
#include "mservo.h"


void MLeg::set_debug(int new_debug_level){
  debug_level = new_debug_level;
  i.set_debug(debug_level);
  m.set_debug(debug_level);
  o.set_debug(debug_level);
}


// (old) https://www.desmos.com/calculator/pxnzvg15nf
// https://www.desmos.com/calculator/zwpvstzazw
// idk if link will be dead after a while or not...
// void calcAngles(float theta, float r, float height, float& innerA, float& middleA, float& outerA){
void MLeg::calcAngles(float theta, float r, float height){
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

void MLeg::set_catesian(float x, float y, float height){
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

void MLeg::test_set_r(float r, float height){

  if(debug(3)){
    printf("Angles: r=%f\n",r);
  }

  // Could just set inside calcAngles so can reduce to 1 line
  // float innerA, middleA, outerA;
  // calcAngles(0, r, height, innerA, middleA, outerA);
  // set_angles(innerA, middleA, outerA);

  calcAngles(0, r, height);
}

void MLeg::set_angles(float innerA, float middleA, float outerA){
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