#ifndef TESTRUNS_H
#define TESTRUNS_H

#include "mservo.h"
#include "mleg.h"

void test_INIT_TO_LIMITS(){
  Serial.println("INIT TO LIMITS");
  for(int j = 0; j < 16; j++){
    if(j%4 == 0) // INNER
      // pwm.setPWM(j,0,LMID);
      pwm.setPWM(j,0,(LMAX-LMIN)*0.5);
    else if(j%4 == 1) // MIDDLE
      pwm.setPWM(j,0,LMAX);
    else if(j%4 == 2) // OUTER
      pwm.setPWM(j,0,LMIN);
  }
}

// Drives specific servo to inputted angle by user
// TODO: Make better
void test_DRIVE_TO_INPUT(MLeg* leg){
  while(Serial.available() == 0){}

  int which = Serial.parseInt();
  int pos = Serial.parseInt();

  if(which == -1){
    leg->i.set(0);
    leg->m.set(0);
    leg->o.set(0);
  } else if(which == 0)
    leg->i.set(pos);
  else if(which == 1)
    leg->m.set(pos);
  else if(which == 2)
    leg->o.set(pos);

  delay(1000);
}


// Drives specific servo to cartesian coords by user
// TODO: Make better
void test_DRIVE_TO_XYZ(MLeg* leg){
  while(Serial.available() == 0){}

  int x = Serial.parseInt();
  int y = Serial.parseInt();
  int z = Serial.parseInt();

  leg->set_catesian(x,y,z);
  delay(1000);
}

void test_LOOP_R_INCREASE(MLeg* leg, long speed_delay = 30, float height = 45){
  int min = 1;
  int max = sqrt((MID_L+OUT_L)*(MID_L+OUT_L)-(height*height)) + INN_L - 1;
  for(int j = min; j <= max; j+=2){
    leg->test_set_r(j, height);
    delay(speed_delay);
  }
  delay(100);
  for(int j = max; j >= min; j-=2){
    leg->test_set_r(j, height);
    delay(speed_delay);
  }
  delay(100);
}

void test_LOOP_Y_INCREASE(MLeg* leg, float x = 70, long speed_delay = 30, float height = 45){
  float min = -80;
  float max =  80;
  for(float y = min; y <= max; y+=2){
    leg->set_catesian(x, y, height);
    delay(speed_delay);
  }
  delay(100);
  for(float y = max; y >= min; y-=2){
    leg->set_catesian(x, y, height);
    delay(speed_delay);
  }
  delay(100);
}

void test_LOOP_90_DEG(MLeg* leg){
  leg->i.set(0);
  leg->m.set(0);
  leg->o.set(0);
  delay(10000);

  leg->i.set(0);
  leg->m.set(90);
  leg->o.set(0);
  delay(10000);

  leg->i.set(0);
  leg->m.set(0);
  leg->o.set(0);
  delay(10000);

  leg->i.set(0);
  leg->m.set(0);
  leg->o.set(90);
  delay(10000);
}

// TODO: make all legs run the same test_###() code
void test_DO_ALL(){

}

#endif