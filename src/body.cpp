#include "body.h"
#include <sys/time.h>

Body::Body(){

}


// WARNING, CAUSES MEMORY LEAK WHEN RAN MULTIPLE TIMES!!!
void Body::initialize(){
  this->plane_rotation = Vec3f::zero();


  legs.resize(6);
  legs[id_FR] = new Leg(LEG::FRONT_RIGHT,  &plane_rotation);
  legs[id_MR] = new Leg(LEG::MIDDLE_RIGHT, &plane_rotation);
  legs[id_RR] = new Leg(LEG::REAR_RIGHT,   &plane_rotation);

  legs[id_FL] = new Leg(LEG::FRONT_LEFT,  &plane_rotation);
  legs[id_ML] = new Leg(LEG::MIDDLE_LEFT, &plane_rotation);
  legs[id_RL] = new Leg(LEG::REAR_LEFT,   &plane_rotation);

  int si_x = 100; // 100
  int si_y = 100; // 100
  int mi = 130;


  // legs[id_FR]->set_offsets(-45,  si_x, si_y);
  // legs[id_MR]->set_offsets(-90,  0, mi);
  // legs[id_RR]->set_offsets(-135, -si_x, si_y);

  // legs[id_FL]->set_offsets(45,  si_x, si_y, true);
  // legs[id_ML]->set_offsets(90,  0, mi, true);
  // legs[id_RL]->set_offsets(135, -si_x, si_y, true);

  legs[id_FR]->set_offsets(-45,  Vec3f( 70, 55, 0), Vec3f(si_x, si_y, 0));
  legs[id_MR]->set_offsets(-90,  Vec3f(  0, 85, 0), Vec3f(0, mi, 0));
  legs[id_RR]->set_offsets(-135, Vec3f(-70, 55, 0), Vec3f(-si_x, si_y, 0));

  legs[id_FL]->set_offsets(45,  Vec3f( 70, -55, 0), Vec3f(si_x, si_y, 0), true);
  legs[id_ML]->set_offsets(90,  Vec3f(  0, -85, 0), Vec3f(0, mi, 0), true);
  legs[id_RL]->set_offsets(135, Vec3f(-70, -55, 0), Vec3f(-si_x, si_y, 0), true);
}

void Body::set_plane(Vec3f plane_rotation){
  this->plane_rotation = plane_rotation * DEG_TO_RAD;
}


Leg* Body::getLeg(int bits){
  int leg  = bits & LEG::ALL;
  leg  >>= LEG::MIN;
  leg =  g.findSetBit(leg);
  if(!leg){
    printf("leg  input incorrect\n");
    return nullptr;
  }
  leg--;
  return legs[leg%6]; // shouldnt overflow but just in case...
}

// only input single bit, get single servo
Servo* Body::getServo(int bits){
  // maybe use strip since more modular?
  // int part = strip(bits, PART::ALL);
  // int leg_bits = strip(bits, (SIDE::ALL | LEG::ALL));

  int part = bits & PART::ALL;
  if(part == PART::INNER)
    return &getLeg(bits)->i;
  if(part == PART::MIDDLE)
    return &getLeg(bits)->m;
  if(part == PART::OUTER)
    return &getLeg(bits)->o;
  printf("Should not be here, PART input incorrect\n");
  return nullptr;
}


template<typename Func>
void Body::runForServos(Func f, int bits){
  int leg  = g.strip(bits, LEG::ALL);
  int part = g.strip(bits, PART::ALL);

  if(!part || !leg){
    printf("Missing inputs\n");
  }

  int bit_l = 1<<LEG::MIN;
  for(int l = 0; l < 6; l++){ // 6 legs
    int bit_p = 1<<PART::MIN;
    for(int p = 0; p < 3; p++){ // 3 servos per leg
      int mbits = (leg & bit_l) | (part & bit_p);
      if((leg & bit_l) && (part & bit_p)){
        f(getServo(mbits));
      }
      bit_p <<= 1;
    }
    bit_l <<= 1;
  }
}


template<typename Func>
void Body::runForLegs(Func f, int bits){
  int leg  = g.strip(bits, LEG::ALL);

  if(!leg){
    printf("Missing inputs\n");
  }

  int bit_l = 1<<LEG::MIN;
  for(int l = 0; l < 6; l++){ // 6 legs
    if(leg & bit_l){
      f(getLeg(leg & bit_l));
    }
    bit_l <<= 1;
  }
}


void Body::setLimits(int min, int max, int bits){
  runForServos([&](Servo* s){s->setLimits(min, max);}, bits);
}

// can input multiple bits for servo
void Body::setServos(int angle, int bits){
  runForServos([&](Servo* s){s->set(angle);}, bits);
}

void Body::setXYZ(Vec3f pos, int leg_bits){
  runForLegs([&](Leg* l){l->set_cartesian(pos);}, leg_bits);
}

void Body::moveXYZ(Vec3f pos, int leg_bits){
  runForLegs([&](Leg* l){
    l->move_cartesian(pos);
    }, leg_bits);
}

// May not be well optimized... but should work?
void Body::moveXYZ_speed(Vec3f target, float time_to_complete, int leg_bits){
  float current_time = 0;
  Vec3f delta = target * (10. / time_to_complete); // get delta per iteration
  
  // while(current_time < time_to_complete){
  //   moveXYZ(delta, leg_bits);
  //   usleep(100e3); // 100ms
  //   current_time += 100.; // experiment, maybe it doesnt sleep for 10ms or something?
  // }


  struct timeval  tv1, tv2;
  while(current_time < time_to_complete){
    moveXYZ(delta, leg_bits);
    gettimeofday(&tv1, NULL);
    float timePassed = 0;
    // Very jank code to make the most precise timing... sometimes it takes too long in the sleep/ or idk and slows down the movement
    do{
      usleep(1);
      gettimeofday(&tv2, NULL);
      timePassed = (float) (tv2.tv_usec - tv1.tv_usec) + (float) (tv2.tv_sec - tv1.tv_sec) * 1e6;
    }while(timePassed < 10e3); // 10ms
    current_time += 10.; // experiment, maybe it doesnt sleep for 10ms or something?
  }
}

// void Body::moveXYZ_speed(Vec3f pos, float time_to_complete, int leg_bits){
//   runForLegs([&](Leg* l){l->move_cartesian(pos);}, leg_bits);
// }

void Body::setScaling(float scaling, int bits){
  runForServos([&](Servo* s){s->scaling = scaling;}, bits);
}