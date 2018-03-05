#include "myShell.h"
//using namespace std;
int main(void){
  while(1){
    myShell newShell;
    newShell.parseInput();
    newShell.replaceRealProgram();
    if (newShell.getHasProgram() == true){
      cout<<"This program exists!\n";
      cout<<newShell.getArgv0()<<endl;
    }
    else if(!strcmp(newShell.getArgv0(),"exit")){
      break;
    }
    else{
      cout<< "Command not found"<<endl;
    }
  }
  return(EXIT_SUCCESS);
}
