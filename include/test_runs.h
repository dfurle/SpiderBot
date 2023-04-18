#pragma once
#include "body.h"
#include "servo.h"
#include "leg.h"
#include "global.h"
#include <iostream>

// extern Global g;

int sideToBit(std::string side){
  int v = 0;
  for(char c : side){
    if(c == 'l')
      v |= SIDE::LEFT;
    else if(c == 'r')
      v |= SIDE::RIGHT;
    else if(c == 'a')
      v |= SIDE::ALL;
    else
      printf("wrong side input\n");
  }
  return v;
}

int legToBit(std::string leg){
  int v = 0;
  for(char c : leg){
    if(c == 'f')
      v |= LEG::FRONT;
    else if(c == 'm')
      v |= LEG::MIDDLE;
    else if(c == 'b')
      v |= LEG::BACK;
    else if(c == 'a')
      v |= LEG::ALL;
    else
      printf("wrong leg  input\n");
  }
  return v;
}

int partToBit(std::string part){
  int v = 0;
  for(char c : part){
    if(c == 'i')
      v |= PART::INNER;
    else if(c == 'm')
      v |= PART::MIDDLE;
    else if(c == 'o')
      v |= PART::OUTER;
    else if(c == 'a')
      v |= PART::ALL;
    else
      printf("wrong part input\n");
  }
  return v;
}

/*
  .  │  ┤  ┐  └  ┴  ┬  ├  ─  ┼  ┘  ┌

  Currently Editing:
  Sides: (LEFT)  | (RIGHT)  |
  Legs : (FRONT) | (MIDDLE) | (BACK)
  Parts: (INNER) | (MIDDLE) | (OUTER)

  Status:

  .  000┌─────┐  ┌─────────┐  ┌─────┐000
  .     │  000└──┤000   000├──┘000  │
  .              │         │
  .  000┌─────┐  │         │  ┌─────┐000
  .     │  000└──┤000   000├──┘000  │
  .              │         │
  .  000┌─────┐  │         │  ┌─────┐000
  .     │  000└──┤000   000├──┘000  │
  .              └─────────┘

*/

int bits_selected = 0;
bool adjustedAngle = true;

