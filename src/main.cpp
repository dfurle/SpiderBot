// #include "leg.h"
#include "body.h"
#include "test_runs.h"

#include "algorithms/alg_setup.h"
#include "algorithms/alg_xyz.h"
#include "algorithms/alg_walk.h"
#include "algorithms/alg_joystick.h"


Global g;
void loop(algo::BaseAlgorithm* alg);

int main(){
  g.left.set_pwm_freq(50);
  g.right.set_pwm_freq(50);
  
  Body body;
  body.initialize();

  body.setLimits(45, 135, LEG::ALL | PART::INNER);
  body.setLimits(0, 160, LEG::ALL | PART::MIDDLE);
  body.setLimits(0, 180, LEG::ALL | PART::OUTER);

  body.setLimits(0, 150, LEG::FRONT_LEFT | PART::MIDDLE);
  body.setLimits(10, 180, LEG::REAR_RIGHT | PART::OUTER);

  // body.setScaling(160./155., LEG::FL | PART::OUTER);
  // body.setScaling(170./155., LEG::ML | PART::OUTER);
  // body.setScaling(165./155., LEG::RL | PART::OUTER);

  // algo::Setup* alg_setup = new algo::Setup(&body);
  // algo::XYZ*   alg_xyz   = new algo::XYZ(&body);
  algo::Walk*  alg_walk  = new algo::Walk(&body);
  // algo::JoystickMove* alg_joystick = new algo::JoystickMove(&body);
  // alg_joystick->init(100);

  // body.set_plane(Vec3f(-10, 0, 0));
  // body.set_plane(Vec3f(0, 0, 20));
  body.set_plane(Vec3f(0, 0, 0));
  alg_walk->init(100);

  while(true){
    // loop(alg_setup);
    // loop(alg_xyz);
    loop(alg_walk);
    // loop(alg_joystick);
  }

  return 0;
}


void loop(algo::BaseAlgorithm* alg){
  alg->step();

  // usleep(1'000'000'000);


  // test_DRIVE_TO_INPUT(body);
  // test_DRIVE_TO_XYZ(body.getLeg(SIDE::LEFT, LEG::FRONT));

  
  // body.setAll((PART) motor, pos);

  
  
  // test_LOOP_R_INCREASE(leg, 10, 45);
  // test_LOOP_Y_INCREASE(leg, 60, 60, 10, 80-38);




  // test_INIT_MIN_CONST(leg);
  // test_INIT_MAX_CONST(leg);
  // test_INIT_MID_CONST(leg);
}