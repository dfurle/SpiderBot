#pragma once
#include "algorithms/basealgorithm.h"
#include "vec.h"

namespace algo{

class XYZ: public BaseAlgorithm{
public:
  std::map<std::string, int> index;

  XYZ(Body* body):
  BaseAlgorithm(body)
  {
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
    aa[0]  = body.legs[id_FL]->pos.x; aa[1]  = body.legs[id_FL]->pos.y;
    aa[2]  = body.legs[id_FR]->pos.x; aa[3]  = body.legs[id_FR]->pos.y;
    aa[4]  = body.legs[id_ML]->pos.x; aa[5]  = body.legs[id_ML]->pos.y;
    aa[6]  = body.legs[id_MR]->pos.x; aa[7]  = body.legs[id_MR]->pos.y;
    aa[8]  = body.legs[id_RL]->pos.x; aa[9]  = body.legs[id_RL]->pos.y;
    aa[10] = body.legs[id_RR]->pos.x; aa[11] = body.legs[id_RR]->pos.y;

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
  int get_input(int& x, int& y, int& z){
    printf("  [ fr mr rr fl ml rl trir tril lall ]\n");
    printf("     '+' -    prefix: append to   current selection\n");
    printf("     '-' -    prefix: remove from current selection\n");
    printf("         - no prefix: override    current selection\n");
    printf("     '# #' - number to set 'x y' position\n");
    std::string in;
    std::getline(std::cin, in);

    try{
      int first = in.find(' ');
      int second = in.find(' ', first+1);
      int third = in.find(' ', second+1);
      std::string m = in.substr(0,first);
      std::string str_x, str_y, str_z;
      if(m == "m"){
        std::string str_x = in.substr(first,second);
        std::string str_y = in.substr(second,third);
        std::string str_z = in.substr(third);
        x = std::stoi(str_x);
        y = std::stoi(str_y);
        z = std::stoi(str_z);
        return 2;
      }else{
        std::string str_x = in.substr(0,first);
        std::string str_y = in.substr(first,second);
        std::string str_z = in.substr(second);
        x = std::stoi(str_x);
        y = std::stoi(str_y);
        z = std::stoi(str_z);
        return 1;
      }
    } catch(std::invalid_argument& e){
    } catch(std::out_of_range& e){}


    this->bits = g.toBits(in, this->bits, index); // TODO: add check for properness
    return 0;
  }

  void step(){
    printf("\n\n\n\n\n\n");
    int x, y, z;

    print_menu(*body);
    int in = get_input(x, y, z);
    if(in){
      if(this->bits){
        if(in == 1)
          body->setXYZ(Vec3f(x,y,z), this->bits);
        else if(in == 2)
          body->moveXYZ(Vec3f(x,y,z), this->bits);
      }else
        printf("bits not set\n");
    }
  }
};


}