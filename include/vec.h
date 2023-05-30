#pragma once

class Vec3f{
public:
  float x, y, z;

  Vec3f(){
    x = 0;
    y = 0;
    z = 0;
  }

  Vec3f(float x, float y, float z){
    this->x = x;
    this->y = y;
    this->z = z;
  }

  Vec3f operator+(Vec3f other){
    other.x += this->x;
    other.y += this->y;
    other.z += this->z;
    return other;
  }

  Vec3f operator-(Vec3f other){
    other.x = this->x - other.x;
    other.y = this->y - other.y;
    other.z = this->z - other.z;
    return other;
  }

};