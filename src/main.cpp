// #include "mleg.h"
#include "body.h"
#include "test_runs.h"


Global g;


// TODO: why can i initialize it here?
// MLeg leg(SIDE::LEFT, LEG::OTHER);
// MLeg* leg;
Body body;


void loop(){
  // test_DRIVE_TO_INPUT(leg);
  // test_DRIVE_TO_XYZ(body.getLeg(SIDE::LEFT, LEG::FRONT));


  
  int motor;
  int pos;
  printf("Enter Motor ID and Degree: ");
  std::cin >> motor;
  std::cin >> pos;
  printf("Moving to %d %d\n",motor,pos);

  body.setAll((PART) motor, pos);

  
  
  // test_LOOP_R_INCREASE(leg, 10, 45);
  // test_LOOP_Y_INCREASE(leg, 60, 60, 10, 80-38);




  // test_INIT_MIN_CONST(leg);
  // test_INIT_MAX_CONST(leg);
  // test_INIT_MID_CONST(leg);
}

int main(){

  g.left.set_pwm_freq(50);
  g.right.set_pwm_freq(50);

  body.initialize();


  body.setAllLimits(45, 135, PART::INNER);
  body.setAllLimits(72, 162, PART::MIDDLE);
  body.setAllLimits(30, 180, PART::OUTER);


  //body.setLimits()



  // body.setLimits(45, 135, SIDE::LEFT, LEG::FRONT, PART::INNER);
  // body.setLimits(72, 162, SIDE::LEFT, LEG::FRONT, PART::MIDDLE);
  // body.setLimits(30, 180, SIDE::LEFT, LEG::FRONT, PART::OUTER);
  // leg = new MLeg(SIDE::LEFT, LEG::FRONT);
  // leg->set_debug(1);

  // leg->i.setLimits(0, 90);
  // leg->m.setLimits(45, 172);
  // leg->o.setLimits(0, 115);


  while(true){
    loop();
  }

  return 0;
}
