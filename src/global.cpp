#include "global.h"
#include <algorithm>

Global::Global(){

}


int Global::toBits(std::string str, int current_bits, std::map<std::string, int>& map){
  size_t pos = 0;
  std::string token;

  int _bits = 0;
  int bits_override = 0;
  int bits_append = 0;
  int bits_subtr = 0;

  bool done = false;
  while(!done) {
    pos = str.find(' ');
    token = str.substr(0, pos);
    std::transform(token.begin(), token.end(), token.begin(), ::toupper);
    str.erase(0, pos+1);
    char addsub = token[0];
    if(addsub == '+' || addsub == '-')
      token = token.substr(1);
    else
      addsub = ' ';
    auto it = map.find(token);
    if (it != map.end()){
      g.print_bin("bits",_bits);
      g.print_bin("iter",it->second);
      switch(addsub){
      case ' ':
        bits_override |= it->second;
        break;
      case '+':
        bits_append |= it->second;
        break;
      case '-':
        // bits_subtr &= ~it->second;
        bits_subtr |= it->second;
      }
    } else {
      printf("Could not find token (%s)\n",token.c_str());
    }
    if(pos == std::string::npos){
      done = true;
    }
  }
  if(g.strip(bits_override, LEG::ALL) == 0)
    bits_override |= g.strip(current_bits, LEG::ALL);
  if(g.strip(bits_override, PART::ALL) == 0)
    bits_override |= g.strip(current_bits, PART::ALL);
  _bits |= bits_override;
  _bits |= bits_append;
  _bits &= ~bits_subtr;
  return _bits;
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

