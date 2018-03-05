#include "myShell.h"
int main(void){
  myProgram program1;
  vector<string> vec;
  vec.push_back("Apple");
  vec.push_back("Orange");
  vec.push_back("Banana");
  vec.push_back("Drew");
  vec.push_back("Genevieve");
  vec.push_back("Valgrind is ass");
  program1.storeArgv(vec);
  myProgram program2(program1);
  myProgram program3;
  vector<string> vec2;
  vec2.push_back("HAHA");
  program3.storeArgv(vec2);
  program3 = program1;
  myProgram program4;
  program1 = program4;
  return(EXIT_SUCCESS);
}
