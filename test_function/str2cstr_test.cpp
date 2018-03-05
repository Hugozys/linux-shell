#include "myShell.h"


int main(void){
  myShell newShell;
  string mystr("Test String!");
  char *cstr = NULL;
  cstr = newShell.str2cstr(mystr);
  cout<<cstr<<endl;
  for (size_t i = 0; i<= mystr.size(); ++i){
    cout<<cstr[i]<<endl;
  }
  delete[] cstr;
  return(EXIT_SUCCESS);
}
