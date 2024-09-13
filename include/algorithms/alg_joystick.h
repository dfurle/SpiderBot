#include "algorithms/basealgorithm.h"
#include "vec.h"

namespace algo{

// to simulate joystick movement, future get input from terminal to change direction and force
class JoystickMove: public BaseAlgorithm{
public:

  int raise_height = 50;
  int max_move_dist = 50;

  // assume X forward, Y side, Z up down
  // only 2d, ignore Z for now
  // [0,1] range
  Vec3f joystick;

  JoystickMove(Body* body):
  BaseAlgorithm(body)
  {
    float angle = 20 * DEG_TO_RAD;
    float force = 0.5;

    joystick.x = cos(angle);
    joystick.y = sin(angle);

    joystick = joystick.norm() * force;
  }


  void init(int height){
    std::string tmp;
    std::getline(std::cin, tmp);
    body->setXYZ(Vec3f::zero(), LEG::ALL);
    // std::getline(std::cin, tmp);
    // body->moveXYZ(-joystick * max_move_dist, COMMON::TRI_RIGHT);
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
    body->moveXYZ(-joystick * max_move_dist, COMMON::TRI_LEFT);
    body->moveXYZ(joystick * max_move_dist, COMMON::TRI_RIGHT);
    printf("\n");

    printf("Lower Right\n");
    body->moveXYZ(Vec3f::up(raise_height), COMMON::TRI_RIGHT);
    printf("\n");
    printf("Raise Left\n");
    body->moveXYZ(Vec3f::down(raise_height), COMMON::TRI_LEFT);

    printf("Move Right&Left\n");
    body->moveXYZ(-joystick * max_move_dist, COMMON::TRI_RIGHT);
    body->moveXYZ(joystick * max_move_dist, COMMON::TRI_LEFT);
    printf("\n");

    printf("Lower Left\n");
    body->moveXYZ(Vec3f::up(raise_height), COMMON::TRI_LEFT);
    std::getline(std::cin, tmp);
    try{
      int a = std::stoi(tmp);
      joystick.x = cos(a);
      joystick.y = sin(a);

      joystick = joystick.norm() * 0.5;
    } catch(std::invalid_argument& e){
    } catch(...){
      printf("Unknown error\n");
    }
    printf("\n");

    printf("\n\n");
  }

};
}