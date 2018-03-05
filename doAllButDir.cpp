#include "myShell.h"
void myProgram::doAllButDir(map<string,string> & mapVar){
  if(getIsSet()){
    throw(success());
  }
  else{
    if(getArgc() == 0){
      throw(success());
    }
    else if(strcmp(getArgv()[0],"exit") == 0){
      throw(success());
    }
    else if(strcmp(getArgv()[0],"cd") == 0){
      changeDIR();
      if(cdError){
	throw(fail());
      }
      else{
	throw(success());
      }
    }
    else if(strcmp(getArgv()[0],"export") == 0){
      exportVar(mapVar);
      if(exportErr){
	throw(fail());
      }
      else{
	throw(success());
      }
    }
    else{
      if (!getRedir()){
	if (isPath()){
	  replaceRealPath();
	  if (getPathError()){
	    throw(fail());
	  }
	}
	else{
	  replaceRealProgram();
	  if (!getHasProgram()){
          //print command not found and continue
	    cerr<< "command "<<getArgv0()<<" not found"<<endl;
	    throw(fail());
	  }
	}
      }
    }
  }
}
