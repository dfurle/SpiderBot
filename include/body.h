#pragma once
#include "leg.h"
#include "global.h"
#include <vector>

class Body{
public:

  std::vector<Leg*> legs;

  Body(){

  }


  // WARNING, CAUSES MEMORY LEAK WHEN RAN MULTIPLE TIMES!!!
  void initialize(){
    legs.resize(6);
    legs[id_FL] = new Leg(LEG::FRONT_LEFT);
    legs[id_ML] = new Leg(LEG::MIDDLE_LEFT);
    legs[id_RL] = new Leg(LEG::REAR_LEFT);

    legs[id_FR] = new Leg(LEG::FRONT_RIGHT);
    legs[id_MR] = new Leg(LEG::MIDDLE_RIGHT);
    legs[id_RR] = new Leg(LEG::REAR_RIGHT);
  }


  Leg* getLeg(int bits){
    int leg  = bits & LEG::ALL;
    leg  >>= LEG::MIN;
    leg =  g.findSetBit(leg);
    if(!leg){
      printf("leg  input incorrect\n");
      return nullptr;
    }
    leg--;
    printf("getLet leg: %d\n",leg);
    return legs[leg%6]; // shouldnt overflow but just in case...
  }

  // only input single bit, get single servo
  Servo& getServo(int bits){
    // maybe use strip since more modular?
    // int part = strip(bits, PART::ALL);
    // int leg_bits = strip(bits, (SIDE::ALL | LEG::ALL));

    int part = bits & PART::ALL;
    if(part == PART::INNER)
      return getLeg(bits)->i;
    if(part == PART::MIDDLE)
      return getLeg(bits)->m;
    if(part == PART::OUTER)
      return getLeg(bits)->o;
    printf("Should not be here, PART input incorrect\n");
    // return 0;
  }

  template<typename Func>
  void runForServos(Func f, int bits){
    int leg  = g.strip(bits, LEG::ALL);
    int part = g.strip(bits, PART::ALL);

    // printf("inp  :");
    // print_bin(bits);
    // printf("side :");
    // print_bin(side);
    // printf("leg  :");
    // print_bin(leg);
    // printf("part :");
    // print_bin(part);

    if(!part || !leg){
      printf("Missing inputs\n");
    }

    int bit_l = 1<<LEG::MIN;
    for(int l = 0; l < 6; l++){ // 6 legs
      int bit_p = 1<<PART::MIN;
      for(int p = 0; p < 3; p++){ // 3 servos per leg
        int mbits = (leg & bit_l) | (part & bit_p);
        if((leg & bit_l) && (part & bit_p)){
          f(getServo(mbits));
        }
        bit_p <<= 1;
      }
      bit_l <<= 1;
    }
  }

  void setLimits(int min, int max, int bits){
    runForServos([&](Servo& s){s.setLimits(min, max);}, bits);
  }

  // can input multiple bits for servo
  void setServos(int angle, int bits){
    runForServos([&](Servo& s){s.set(angle);}, bits);
  }
};
