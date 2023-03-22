#include "mleg.h"
#include "test_runs.h"


Global g;


// TODO: why can i initialize it here?
// MLeg leg(SIDE::LEFT, LEG::OTHER);
MLeg* leg;


void loop(){
  // test_DRIVE_TO_INPUT(leg);
  // test_DRIVE_TO_XYZ(leg);
  
  
  // test_LOOP_R_INCREASE(leg, 10, 45);
  test_LOOP_Y_INCREASE(leg, 60, 60, 10, 80-38);




  // test_INIT_MIN_CONST(leg);
  // test_INIT_MAX_CONST(leg);
  // test_INIT_MID_CONST(leg);
}

int main(){

  g.pwm.set_pwm_freq(50);

  leg = new MLeg(SIDE::LEFT, LEG::OTHER);
  // leg->set_debug(1);

  while(true){
    loop();
  }

  return 0;
}