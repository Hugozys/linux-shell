#include "myShell.h"
string findYourName(const string & program);
int main(void){
  string str("/findYourName/test/normal/IamHere");
  cout<<str<<endl;
  cout<<findYourName(str)<<endl;
  return(EXIT_SUCCESS);
}
