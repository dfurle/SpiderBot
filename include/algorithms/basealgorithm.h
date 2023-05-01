#pragma once
#include "body.h"

namespace algo{
class BaseAlgorithm{
public:
  Body* body;
  int bits = 0;

  BaseAlgorithm(Body* body){
    this->body = body;
  }

  void loop(){
    while(true)
      step();
  }
  virtual void step() {};
};
}

