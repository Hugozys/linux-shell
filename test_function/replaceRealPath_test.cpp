#include "myShell.h"
int main(void){
  while(1){
    myShell newShell;
    newShell.parseInput();
    if(!strcmp(newShell.getArgv0(),"exit")){
      break;
    }
    else if (!newShell.isPath()){
      cout<<"There is no such path"<<endl;
    }
    else{
      newShell.replaceRealPath();
      if (!newShell.getPathError()){
	cout<<newShell.getArgv0()<<endl;
      }
    }
  }
  return(EXIT_SUCCESS);
}
