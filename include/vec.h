#pragma once


class Vec3f{
public:

  static Vec3f zero(){
    return Vec3f(0,0,0);
  }
  static Vec3f forward(float scale){
    return Vec3f(scale,0,0);
  };
  static Vec3f backward(float scale){
    return Vec3f(-scale,0,0);
  };
  static Vec3f right(float scale){
    return Vec3f(0,scale,0);
  };
  static Vec3f left(float scale){
    return Vec3f(0,-scale,0);
  };
  static Vec3f up(float scale){
    return Vec3f(0,0,scale);
  };
  static Vec3f down(float scale){
    return Vec3f(0,0,-scale);
  };

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

  void operator=(Vec3f other){
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
  }

  void operator*=(float scalar){
    *this = *this * scalar;
  }
  void operator+=(Vec3f other){
    *this = *this + other;
  }
  void operator-=(Vec3f other){
    *this = *this - other;
  }

  Vec3f operator*(float scalar){
    Vec3f other = *this;
    other.x *= scalar;
    other.y *= scalar;
    other.z *= scalar;
    return other;
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
