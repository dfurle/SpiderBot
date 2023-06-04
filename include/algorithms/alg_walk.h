#include "algorithms/basealgorithm.h"
#include "vec.h"

namespace algo{

class Walk: public BaseAlgorithm{
public:

  int raise_height = 50;
  int move_dist = 50;
  float time_to_move = 100;

  int max_steps = 3;

  Walk(Body* body):
  BaseAlgorithm(body)
  {

  }


  void init(int height){
    std::string tmp;
    std::getline(std::cin, tmp);
    body->setXYZ(Vec3f::zero(), LEG::ALL);
    std::getline(std::cin, tmp);
    body->moveXYZ(Vec3f::backward(move_dist), COMMON::TRI_RIGHT);
    std::getline(std::cin, tmp);
    body->moveXYZ_speed(Vec3f::up(height), time_to_move, LEG::ALL);
    std::getline(std::cin, tmp);
  }


  void step(){
    std::string tmp;
    printf("Raise Right\n");
    body->moveXYZ_speed(Vec3f::down(raise_height), time_to_move, COMMON::TRI_RIGHT);
    printf("\n");

    printf("Move Left&Right\n");
    body->moveXYZ_speed(Vec3f::backward(move_dist), time_to_move, COMMON::TRI_LEFT);
    body->moveXYZ_speed(Vec3f::forward(move_dist), time_to_move, COMMON::TRI_RIGHT);
    printf("\n");

    printf("Lower Right\n");
    body->moveXYZ_speed(Vec3f::up(raise_height), time_to_move, COMMON::TRI_RIGHT);
    printf("\n");
    printf("Raise Left\n");
    body->moveXYZ_speed(Vec3f::down(raise_height), time_to_move, COMMON::TRI_LEFT);

    printf("Move Right&Left\n");
    body->moveXYZ_speed(Vec3f::backward(move_dist), time_to_move, COMMON::TRI_RIGHT);
    body->moveXYZ_speed(Vec3f::forward(move_dist), time_to_move, COMMON::TRI_LEFT);
    printf("\n");

    printf("Lower Left\n");
    body->moveXYZ_speed(Vec3f::up(raise_height), time_to_move, COMMON::TRI_LEFT);
    printf("\n");

    if(max_steps-- <= 0){
      std::getline(std::cin, tmp);
    }

    printf("\n\n");
  }


  // void step(){
  //   std::string tmp;
  //   printf("Raise Right\n");
  //   body->moveXYZ(0, 0, -raise_height, COMMON::TRI_RIGHT);
  //   std::getline(std::cin, tmp);
  //   printf("\n");

  //   printf("Move Left&Right\n");
  //   body->moveXYZ(-move_dist, 0, 0, COMMON::TRI_LEFT);
  //   body->moveXYZ( move_dist, 0, 0, COMMON::TRI_RIGHT);
  //   std::getline(std::cin, tmp);
  //   printf("\n");

  //   printf("Lower Right\n");
  //   body->moveXYZ(0, 0, raise_height, COMMON::TRI_RIGHT);
  //   std::getline(std::cin, tmp);
  //   printf("\n");
  //   printf("Raise Left\n");
  //   body->moveXYZ(0, 0, -raise_height, COMMON::TRI_LEFT);
  //   std::getline(std::cin, tmp);

  //   printf("Move Right&Left\n");
  //   body->moveXYZ(-move_dist, 0, 0, COMMON::TRI_RIGHT);
  //   body->moveXYZ( move_dist, 0, 0, COMMON::TRI_LEFT);
  //   std::getline(std::cin, tmp);
  //   printf("\n");

  //   printf("Lower Left\n");
  //   body->moveXYZ(0, 0, raise_height, COMMON::TRI_LEFT);
  //   std::getline(std::cin, tmp);
  //   printf("\n");

  //   printf("\n\n");
  // }

};
}