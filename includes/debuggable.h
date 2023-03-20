#pragma once
#include <string.h>
#include <stdio.h>

class Debuggable{
public:
  int debug_level = 0;

  void set_debug(int new_debug_level){
    debug_level = new_debug_level;
  }

  bool debug(int min, int max = 1e3){
    return min <= debug_level && debug_level <= max;
  }

  // TODO: figure out way to add max value too
  bool debug(int min, const char* str, float val = -1){
    bool ret = debug_level >= min;
    if(ret && strlen(str) != 0 && val == -1){
      printf("%s\n",str);
    } else if(ret && strlen(str) != 0){
      printf("%s%d\n",str,val);
    }
    return ret;
  }
};