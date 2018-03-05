#include "myShell.h"
void restore(vector<int> & stdt);
void direct_op(int type, const char * filename,vector<int> & stdt);
int main(void){
  vector<int> stdt;
  stdt.push_back(dup(0));
  stdt.push_back(dup(1));
  stdt.push_back(dup(2));
  direct_op(1,"wNExist.txt",stdt);
  restore(stdt);
  cout<<"Write someghing else to std::cout"<<endl;
  return(EXIT_SUCCESS);
}
