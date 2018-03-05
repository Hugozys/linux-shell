#include "myShell.h"
void printVectorStr(vector<string> & str);
vector<string> extractDIR(const char *linuxPATH);
void walkThroughDIR(const char *dir, vector<string> &cache);

int main(void){
  const char * path = getenv("PATH");
  vector<string> Envp;
  vector<string> AoP;
  Envp = extractDIR(path);
  vector<string>::const_iterator it_envp = Envp.begin();
  while (it_envp != Envp.end()){
    const char * dir = (*it_envp).c_str();
    //cout<<dir<<endl;
    walkThroughDIR(dir,AoP);
    ++it_envp;
  }
  printVectorStr(AoP);
  return(EXIT_SUCCESS);
}
