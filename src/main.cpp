// #include "leg.h"
#include "body.h"
#include "test_runs.h"


Global g;


// TODO: why can i initialize it here?
// Leg leg(SIDE::LEFT, LEG::OTHER);
// Leg* leg;


void loop(Body& body){
  test_DRIVE_TO_INPUT(body);
  // test_DRIVE_TO_XYZ(body.getLeg(SIDE::LEFT, LEG::FRONT));

  
  // body.setAll((PART) motor, pos);

  
  
  // test_LOOP_R_INCREASE(leg, 10, 45);
  // test_LOOP_Y_INCREASE(leg, 60, 60, 10, 80-38);




  // test_INIT_MIN_CONST(leg);
  // test_INIT_MAX_CONST(leg);
  // test_INIT_MID_CONST(leg);
}

int main(){
  Body body;

  g.left.set_pwm_freq(50);
  g.right.set_pwm_freq(50);

  body.initialize();

  // body.getLeg(SIDE::LEFT | LEG::MIDDLE | PART::ALL);
  // for(int i = 0; i < 1<<5; i++){
  //   // body.getLeg(i);
  //   // body.setServos(0, SIDE::LEFT | LEG::MIDDLE | PART::ALL);
  // }


  body.setLimits(45, 135, SIDE::ALL | LEG::ALL | PART::INNER);
  body.setLimits(72, 162, SIDE::ALL | LEG::ALL | PART::MIDDLE);
  body.setLimits(30, 180, SIDE::ALL | LEG::ALL | PART::OUTER);

  // body.setServos(0, SIDE::LEFT | LEG::MIDDLE | PART::ALL);



  // body.setLimits(45, 135, SIDE::LEFT, LEG::FRONT, PART::INNER);
  // body.setLimits(72, 162, SIDE::LEFT, LEG::FRONT, PART::MIDDLE);
  // body.setLimits(30, 180, SIDE::LEFT, LEG::FRONT, PART::OUTER);
  // leg = new Leg(SIDE::LEFT, LEG::FRONT);
  // leg->set_debug(1);

  // leg->i.setLimits(0, 90);
  // leg->m.setLimits(45, 172);
  // leg->o.setLimits(0, 115);


  while(true){
    loop(body);
  }

  return 0;
}
