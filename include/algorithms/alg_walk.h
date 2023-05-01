#include "algorithms/basealgorithm.h"

namespace algo{

class Walk: public BaseAlgorithm{
public:
  Walk(Body* body):
  BaseAlgorithm(body)
  {

  }


  void init(int height){
    body->setXYZ(0, 0, height, LEG::ALL);
  }


  void step(){
    printf("Raise Right\n");
    body->moveXYZ(0, 0, -20, COMMON::TRI_RIGHT);
    usleep(1000'000);
    printf("\n");

    printf("Move Left\n");
    body->moveXYZ(-10, 0, 0, COMMON::TRI_LEFT);
    printf("Move Right\n");
    body->moveXYZ( 10, 0, 0, COMMON::TRI_RIGHT);
    usleep(5000'000);
    printf("\n");

    printf("Lower Right\n");
    body->moveXYZ(0, 0, 20, COMMON::TRI_RIGHT);
    usleep(1000'000);
    printf("\n");
    printf("Raise Left\n");
    body->moveXYZ(0, 0, -20, COMMON::TRI_LEFT);

    printf("Move Right\n");
    body->moveXYZ(-10, 0, 0, COMMON::TRI_RIGHT);
    printf("Move Left\n");
    body->moveXYZ( 10, 0, 0, COMMON::TRI_LEFT);
    usleep(5000'000);
    printf("\n");

    printf("Lower Left\n");
    body->moveXYZ(0, 0, 20, COMMON::TRI_LEFT);
    usleep(1000'000);
    printf("\n");

    printf("\n\n");
  }

};
}