void print_menu(Body& body){
  printf("Currently Editing:\n");
  int b = bits_selected;
  printf("Sides: (%5s) | (%5s) |\n",((b & SIDE::LEFT)?"LEFT ":""),((b & SIDE::RIGHT)?"RIGHT":""));
  printf("Legs : (%5s) | (%5s) | (%5s)\n",(b & LEG::FRONT)?"FRONT":"",(b & LEG::MIDDLE)?"MIDDLE":"",(b & LEG::BACK)?"BACK ":"");
  printf("Parts: (%5s) | (%5s) | (%5s)\n",(b & PART::INNER)?"INNER":"",(b & PART::MIDDLE)?"MIDDLE":"",(b & PART::OUTER)?"OUTER":"");
  g.print_bin("bin",bits_selected);
  printf("\nStatus in (%s) form\n\n",(adjustedAngle?"Adjusted":"Raw"));

  std::vector<int> aa;
  aa.resize(18); // 2*3*3 = 18
  if(adjustedAngle){
    aa[0]  = body.legs[LF]->o.ad; aa[2]  = body.legs[LF]->m.ad; aa[3]  = body.legs[LF]->i.ad;
    aa[1]  = body.legs[RF]->o.ad; aa[4]  = body.legs[RF]->i.ad; aa[5]  = body.legs[RF]->m.ad;
    aa[6]  = body.legs[LM]->o.ad; aa[8]  = body.legs[LM]->m.ad; aa[9]  = body.legs[LM]->i.ad;
    aa[7]  = body.legs[RM]->o.ad; aa[10] = body.legs[RM]->i.ad; aa[11] = body.legs[RM]->m.ad;
    aa[12] = body.legs[LB]->o.ad; aa[14] = body.legs[LB]->m.ad; aa[15] = body.legs[LB]->i.ad;
    aa[13] = body.legs[RB]->o.ad; aa[16] = body.legs[RB]->i.ad; aa[17] = body.legs[RB]->m.ad;
  } else {
    aa[0]  = body.legs[LF]->o.a; aa[2]  = body.legs[LF]->m.a; aa[3]  = body.legs[LF]->i.a;
    aa[1]  = body.legs[RF]->o.a; aa[4]  = body.legs[RF]->i.a; aa[5]  = body.legs[RF]->m.a;
    aa[6]  = body.legs[LM]->o.a; aa[8]  = body.legs[LM]->m.a; aa[9]  = body.legs[LM]->i.a;
    aa[7]  = body.legs[RM]->o.a; aa[10] = body.legs[RM]->i.a; aa[11] = body.legs[RM]->m.a;
    aa[12] = body.legs[LB]->o.a; aa[14] = body.legs[LB]->m.a; aa[15] = body.legs[LB]->i.a;
    aa[13] = body.legs[RB]->o.a; aa[16] = body.legs[RB]->i.a; aa[17] = body.legs[RB]->m.a;
  }

  auto it = aa.begin();

  printf("  .  %03d┌─────┐  ┌─────────┐  ┌─────┐%03d\n",*(it++),*(it++));
  printf("  .     │  %03d└──┤%03d   %03d├──┘%03d  │   \n",*(it++),*(it++),*(it++),*(it++));
  printf("  .              │         │            \n");
  printf("  .  %03d┌─────┐  │         │  ┌─────┐%03d\n",*(it++),*(it++));
  printf("  .     │  %03d└──┤%03d   %03d├──┘%03d  │   \n",*(it++),*(it++),*(it++),*(it++));
  printf("  .              │         │            \n");
  printf("  .  %03d┌─────┐  │         │  ┌─────┐%03d\n",*(it++),*(it++));
  printf("  .     │  %03d└──┤%03d   %03d├──┘%03d  │   \n",*(it++),*(it++),*(it++),*(it++));
  printf("  .              └─────────┘            \n");
  printf("\n");
}

// returns if angle is returned
bool get_input(int& angle){
  printf("       E - edit which servos are accessed\n");
  printf("       A - set just servo of choice\n");
  printf("       S - Switch angle type viewing\n");
  printf("       # - or enter any number to set angle\n");
  printf("Enter ('e', 's', 'a' or angle): ");
  std::string in;
  std::cin >> in;
  if(in[0] == 'e' || in[0] == 'E'){
    printf("Enter Servos to access: (side:(rla) leg:(fmba) part:(omia))   (ex: 'r fm o')\n");
    std::string side;
    std::string leg;
    std::string part;

    std::cin >> side;
    std::cin >> leg;
    std::cin >> part;
    int bside = sideToBit(side);
    int bleg  = legToBit(leg);
    int bpart = partToBit(part);
    if(bside && bleg && bpart){
      bits_selected = bside | bleg | bpart;
    } else {
      printf("Invalid inputs, please enter only above mentioned\n");
    }
  } else if(in[0] == 's' || in[0] == 'S'){
    adjustedAngle = !adjustedAngle;
  } else if(in[0] == 'a' || in[0] == 'A'){
    printf("Enter Servos and angle: (part:(omia) #angle)   (ex: 'r fm o')\n");
    std::string part;
    int angle = 0;
    std::cin >> part;
    std::cin >> angle;
    int bpart = partToBit(part);
    if(bits_selected && bpart){
      bits_selected %= 1<<PART::MIN;
      bits_selected |= bpart;
    } else {
      printf("Invalid inputs, please enter only above mentioned\n");
    }
  } else { // number probably input
    angle = std::stoi(in);
    return true;
  }
  return false;
}

// Drives specific servo to inputted angle by user
// TODO: make work with rpi
void test_DRIVE_TO_INPUT(Body& body){
  printf("\n\n\n\n\n\n");
  print_menu(body);
  int angle = 0;
  if(get_input(angle)){
    if(bits_selected)
      body.setServos(angle, bits_selected);
    else
      printf("bits not set\n");
  }
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
