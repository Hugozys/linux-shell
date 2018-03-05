#include "myShell.h"
extern char** environ;
bool isWhite(string & line){
  string::const_iterator str_it = line.begin();
  while (str_it != line.end()){
    if((*str_it != ' ') && (*str_it != 9)){
	return false;
      }
    else{
      ++str_it;
    }
  }
  return true;
}
	
void myShell:: parseInput(){
  string line;
  //read one line
  getline(cin, line);
  //std::cout<<line<<endl; //This is used to display user friendly test result
  if (cin.eof()){
  //exit the program
    //std::cout<<endl;
    throw(eof());
    exit(EXIT_SUCCESS);
  }
  //else
  else{
    //if no | simply set programNum to 1
    if (line.find_first_of('|') == string::npos){
      pipProgram.push_back(line);
      programNum = 1;
    }
    //if last character is | that is an error
    else if(line.find_first_of('|') == (line.size()-1)){
      cerr<<"-myShell: Invalid Use of |"<<endl;
      pipeError = true;
      return;
    }
    else{
    //else
      //seperate strings with |, push them into vector
      stringstream ss;
      string temp;
      ss<<line;
      while(!ss.eof()){
	getline(ss,temp,'|');
	if (temp.empty() || isWhite(temp)){
	  cerr<<"-myShell: Invalid Use of |"<<endl;
	  pipeError = true;
	  return;
	}
	else{
	  pipProgram.push_back(temp);
	}
      }
      programNum = pipProgram.size();
    }
  }
}


int main(int ARGC,char **ARGV,char ** ENVP){
  map <string,string> mapVar;
  addEnvp(mapVar,ENVP); //ADD SYSTEM ENVP INTO MAP
  while(1){
    myShell newShell;
    newShell.requestInput();  //requestInput from user
    try{
      newShell.parseInput(); //parseInput from user
    }
    catch(eof & e){ //if it is eof(ctrl+D)
      break;
    }
    if (newShell.pipeError){
      continue;
    }

    if (newShell.getNum() == 1){ //if there is only one program no pipe, execute the following)
      string entry = newShell.getProgram(0);
      myProgram newProgram;    
      newProgram.parse(entry,mapVar);//parse each program  
      if (newProgram.getIsSet()){
	continue;
      }
      else{
	if (newProgram.getArgc() == 0){
	  continue; 
	}
	else if(strcmp(newProgram.getArgv()[0],"exit")== 0){ //exit 
	  break;
	}
	else if(strcmp(newProgram.getArgv()[0],"cd") == 0){ //cd command
	  //call changeDIR function
	  newProgram.changeDIR();
	  continue;
	}
	else if(strcmp(newProgram.getArgv()[0],"export") == 0){ //execute export in-built command
	  newProgram.exportVar(mapVar);
	  continue;
	}
	else{
	  if (!newProgram.getRedir()){
	//check 0th element in Argv field
	//if there is / in it
	    if (newProgram.isPath()){
	  //try to find the absolute path replace 0th element with this absolute path
	      newProgram.replaceRealPath();
	//if error
	      if (newProgram.getPathError()){
		continue;
	      }
	    }
	    else{
         //find the program and replace 0th element with absolute path
	      newProgram.replaceRealProgram();
         //if not find
	      if (!newProgram.getHasProgram()){
		cerr<< "command "<<newProgram.getArgv0()<<" not found"<<endl;
		continue;
	      }
	    }
	  }
	
	  
	  if (newProgram.getRedir()){ //if there is possible redirection 
	    try{
	      newProgram.redirection();
	    }    	  
	    catch(exception & e){ //catch redirection exception
	      continue;
	    }
	  }
	  newProgram.forkAndExecve(environ); //fork, execute redirection and execve
	}
      }  
    }
    else{
      try{
	newShell.pipePrograms(mapVar,environ); //if pipe, execute
      }
      catch(success & e){ //child succeeds
	//_exit(EXIT_SUCCESS);
	break;
      }
      catch(exception & e){ //child fails
	//_exit(EXIT_FAILURE);
	return(EXIT_FAILURE);
      }
    }
  }
  return(EXIT_SUCCESS);
}
