#include "algorithms/basealgorithm.h"
#include "vec.h"

namespace algo{

class Walk: public BaseAlgorithm{
public:

  int raise_height = 50;
  int move_dist = 50;

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
    body->moveXYZ(Vec3f::up(height), LEG::ALL);
    std::getline(std::cin, tmp);
  }


  void step(){
    std::string tmp;
    printf("Raise Right\n");
    body->moveXYZ(Vec3f::down(raise_height), COMMON::TRI_RIGHT);
    printf("\n");

    printf("Move Left&Right\n");
    body->moveXYZ(Vec3f::backward(move_dist), COMMON::TRI_LEFT);
    body->moveXYZ(Vec3f::forward(move_dist), COMMON::TRI_RIGHT);
    printf("\n");

    printf("Lower Right\n");
    body->moveXYZ(Vec3f::up(raise_height), COMMON::TRI_RIGHT);
    printf("\n");
    printf("Raise Left\n");
    body->moveXYZ(Vec3f::down(raise_height), COMMON::TRI_LEFT);

    printf("Move Right&Left\n");
    body->moveXYZ(Vec3f::backward(move_dist), COMMON::TRI_RIGHT);
    body->moveXYZ(Vec3f::forward(move_dist), COMMON::TRI_LEFT);
    printf("\n");

    printf("Lower Left\n");
    body->moveXYZ(Vec3f::up(raise_height), COMMON::TRI_LEFT);
    std::getline(std::cin, tmp);
    printf("\n");

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