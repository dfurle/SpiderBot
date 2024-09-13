#include "algorithms/basealgorithm.h"
#include "vec.h"
#include <chrono>

namespace algo{

class Walk: public BaseAlgorithm{
public:

  int raise_height = 50;
  int move_dist = 60; // 50
  float time_to_move = 200; // 200
  float angle = 0 * DEG_TO_RAD;


  int max_steps = 1;

  Walk(Body* body):
  BaseAlgorithm(body)
  {

  }


  void init(int height){
    std::vector<Vec3f> pts = {Vec3f(0,0,100), Vec3f(0,-60,100), Vec3f(0,0,0), Vec3f(0,60,100)};

    body->runForLegs([&](Leg* l){l->set_loop(pts);}, LEG::ALL);

    std::string tmp;
    std::getline(std::cin, tmp);
    body->setXYZ(Vec3f::zero(), LEG::ALL);
    std::getline(std::cin, tmp);
    // body->moveXYZ(Vec3f::backward(move_dist).rotate(angle, 'z'), COMMON::TRI_RIGHT);
    // std::getline(std::cin, tmp);
    body->moveXYZ_speed(Vec3f::up(height).rotate(angle, 'z'), time_to_move, LEG::ALL);
    std::getline(std::cin, tmp);
  }

  void step(){
    std::string tmp;
    printf("Starting Algorithm\n");
    std::getline(std::cin, tmp);

    float current_time = 0.0f;
    float time_to_complete = 500;

    while(current_time < time_to_complete){
      body->updateAll(current_time / time_to_complete);
      auto start = std::chrono::high_resolution_clock::now();
      float timePassed = 0;
      do{
        usleep(1);
        auto end = std::chrono::high_resolution_clock::now();
        timePassed = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
      }while(timePassed < 10e3); // 10ms
      printf("timePassed %.3f -- %.0f/%.0f -> t=%f\n", timePassed / 1e3, current_time, time_to_complete, current_time/time_to_complete);
      current_time += (timePassed / 1e3); // experiment, maybe it doesnt sleep for 10ms or something?
    }
    body->updateAll(1);
  }

  // void step(){
  //   std::string tmp;
  //   printf("Raise Right\n");
  //   body->moveXYZ_speed(Vec3f::down(raise_height).rotate(angle, 'z'), time_to_move, COMMON::TRI_RIGHT);
  //   printf("\n");

  //   printf("Move Right\n");
  //   body->setXYZ_speed(Vec3f::forward(move_dist).rotate(angle, 'z'), 2*time_to_move, COMMON::TRI_RIGHT, true);
  //   printf("\n");

  //   printf("Lower Right\n");
  //   body->moveXYZ_speed(Vec3f::up(raise_height).rotate(angle, 'z'), time_to_move, COMMON::TRI_RIGHT);
  //   printf("\n");

  //   printf("Move Right&Left\n");
  //   body->moveXYZ_speed(Vec3f::backward(move_dist).rotate(angle, 'z'), time_to_move, LEG::ALL);
  //   printf("\n");

  //   printf("Raise Left\n");
  //   body->moveXYZ_speed(Vec3f::down(raise_height).rotate(angle, 'z'), time_to_move, COMMON::TRI_LEFT);
  //   printf("\n");

  //   printf("Move Left\n");
  //   body->setXYZ_speed(Vec3f::forward(move_dist).rotate(angle, 'z'), 2*time_to_move, COMMON::TRI_LEFT, true);
  //   printf("\n");

  //   printf("Lower Left\n");
  //   body->moveXYZ_speed(Vec3f::up(raise_height).rotate(angle, 'z'), time_to_move, COMMON::TRI_LEFT);
  //   printf("\n");

  //   printf("Move Right&Left\n");
  //   body->moveXYZ_speed(Vec3f::backward(move_dist).rotate(angle, 'z'), time_to_move, LEG::ALL);
  //   printf("\n");

  //   if(max_steps-- <= 0){
  //     std::getline(std::cin, tmp);
  //     try{
  //       int a = std::stoi(tmp);
  //       angle = a * DEG_TO_RAD;
  //     } catch(std::invalid_argument& e){
  //     } catch(...){
  //       printf("Unknown error\n");
  //     }
  //   }

  //   printf("\n\n");
  // }


  // void step(){
  //   std::string tmp;
  //   printf("Raise Right\n");
  //   body->moveXYZ_speed(Vec3f::down(raise_height).rotate(angle, 'z'), time_to_move, COMMON::TRI_RIGHT);
  //   printf("\n");

  //   printf("Move Left&Right\n");
  //   body->moveXYZ_speed(Vec3f::backward(move_dist).rotate(angle, 'z'), time_to_move, COMMON::TRI_LEFT);
  //   body->moveXYZ_speed(Vec3f::forward(move_dist).rotate(angle, 'z'), time_to_move, COMMON::TRI_RIGHT);
  //   printf("\n");

  //   printf("Lower Right\n");
  //   body->moveXYZ_speed(Vec3f::up(raise_height).rotate(angle, 'z'), time_to_move, COMMON::TRI_RIGHT);
  //   printf("\n");
  //   printf("Raise Left\n");
  //   body->moveXYZ_speed(Vec3f::down(raise_height).rotate(angle, 'z'), time_to_move, COMMON::TRI_LEFT);

  //   printf("Move Right&Left\n");
  //   body->moveXYZ_speed(Vec3f::backward(move_dist).rotate(angle, 'z'), time_to_move, COMMON::TRI_RIGHT);
  //   body->moveXYZ_speed(Vec3f::forward(move_dist).rotate(angle, 'z'), time_to_move, COMMON::TRI_LEFT);
  //   printf("\n");

  //   printf("Lower Left\n");
  //   body->moveXYZ_speed(Vec3f::up(raise_height).rotate(angle, 'z'), time_to_move, COMMON::TRI_LEFT);
  //   printf("\n");

  //   if(max_steps-- <= 0){
  //     std::getline(std::cin, tmp);
  //     try{
  //       int a = std::stoi(tmp);
  //       angle = a * DEG_TO_RAD;
  //     } catch(std::invalid_argument& e){
  //     } catch(...){
  //       printf("Unknown error\n");
  //     }
  //   }

  //   printf("\n\n");
  // }


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