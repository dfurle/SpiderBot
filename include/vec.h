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
  
  Vec3f operator-(){
    Vec3f other;
    other.x = -this->x;
    other.y = -this->y;
    other.z = -this->z;
    return other;
  }

  Vec3f norm(){
    float mag = 1/sqrt(this->x*this->x + this->y*this->y + this->z*this->z);
    return (*this) * mag;
  }

  Vec3f rotate(float angle, char axis){
    Vec3f tmp;
    tmp.x = this->x;
    tmp.y = this->y;
    tmp.z = this->z;
    Vec3f pos = tmp;
    if(axis == 'x'){
      pos.y =  tmp.y*cos(angle) + tmp.z*sin(angle);
      pos.z = -tmp.y*sin(angle) + tmp.z*cos(angle);
    } else if(axis == 'y'){
      pos.x = tmp.x*cos(angle) - tmp.z*sin(angle);
      pos.z = tmp.x*sin(angle) + tmp.z*cos(angle);
    } else if(axis == 'z'){
      pos.x = tmp.x*cos(angle) - tmp.y*sin(angle);
      pos.y = tmp.x*sin(angle) + tmp.y*cos(angle);
    } else {
      printf("unknown axis!\n\n");
    }
    return pos;
  }

  operator std::string(){
    std::string str = "";
    str += "<";
    str += std::to_string(x);
    str += ",";
    str += std::to_string(y);
    str += ",";
    str += std::to_string(z);
    str += ">";
    return str;
  }


};
