#pragma once
#include "mservo.h"
#include "mleg.h"
#include <iostream>

extern Global g;

void test_INIT_MID_CONST(MLeg* l){
  printf("INIT TO MID constrained\n");
  l->i.set(0);
  l->m.set(90);
  l->o.set(90);
}


void test_INIT_MAX_CONST(MLeg* l){
  printf("INIT TO MAX constrained\n");
  l->i.set(90);
  l->m.set(180);
  l->o.set(180);
}


void test_INIT_MIN_CONST(MLeg* l){
  printf("INIT TO MIN constrained\n");
  l->i.set(-90);
  l->m.set(0);
  l->o.set(0);
}


// Drives specific servo to inputted angle by user
// TODO: make work with rpi
void test_DRIVE_TO_INPUT(Body* body){
  int leg;
  int motor;
  int pos;
  printf("Enter Motor ID and Degree: ");
  std::cin >> leg;
  std::cin >> motor;
  std::cin >> pos;
  printf("Moving to %d %d\n",motor,pos);

  if(motor == -1){
    body->getLeg(SIDE::LEFT, LEG::FRONT)->i.set(0);
    //leg->m.set(0);
    //leg->o.set(0);
  } else if(motor == 0){
    //leg->i.set(pos);
  }else if(motor == 1){
    //leg->m.set(pos);
  }else if(motor == 2){
    //leg->o.set(pos);
  }
}


// Drives specific servo to cartesian coords by user
// TODO: Make work with RPI
void test_DRIVE_TO_XYZ(MLeg* leg){
  int x, y, z;
  printf("Enter XYZ: ");
  std::cin >> x;
  std::cin >> y;
  std::cin >> z;
  printf("Moving to %d %d %d\n",x,y,z);

  leg->set_catesian(x,y,z);
}

void test_LOOP_R_INCREASE(MLeg* leg, long speed_delay = 30, float height = 45){
  int min = 1;
  int max = sqrt((MID_L+OUT_L)*(MID_L+OUT_L)-(height*height)) - 1;
  printf("max: %d\n",max);
  for(int j = min; j <= max; j+=2){
    leg->test_set_r(j, height);
    usleep(speed_delay * 1000);
  }
  usleep(100000);
  for(int j = max; j >= min; j-=2){
    leg->test_set_r(j, height);
    usleep(speed_delay * 1000);
  }
  usleep(100000);
}

// WARNING, (y_range < x) !!! and might break with (height < 80) due to servo limits, TODO implement check and warning!
void test_LOOP_Y_INCREASE(MLeg* leg, float x = 70, float y_range = 30, long speed_delay = 30, float height = 45){
  float min = -y_range;
  float max =  y_range;
  for(float y = min; y <= max; y+=2){
    leg->set_catesian(x, y, height);
    usleep(speed_delay * 1000);
  }
  usleep(100000);
  for(float y = max; y >= min; y-=2){
    leg->set_catesian(x, y, height);
    usleep(speed_delay * 1000);
  }
  usleep(100000);
}

void test_LOOP_90_DEG(MLeg* leg){
  leg->i.set(0);
  leg->m.set(0);
  leg->o.set(0);
  usleep(10 * 1000 * 1000);

  leg->i.set(0);
  leg->m.set(90);
  leg->o.set(0);
  usleep(10 * 1000 * 1000);

  leg->i.set(0);
  leg->m.set(0);
  leg->o.set(0);
  usleep(10 * 1000 * 1000);

  leg->i.set(0);
  leg->m.set(0);
  leg->o.set(90);
  usleep(10 * 1000 * 1000);
}

// TODO: make all legs run the same test_###() code
void test_DO_ALL(){

}
