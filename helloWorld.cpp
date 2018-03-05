#include<iostream>
#include<cstdlib>
#include<string>
int main(int argc, char **argv){
  std::string str;
  getline(std::cin,str);
  std::cout<<str<<std::endl;
  std::cout<<"argc: "<<argc<<std::endl;
  for (int i = 0;i < argc; ++i){
    std::cout<<"argv["<<i<<"]: "<<argv[i]<<std::endl;
  }
  std::cerr<<"Test stderr redirection! Hello World!"<<std::endl;
  return(EXIT_SUCCESS);
}
