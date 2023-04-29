// #include "leg.h"
#include "body.h"
#include "test_runs.h"

#include "algorithms/alg_setup.h"
#include "algorithms/alg_xyz.h"


Global g;
void loop(algo::BaseAlgorithm* alg);

int main(){
  Body body;

  algo::Setup* alg_setup = new algo::Setup();
  algo::XYZ*   alg_xyz   = new algo::XYZ();

  g.left.set_pwm_freq(50);
  g.right.set_pwm_freq(50);

  body.initialize();

  body.setLimits(45, 135, LEG::ALL | PART::INNER);
  body.setLimits(0, 160, LEG::ALL | PART::MIDDLE);
  body.setLimits(0, 180, LEG::ALL | PART::OUTER);

  alg_setup->set_body(&body);
  alg_xyz  ->set_body(&body);

  while(true){
    // loop(alg_setup);
    loop(alg_xyz);
  }

  return 0;
}



void loop(algo::BaseAlgorithm* alg){
  alg->step();


  // test_DRIVE_TO_INPUT(body);
  // test_DRIVE_TO_XYZ(body.getLeg(SIDE::LEFT, LEG::FRONT));

  
  // body.setAll((PART) motor, pos);

  
  
  // test_LOOP_R_INCREASE(leg, 10, 45);
  // test_LOOP_Y_INCREASE(leg, 60, 60, 10, 80-38);




  // test_INIT_MIN_CONST(leg);
  // test_INIT_MAX_CONST(leg);
  // test_INIT_MID_CONST(leg);
}