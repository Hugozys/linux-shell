#include "myShell.h"
void myProgram::PWD(const char * pwd){
  if (chdir(pwd) == -1){
      cerr<<"-myShell: cd: "<<pwd<<": ";
      perror("");
      cdError = true;
  }
  else{
    char *newPWD = relative2Absolute("./");
    setenv("PWD",newPWD,1);
    free(newPWD);
  }
}
void myProgram::changeDIR(){
  const char * pwd = getenv("PWD");
  //first you need to change OLDPWD to PWD
  setenv("OLDPWD", pwd , 1);
  //check if argv[1] is NULL
  //if so go to home directory
  //change PWD to home
  if (argv[1] == NULL || !strcmp(argv[1],"~")){
    const char * home = getenv("HOME");
    PWD(home);
  }    
  //else
  //next you need change PWD to argv[1]
  //To do this you need to change argv[1] to its absolute path
  else{
    PWD(argv[1]); 
  }
}
