#include<iostream>
#include<fstream>
#include<cstdlib>
#include<string>
int main(void){
  std::string str;
  while (std::cin){
    int c = std::cin.get();
    if ( c!= -1){
      str.push_back(c);
    }
  }
  std::cout<<str;
  return(EXIT_SUCCESS);
}

