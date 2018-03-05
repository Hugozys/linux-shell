#include "myShell.h"
//The following code is cited from man page
//man execve EXAMPLE
//man waitpid EXAMPLE 
void myProgram::redirection(){ 
    vector<string> temp = redirect();
    Delete(); //delet old argv
    storeArgv(temp); //store new
    if (isPath()){
      replaceRealPath();
      if (getPathError()){
	throw(pathExp());
      }
    }
    else{
      replaceRealProgram();
      if (!hasProgram){
	cerr<< "command "<<getArgv0()<<" not found"<<endl;
	throw(pathExp());
      }
    }
}

void myProgram:: forkAndExecve(char** environment){  
  cpid = fork();
  if ( cpid == -1 ){
    perror("FORK");
    _exit(EXIT_FAILURE);
  }
  else if ( cpid == 0){
    executeRedir();
    //YOU ARE SUPPOSED TO EXECUTE REDIRECTION HERE
    if (hasProgram){
      execve(commandName.c_str(),argv,environment); //rm instead of /bin/rm
    }
    else{
      execve(argv[0],argv,environment); //program with slash
    }      
    cerr<<"-myShell: "<<programName<<": ";
    perror("");
    _exit(EXIT_FAILURE);
  }
  else{
    do{
      w = waitpid(cpid, &status,WUNTRACED | WCONTINUED);
      if (w == -1){
	perror("WAITPID");
	_exit(EXIT_FAILURE);
      }
      else if(WIFEXITED(status)){
	cout<<"Program exited with status "<<WEXITSTATUS(status)<<endl;
      }
      else if(WIFSTOPPED(status)){
	cout<<"Program was stopped by signal "<<WSTOPSIG(status)<<endl;
      }
      else if(WIFSIGNALED(status)){
	cout<<"Program was killed by signal "<<WTERMSIG(status)<<endl;
      }
      else if(WIFCONTINUED(status)){
	cout<<"continued"<<endl;
      }
    } while(!WIFEXITED(status) && !WIFSIGNALED(status));
  }
}
      
    
