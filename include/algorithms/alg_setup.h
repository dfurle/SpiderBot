#pragma once
#include "global.h"
#include "algorithms/basealgorithm.h"

namespace algo{

class Setup: public BaseAlgorithm{
public:
  bool adjustedAngle = true;
  std::map<std::string, int> index;

  Setup(){
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
  }

  void print_selection(int b){
    printf("Currently Editing:\n");
    printf("Right: (%5s) | (%6s) | (%5s)\n",(b & LEG::FR)?"FRONT":"",(b & LEG::MR)?"MIDDLE":"",(b & LEG::RR)?"BACK ":"");
    printf("Left : (%5s) | (%6s) | (%5s)\n",(b & LEG::FL)?"FRONT":"",(b & LEG::ML)?"MIDDLE":"",(b & LEG::RL)?"BACK ":"");
    printf("Parts: (%5s) | (%6s) | (%5s)\n",(b & PART::INNER)?"INNER":"",(b & PART::MIDDLE)?"MIDDLE":"",(b & PART::OUTER)?"OUTER":"");
    g.print_bin("bin",b);
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
    print_selection(this->bits);
    printf("\nStatus in (%s) form\n\n",(adjustedAngle?"Adjusted":"Raw"));

    std::vector<int> aa;
    aa.resize(18); // 2*3*3 = 18
    // TODO: fix this damn mess
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
    printf("  [ fr mr rr fl ml rl trir tril lall ]   [ i m o pall ]\n");
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
      this->bits = g.toBits(in, this->bits, index); // TODO: add check for properness
    }
    return false;
  }

  // Drives specific servo to inputted angle by user
  void step(){
    printf("\n\n\n\n\n\n");
    print_menu(*body);
    int angle = 0;
    if(get_input(angle)){
      if(this->bits)
        body->setServos(angle, this->bits);
      else
        printf("bits not set\n");
    }
  }
};

}