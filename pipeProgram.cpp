#include "myShell.h"
void myShell::pipePrograms(map<string,string> & varMap,char ** envp){
  //we need to create an array of program 
  arrProgram_ptr = new myProgram[programNum](); //(remember to delete)
  int num = programNum -1;
  vector<int*> temp(num);
  pipArray  =  temp;
  //to each program we use methods to fill in with fields
  //create an array of pipefd
  for (int i = 0; i < programNum -1 ; ++i){
    pipArray[i] = new int[2](); //remember to delete
    pipe((pipArray[i])); //pipe tunnel
  }
  //count i from 0 to programNum(exclusive)
  for( int i = 0; i < programNum; ++i){   
  //create fork
    int cpid = fork();
    if ( cpid == -1){
      perror("FORK");
      _exit(EXIT_FAILURE);
    } 
    //if 0 that means child
    else if ( cpid == 0){
      //do what child should do
      arrProgram_ptr[i].parse(pipProgram[i],varMap);
      //you do all of the things before exceve
	arrProgram_ptr[i].doAllButDir(varMap);
      if(arrProgram_ptr[i].getRedir()){
	  arrProgram_ptr[i].redirection();
	arrProgram_ptr[i].executeRedir();
      }
      //then you manipulate file descriptors
      if (i == 0){   //This means that this is the first program in the pipeline
	close(pipArray[0][0]); //close read end
	dup2(pipArray[0][1],1); 
	close(pipArray[0][1]); //close write end
      }
      else if ( i == programNum -1){ //This means that this is the last program in the pipeline
	dup2(pipArray[i-1][0],0); 
	close(pipArray[i-1][1]); 
      }      
      else{ //These are the programs in the midlle
	dup2(pipArray[i-1][0],0); //redirect this process's stdin to the read end of pipe
	
	dup2(pipArray[i][1],1); //redirect this process's stdout to the write end of pipe
	close(pipArray[i][1]);
      }

      //at last you are gonna call exceve
      if (arrProgram_ptr[i].getHasProgram()){
	execve((arrProgram_ptr[i].getcmd()).c_str(),arrProgram_ptr[i].getArgv(),envp);
      }
      else{
	execve(arrProgram_ptr[i].getArgv0(),arrProgram_ptr[i].getArgv(),envp);
      }      
      cerr<<"-myShell: "<<arrProgram_ptr[i].getProgName()<<": ";
      perror("");
      throw(fail());
    }

    else{
      if (i != programNum -1){
	close(pipArray[i][1]); //parent close last pipe's write end to send read end EOF
      }
    }
  }
  int stat = 0;
  int w = 0;
  w = waitpid(-1, &stat,0);
  while(w>0){
    if(WIFEXITED(stat)){
      cout<<"Program exited with status "<<WEXITSTATUS(stat)<<endl;
    }
    else if(WIFSTOPPED(stat)){
      cout<<"Program was stopped by signal "<<WSTOPSIG(stat)<<endl;
    }
    else if(WIFSIGNALED(stat)){
      cout<<"Program was killed by signal "<<WTERMSIG(stat)<<endl;
    }
    else if(WIFCONTINUED(stat)){
      cout<<"continued"<<endl;
    }
    w = waitpid(-1,&stat,0);
  }
  //wait child to response
}


  
