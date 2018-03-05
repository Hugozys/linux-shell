#include "myShell.h"
int main(void){
  vector<string> test_vec;
  test_vec.push_back("Apple");
  test_vec.push_back("Banana");
  test_vec.push_back("Cat");
  test_vec.push_back("Drew");
  test_vec.push_back("Egg");
  vector<string> test_vec2;
  test_vec2.push_back("");
  myShell newShell;
  newShell.storeArgv(test_vec);
  cout<<"newShell's argv is: " <<endl;
  newShell.getArgv();
  myShell newShell2;
  newShell2.storeArgv(test_vec2);
  cout<<"newShell2's argv is: " <<endl;
  newShell2.getArgv();
  return(EXIT_SUCCESS);
}
