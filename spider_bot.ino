#include "mservo.h"
#include "test_runs.h"

// TODO: why can i initialize it here?
// MLeg leg(SIDE::LEFT, LEG::OTHER);
MLeg* leg;


void loop(){
  // test_LOOP_R_INCREASE_SMOOTH(leg, 20, 80);
  // test_DRIVE_TO_INPUT(leg);
  // test_INIT_TO_LIMITS();
  // test_DRIVE_TO_INPUT(leg);
  // test_DRIVE_TO_XYZ(leg);
  test_LOOP_Y_INCREASE(leg);
}

void setup(){
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(50);

  Serial.begin(9600);
  Serial.println("Setup");

  leg = new MLeg(SIDE::LEFT, LEG::OTHER);
  // leg->set_debug(1);
}