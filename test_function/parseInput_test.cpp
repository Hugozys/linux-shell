#include "myShell.h"
int main(){
  myShell newShell;
  newShell.requestInput();
  newShell.parseInput();
  newShell.getArgv();
  return(EXIT_SUCCESS);
}
