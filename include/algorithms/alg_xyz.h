#pragma once
#include "algorithms/basealgorithm.h"

namespace algo{

class XYZ: public BaseAlgorithm{
public:
  std::map<std::string, int> index;

  XYZ(){
    index["FR"] = LEG::FR;
    index["MR"] = LEG::MR;
    index["RR"] = LEG::RR;
    index["FL"] = LEG::FL;
    index["ML"] = LEG::ML;
    index["RL"] = LEG::RL;
    index["LALL"] = LEG::ALL;
    index["TRIR"] = COMMON::TRI_RIGHT;
    index["TRIL"] = COMMON::TRI_LEFT;
  }

  void print_menu(Body& body){
    int b = this->bits;
    printf("Currently Editing:\n");
    printf("Right: (%5s) | (%6s) | (%5s)\n",(b & LEG::FR)?"FRONT":"",(b & LEG::MR)?"MIDDLE":"",(b & LEG::RR)?"BACK ":"");
    printf("Left : (%5s) | (%6s) | (%5s)\n",(b & LEG::FL)?"FRONT":"",(b & LEG::ML)?"MIDDLE":"",(b & LEG::RL)?"BACK ":"");
    g.print_bin("bin",b);

    std::vector<float> aa;
    aa.resize(12); // 6*2 = 12
    // TODO: fix this damn mess
    aa[0]  = body.legs[id_FL]->x; aa[1]  = body.legs[id_FL]->y;
    aa[2]  = body.legs[id_FR]->x; aa[3]  = body.legs[id_FR]->y;
    aa[4]  = body.legs[id_ML]->x; aa[5]  = body.legs[id_ML]->y;
    aa[6]  = body.legs[id_MR]->x; aa[7]  = body.legs[id_MR]->y;
    aa[8]  = body.legs[id_RL]->x; aa[9]  = body.legs[id_RL]->y;
    aa[10] = body.legs[id_RR]->x; aa[11] = body.legs[id_RR]->y;

    auto it = aa.begin();
    printf("  .     ┌─────┐  ┌─────────┐  ┌─────┐   \n");
    printf("  .     │     └──┤         ├──┘     │   \n");
    printf("  .       %03.0f,%03.0f│         │%03.0f,%03.0f      \n",*(it++),*(it++),*(it++),*(it++));
    printf("  .     ┌─────┐  │         │  ┌─────┐   \n");
    printf("  .     │     └──┤         ├──┘     │   \n");
    printf("  .       %03.0f,%03.0f│         │%03.0f,%03.0f     \n",*(it++),*(it++),*(it++),*(it++));
    printf("  .     ┌─────┐  │         │  ┌─────┐   \n");
    printf("  .     │     └──┤         ├──┘     │   \n");
    printf("  .       %03.0f,%03.0f└─────────┘%03.0f,%03.0f     \n",*(it++),*(it++),*(it++),*(it++));
    printf("\n");
  }

  // returns if angle is returned
  bool get_input(int& x, int& y){
    printf("  [ fr mr rr fl ml rl trir tril lall ]\n");
    printf("     '+' -    prefix: append to   current selection\n");
    printf("     '-' -    prefix: remove from current selection\n");
    printf("         - no prefix: override    current selection\n");
    printf("     '# #' - number to set 'x y' position\n");
    std::string in;
    std::getline(std::cin, in);

    try{
      std::string str_x = in.substr(0,in.find(' '));
      std::string str_y = in.substr(in.find(' '));
      x = std::stoi(str_x);
      y = std::stoi(str_y);
      return true;
    } catch(std::invalid_argument& e){
    } catch(std::out_of_range& e){}


    this->bits = g.toBits(in, this->bits, index); // TODO: add check for properness
    return false;
  }

  void step(){
    printf("\n\n\n\n\n\n");
    int x, y, z;
    z = 30;

    print_menu(*body);
    if(get_input(x, y)){
      if(this->bits)
        body->setXYZ(x, y, z, this->bits);
      else
        printf("bits not set\n");
    }
  }
};


}