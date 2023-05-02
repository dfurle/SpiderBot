#include "algorithms/basealgorithm.h"

namespace algo{

class Walk: public BaseAlgorithm{
public:
  Walk(Body* body):
  BaseAlgorithm(body)
  {

  }


  void init(int height){
    std::string tmp;
    std::cin >> tmp;
    body->setXYZ(0, 0, height, LEG::ALL);
    std::cin >> tmp;
  }


  void step(){
    std::string tmp;
    printf("Raise Right\n");
    body->moveXYZ(0, 0, -20, COMMON::TRI_RIGHT);
    std::cin >> tmp;
    printf("\n");

    printf("Move Left\n");
    body->moveXYZ(-10, 0, 0, COMMON::TRI_LEFT);
    std::cin >> tmp;
    printf("Move Right\n");
    body->moveXYZ( 10, 0, 0, COMMON::TRI_RIGHT);
    std::cin >> tmp;
    printf("\n");

    printf("Lower Right\n");
    body->moveXYZ(0, 0, 20, COMMON::TRI_RIGHT);
    std::cin >> tmp;
    printf("\n");
    printf("Raise Left\n");
    body->moveXYZ(0, 0, -20, COMMON::TRI_LEFT);
    std::cin >> tmp;

    printf("Move Right\n");
    body->moveXYZ(-10, 0, 0, COMMON::TRI_RIGHT);
    std::cin >> tmp;
    printf("Move Left\n");
    body->moveXYZ( 10, 0, 0, COMMON::TRI_LEFT);
    std::cin >> tmp;
    printf("\n");

    printf("Lower Left\n");
    body->moveXYZ(0, 0, 20, COMMON::TRI_LEFT);
    std::cin >> tmp;
    printf("\n");

    printf("\n\n");
  }

};
}