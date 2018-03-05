#include<cstdlib>
#include<iostream>
#include<string>
#include<unistd.h>
#include<cstring>
using namespace std;
int direct_op(int type, const char * filename, const char *mode);

int main(void){
  /*
  if(direct_op(0,"exist.txt","r") == 0){
    string str;
    getline(cin,str);
    cout<<"cin: "<<str<<endl;
  }
  */
  /*
  direct_op(1,"notExist.txt","r");
  if(direct_op(1,"wExist.txt","w") == 0){
    cout<<"Write something to std::cout"<<endl;
  }
  */
  direct_op(1,"wNExist.txt","w");
  cout<<"Write someghing else to std::cout"<<endl;
  direct_op(2,"errExist.txt","w");
  cerr<<"ERROR!"<<endl;
  return(EXIT_SUCCESS);
}
