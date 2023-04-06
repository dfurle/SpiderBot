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
    legs[0] = new Leg(SIDE::LEFT | LEG::FRONT);
    legs[1] = new Leg(SIDE::LEFT | LEG::MIDDLE);
    legs[2] = new Leg(SIDE::LEFT | LEG::BACK);

    legs[3] = new Leg(SIDE::RIGHT | LEG::FRONT);
    legs[4] = new Leg(SIDE::RIGHT | LEG::MIDDLE);
    legs[5] = new Leg(SIDE::RIGHT | LEG::BACK);
  }

  int findSetBit(std::uint32_t bits){
    if (!(bits && !(bits & (bits-1))))
      return 0;
    return log2(bits) + 1;
  }

  int strip(int bits, int all){
    int v = bits & all;
    return v;
  }

  Leg* getLeg(int bits){
    int side = bits & SIDE::ALL;
    int leg  = bits & LEG::ALL;
    side >>= SIDE::MIN;
    leg  >>= LEG::MIN;
    side = findSetBit(side);
    leg =  findSetBit(leg);
    if(!side){
      printf("side input incorrect\n");
      return nullptr;
    }
    if(!leg){
      printf("leg  input incorrect\n");
      return nullptr;
    }
    return legs[3*side+leg%3];


    // int s_bits = bits&(SIDE::ALL);
    // int l_bits = bits&(LEG::ALL);

    // if(!s_bits || !l_bits)
    //   return nullptr;
    // print_bin("bits  ",bits);
    // print_bin("sbits ",s_bits);
    // print_bin("lbits ",l_bits);
    // printf("----------------------\n");
    // s_bits >>= SIDE::MIN;
    // l_bits >>= LEG::MIN;
    // print_bin("abits ",s_bits+l_bits);
    // printf("index: %d\n",s_bits+l_bits);
    // printf("\n\n");



    // printf("----------------------\n");
    // print_bin("mod3 ",bits%(1<<3));
    // print_bin("div3 ",bits/(1<<3));
    // printf("----------------------\n");
    // print_bin("mod2 ",bits%(1<<2));
    // print_bin("div2 ",bits/(1<<2));
    // printf("----------------------\n");
    // print_bin("moda ",bits%(1<<5));
    // print_bin("diva ",bits/(1<<5));
    // printf("\n\n");


  }

  // only input single bit, get single servo
  Servo& getServo(int bits){
    // maybe use strip since more modular?
    // int part = strip(bits, PART::ALL);
    // int leg_bits = strip(bits, (SIDE::ALL | LEG::ALL));

    int part = bits & PART::ALL;
    int leg_bits = bits & (SIDE::ALL | LEG::ALL);
    if(part == PART::INNER)
      return getLeg(leg_bits)->i;
    if(part == PART::MIDDLE)
      return getLeg(leg_bits)->m;
    if(part == PART::OUTER)
      return getLeg(leg_bits)->o;
    printf("Should not be here, PART input incorrect\n");
    // return 0;
  }

  template<typename Func>
  void runForServos(Func f, int bits){
    int side = strip(bits, SIDE::ALL);
    int leg  = strip(bits, LEG::ALL);
    int part = strip(bits, PART::ALL);

    // printf("inp  :");
    // print_bin(bits);
    // printf("side :");
    // print_bin(side);
    // printf("leg  :");
    // print_bin(leg);
    // printf("part :");
    // print_bin(part);

    if(!part || !leg || !side){
      printf("Missing inputs\n");
    }

    int bit_s = 1<<SIDE::MIN;
    int bit_l = 1<<LEG::MIN;
    int bit_p = 1<<PART::MIN;
    for(int s = 0; s < 2; s++){ // 2 sides
      for(int l = 0; l < 3; l++){ // 3 legs per side
        for(int p = 0; p < 3; p++){ // 3 servos per leg
          if(!(side & bit_s) || !(leg & bit_l) || !(part & bit_p)){
            continue;
          }
          int mbits = (side & bit_s) | (leg & bit_l) | (part & bit_p);
          // printf("mbits:");
          // print_bin(mbits);
          f(getServo(mbits));
          // getServo(mbits).set(angle);
          bit_p <<= 1;
        }
        bit_l <<= 1;
      }
      bit_s <<= 1;
    }
  }

  void setLimits(int min, int max, int bits){
    runForServos([&](Servo s){s.setLimits(min, max);}, bits);
  }

  // can input multiple bits for servo
  void setServos(int angle, int bits){
    runForServos([&](Servo s){s.set(angle);}, bits);
  }
};
