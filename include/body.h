#pragma once
#include "mleg.h"
#include "global.h"

class Body{
public:

  MLeg* legs[2][3];

  Body(){

  }

  // WARNING DO NOT RUN MULTIPLE TIMES, MEMORY LEAK WILL HAPPEN!!!
  void initialize(){
    legs[0][0] = new MLeg(SIDE::LEFT, LEG::FRONT);
    legs[0][1] = new MLeg(SIDE::LEFT, LEG::MIDDLE);
    legs[0][2] = new MLeg(SIDE::LEFT, LEG::BACK);

    legs[1][0] = new MLeg(SIDE::RIGHT, LEG::FRONT);
    legs[1][1] = new MLeg(SIDE::RIGHT, LEG::MIDDLE);
    legs[1][2] = new MLeg(SIDE::RIGHT, LEG::BACK);
  }

  void setAllLimits(int low, int high, PART part){
    if(part == PART::INNER){
      getLeg(SIDE::LEFT,  LEG::FRONT )->i.setLimits(low, high);
      getLeg(SIDE::LEFT,  LEG::MIDDLE)->i.setLimits(low, high);
      getLeg(SIDE::LEFT,  LEG::BACK  )->i.setLimits(low, high);
      getLeg(SIDE::RIGHT, LEG::FRONT )->i.setLimits(low, high);
      getLeg(SIDE::RIGHT, LEG::MIDDLE)->i.setLimits(low, high);
      getLeg(SIDE::RIGHT, LEG::BACK  )->i.setLimits(low, high);
    } else if(part == PART::MIDDLE){
      getLeg(SIDE::LEFT,  LEG::FRONT )->m.setLimits(low, high);
      getLeg(SIDE::LEFT,  LEG::MIDDLE)->m.setLimits(low, high);
      getLeg(SIDE::LEFT,  LEG::BACK  )->m.setLimits(low, high);
      getLeg(SIDE::RIGHT, LEG::FRONT )->m.setLimits(low, high);
      getLeg(SIDE::RIGHT, LEG::MIDDLE)->m.setLimits(low, high);
      getLeg(SIDE::RIGHT, LEG::BACK  )->m.setLimits(low, high);
    } else if(part == PART::OUTER){
      getLeg(SIDE::LEFT,  LEG::FRONT )->o.setLimits(low, high);
      getLeg(SIDE::LEFT,  LEG::MIDDLE)->o.setLimits(low, high);
      getLeg(SIDE::LEFT,  LEG::BACK  )->o.setLimits(low, high);
      getLeg(SIDE::RIGHT, LEG::FRONT )->o.setLimits(low, high);
      getLeg(SIDE::RIGHT, LEG::MIDDLE)->o.setLimits(low, high);
      getLeg(SIDE::RIGHT, LEG::BACK  )->o.setLimits(low, high);
    }
  }

  void setLimits(int low, int high, SIDE side, LEG leg, PART part){
    if(part == PART::INNER){
      getLeg(side, leg)->i.setLimits(low, high);
    } else if(part == PART::MIDDLE){
      getLeg(side, leg)->m.setLimits(low, high);
    } else if(part == PART::OUTER){
      getLeg(side, leg)->o.setLimits(low, high);
    }
  }

  MLeg* getLeg(SIDE side, LEG leg){
    return legs[int(side)][int(leg)];
  }

  void setAll(PART part, int angle){
    if(part == PART::INNER){
      getLeg(SIDE::LEFT,  LEG::FRONT )->i.set(angle);
      getLeg(SIDE::LEFT,  LEG::MIDDLE)->i.set(angle);
      getLeg(SIDE::LEFT,  LEG::BACK  )->i.set(angle);
      getLeg(SIDE::RIGHT, LEG::FRONT )->i.set(angle);
      getLeg(SIDE::RIGHT, LEG::MIDDLE)->i.set(angle);
      getLeg(SIDE::RIGHT, LEG::BACK  )->i.set(angle);
    } else if(part == PART::MIDDLE){
      getLeg(SIDE::LEFT,  LEG::FRONT )->m.set(angle);
      getLeg(SIDE::LEFT,  LEG::MIDDLE)->m.set(angle);
      getLeg(SIDE::LEFT,  LEG::BACK  )->m.set(angle);
      getLeg(SIDE::RIGHT, LEG::FRONT )->m.set(angle);
      getLeg(SIDE::RIGHT, LEG::MIDDLE)->m.set(angle);
      getLeg(SIDE::RIGHT, LEG::BACK  )->m.set(angle);
    } else if(part == PART::OUTER){
      getLeg(SIDE::LEFT,  LEG::FRONT )->o.set(angle);
      getLeg(SIDE::LEFT,  LEG::MIDDLE)->o.set(angle);
      getLeg(SIDE::LEFT,  LEG::BACK  )->o.set(angle);
      getLeg(SIDE::RIGHT, LEG::FRONT )->o.set(angle);
      getLeg(SIDE::RIGHT, LEG::MIDDLE)->o.set(angle);
      getLeg(SIDE::RIGHT, LEG::BACK  )->o.set(angle);
    }
  }


};
