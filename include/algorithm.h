#include "body.h"

namespace algo{
class BaseAlgorithm{
public:
  Body* body;
  int bits = 0;

  BaseAlgorithm(){}

  void set_body(Body* body){
    this->body = body;
  }

  void loop(){
    while(true)
      step();
  }
  virtual void step() {};
};
}

