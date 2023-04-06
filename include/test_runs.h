#pragma once
#include "servo.h"
#include "leg.h"
#include "global.h"
#include <iostream>

// extern Global g;

int sideToBit(std::string side){
  if(side == "l")
    return SIDE::LEFT;
  else if(side == "r")
    return SIDE::RIGHT;
  else
    printf("wrong side input\n");
}

int legToBit(std::string leg){
  if(leg == "f")
    return LEG::FRONT;
  else if(leg == "m")
    return LEG::MIDDLE;
  else if(leg == "b")
    return LEG::BACK;
  else
    printf("wrong leg  input\n");
}

int partToBit(std::string part){
  if(part == "i")
    return PART::INNER;
  else if(part == "m")
    return PART::MIDDLE;
  else if(part == "o")
    return PART::OUTER;
  else
    printf("wrong part input\n");
}

void print_menu(){
  printf("");
}

// Drives specific servo to inputted angle by user
// TODO: make work with rpi
void test_DRIVE_TO_INPUT(Body* body){
  std::string side;
  std::string leg;
  std::string part;
  int angle;
  printf("Enter (SIDE LEG PART angle): ");
  std::cin >> side;
  std::cin >> leg;
  std::cin >> part;
  std::cin >> angle;
  printf("Moving to SIDE::%s LEG::%s PART::%s angle=%d\n",side.c_str(),leg.c_str(),part.c_str(),angle);

  int bside = sideToBit(side);
  int bleg  = legToBit(leg);
  int bpart = partToBit(part);

  g.print_bin("bin",bside | bleg | bpart);

  printf("\n\n\n\n\n\n");

  if(bside && bleg && bpart)
    body->setServos(angle, bside | bleg | bpart);
}


// Drives specific servo to cartesian coords by user
// TODO: Make work with RPI
void test_DRIVE_TO_XYZ(Leg* leg){
  int x, y, z;
  printf("Enter XYZ: ");
  std::cin >> x;
  std::cin >> y;
  std::cin >> z;
  printf("Moving to %d %d %d\n",x,y,z);

  leg->set_catesian(x,y,z);
}

void test_LOOP_R_INCREASE(Leg* leg, long speed_delay = 30, float height = 45){
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
void test_LOOP_Y_INCREASE(Leg* leg, float x = 70, float y_range = 30, long speed_delay = 30, float height = 45){
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

void test_LOOP_90_DEG(Leg* leg){
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
