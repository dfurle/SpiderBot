#pragma once
#include "body.h"
#include "servo.h"
#include "leg.h"
#include "global.h"
#include <iostream>
#include <map>
#include <algorithm>

int bits_selected = 0;
bool adjustedAngle = true;

int toBits(std::string str){
  size_t pos = 0;
  std::string token;

  int bits = 0;
  int bits_override = 0;
  int bits_append = 0;
  int bits_subtr = 0;

  std::map<std::string, int> index;
  index["FR"] = LEG::FR;
  index["MR"] = LEG::MR;
  index["RR"] = LEG::RR;
  index["FL"] = LEG::FL;
  index["ML"] = LEG::ML;
  index["RL"] = LEG::RL;
  index["LALL"] = LEG::ALL;
  index["TRIR"] = COMMON::TRI_RIGHT;
  index["TRIL"] = COMMON::TRI_LEFT;
  index["INNER"] = PART::INNER;
  index["MIDDLE"] = PART::MIDDLE;
  index["OUTER"] = PART::OUTER;
  index["I"] = PART::INNER;
  index["M"] = PART::MIDDLE;
  index["O"] = PART::OUTER;
  index["PALL"] = PART::ALL;

  bool done = false;
  while(!done) {
    pos = str.find(' ');
    token = str.substr(0, pos);
    std::transform(token.begin(), token.end(), token.begin(), ::toupper);
    str.erase(0, pos+1);
    char addsub = token[0];
    if(addsub == '+' || addsub == '-')
      token = token.substr(1);
    else
      addsub = ' ';
    auto it = index.find(token);
    if (it != index.end()){
      g.print_bin("bits",bits);
      g.print_bin("iter",it->second);
      switch(addsub){
      case ' ':
        bits_override |= it->second;
        break;
      case '+':
        bits_append |= it->second;
        break;
      case '-':
        // bits_subtr &= ~it->second;
        bits_subtr |= it->second;
      }
    } else {
      printf("Could not find token (%s)\n",token.c_str());
    }
    if(pos == std::string::npos){
      done = true;
    }
  }
  if(g.strip(bits_override, LEG::ALL) == 0)
    bits_override |= g.strip(bits_selected, LEG::ALL);
  if(g.strip(bits_override, PART::ALL) == 0)
    bits_override |= g.strip(bits_selected, PART::ALL);
  bits |= bits_override;
  bits |= bits_append;
  bits &= ~bits_subtr;
  return bits;
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

void print_menu(Body& body){
  printf("Currently Editing:\n");
  int b = bits_selected;
  printf("Right: (%5s) | (%6s) | (%5s)\n",(b & LEG::FR)?"FRONT":"",(b & LEG::MR)?"MIDDLE":"",(b & LEG::RR)?"BACK ":"");
  printf("Left : (%5s) | (%6s) | (%5s)\n",(b & LEG::FL)?"FRONT":"",(b & LEG::ML)?"MIDDLE":"",(b & LEG::RL)?"BACK ":"");
  printf("Parts: (%5s) | (%6s) | (%5s)\n",(b & PART::INNER)?"INNER":"",(b & PART::MIDDLE)?"MIDDLE":"",(b & PART::OUTER)?"OUTER":"");
  g.print_bin("bin",bits_selected);
  printf("\nStatus in (%s) form\n\n",(adjustedAngle?"Adjusted":"Raw"));

  std::vector<int> aa;
  aa.resize(18); // 2*3*3 = 18
  if(adjustedAngle){
    aa[0]  = body.legs[id_FL]->o.ad; aa[2]  = body.legs[id_FL]->m.ad; aa[3]  = body.legs[id_FL]->i.ad;
    aa[1]  = body.legs[id_FR]->o.ad; aa[4]  = body.legs[id_FR]->i.ad; aa[5]  = body.legs[id_FR]->m.ad;
    aa[6]  = body.legs[id_ML]->o.ad; aa[8]  = body.legs[id_ML]->m.ad; aa[9]  = body.legs[id_ML]->i.ad;
    aa[7]  = body.legs[id_MR]->o.ad; aa[10] = body.legs[id_MR]->i.ad; aa[11] = body.legs[id_MR]->m.ad;
    aa[12] = body.legs[id_RL]->o.ad; aa[14] = body.legs[id_RL]->m.ad; aa[15] = body.legs[id_RL]->i.ad;
    aa[13] = body.legs[id_RR]->o.ad; aa[16] = body.legs[id_RR]->i.ad; aa[17] = body.legs[id_RR]->m.ad;
  } else {
    aa[0]  = body.legs[id_FL]->o.a; aa[2]  = body.legs[id_FL]->m.a; aa[3]  = body.legs[id_FL]->i.a;
    aa[1]  = body.legs[id_FR]->o.a; aa[4]  = body.legs[id_FR]->i.a; aa[5]  = body.legs[id_FR]->m.a;
    aa[6]  = body.legs[id_ML]->o.a; aa[8]  = body.legs[id_ML]->m.a; aa[9]  = body.legs[id_ML]->i.a;
    aa[7]  = body.legs[id_MR]->o.a; aa[10] = body.legs[id_MR]->i.a; aa[11] = body.legs[id_MR]->m.a;
    aa[12] = body.legs[id_RL]->o.a; aa[14] = body.legs[id_RL]->m.a; aa[15] = body.legs[id_RL]->i.a;
    aa[13] = body.legs[id_RR]->o.a; aa[16] = body.legs[id_RR]->i.a; aa[17] = body.legs[id_RR]->m.a;
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
  printf("  [ fr mr rr fl ml rl i m o trir tril lall pall ]\n");
  printf("     '+' -    prefix: append to   current selection\n");
  printf("     '-' -    prefix: remove from current selection\n");
  printf("         - no prefix: override    current selection\n");
  printf("     '#' - number to set angle\n");
  printf("     's' - switch angle viewing type\n");
  std::string in;
  std::getline(std::cin, in);

  try{
    angle = std::stoi(in);
    return true;
  } catch(std::invalid_argument& e){}

  if(in[0] == 's' || in[0] == 'S'){
    adjustedAngle = !adjustedAngle;
  } else {
    // std::string str;
    // std::getline(std::cin, str);
    bits_selected = toBits(in); // TODO: add check for properness
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
