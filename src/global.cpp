#include "global.h"

Global::Global(){

}

  void Global::print_bin(std::string title, short val){
    const unsigned short bin_size = 8;
    const unsigned short str_size = bin_size + (bin_size / 4) + 1;
    char bin[str_size];
    unsigned short bit = 1;
    bin[str_size-1] = '\0';
    for(int i = 0; i < str_size-1; i++){
      if(i == 2 || i == 6){
        bin[str_size-2-i] = ' ';
      } else {
        bin[str_size-2-i] = ((bit & val) == 0) ? '0' : '1';
        bit <<= 1;
      }
    }
    printf("%s: %s (%d)\n",title.c_str(),bin,val);
  }

