#include <iostream>
#include <cstdlib>
#include <string>
int main(int argc, char ** argv){
  for (int i = 0; i < argc; ++ i){
    std::string str(argv[i]);
    std::string::const_iterator it_str = str.begin();
      int space = 0;
      int tab   = 0;
      while ( it_str != str.end()){
	if (*it_str == 32){
	  ++space;
	}
	else if(*it_str == 9){
	  ++tab;
	}
	++it_str;
      }
      std::cout<<"argv["<<i<<"]: "<<argv[i]<<" (space = "<<space<<", tab = "<<tab<<" )"<<std::endl;
  }  
  return(EXIT_SUCCESS);
}
