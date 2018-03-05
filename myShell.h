#ifndef _MYSHELL__H
#define _MYSHELL__H
#include<assert.h>
#include<cstdlib>
#include<iostream>
#include <unistd.h>  //For fork and execve function and stat
#include <sys/stat.h> //stat
#include<sys/types.h> //For waitpid function and stat
#include<sys/wait.h>  //For waitpid function
#include <string>
#include <sstream>
#include <fcntl.h> //for open
#include <vector>
#include <cstring> //for strcpy strcmp strdup
#include <cstdio> //for perror
#include <dirent.h> //scandir
#include <map>      //map
#include <utility>  //pair
#include <exception>
#include <queue>
using namespace std;
class redirectExcep: public exception{
};

class pathExp: public exception{
};

class eof{
};

class fail: public exception{
};

class success{
};

class myProgram{
  string programName; //This field is only used when permission denied(program with slash)
  string commandName; //This field is only used for program in the PATH(without slash)
  char **argv;
  int argc;
  int status; //status of child
  pid_t cpid;  //PID = 0 for child, PID = child pid for parent
  pid_t w;  //used when waiting for child's terminating
  bool hasProgram; //whether the requested program exists in PATH
  bool pathError; //Is there error when change from relative path to absolute path( permission denied or no such file or directory)
  bool isSet; //This is used to judge whether the command is set or not
  vector<string> vec; //a copy of argument in case we need redirection
  bool needRedir;  //whether this program needs redirection or not
  int dirStatus;   //-1=command line argument; 0=stdin; 1=stdout; 2=stderr 
  queue<string> in;  //queue used to store stdin redirection file
  queue<pair<int,string> > out; //queue used to store stdout and stderr redirection file
  bool cdError; //if cd nonExistPath
  bool exportErr; //if export incorrect usage
 public:
  bool getcd() const{
    return cdError;
  }
  bool getExpErr() const{
    return exportErr;
  }
  int getArgc() const{
    return argc;
  }
  string getProgName() const{
    return programName;
  }
  string getcmd() const{
    return commandName;
  }
  char ** getArgv() const{
    return argv;
  }
  
  char * getArgv0() const{
    return argv[0];
  }
  bool getPathError() const{
    return pathError;
  }
  bool getHasProgram() const{
    return hasProgram;
  }
  bool getIsSet() const{
    return isSet;
  }
  char * str2cstr(const string & str); //change str to cstr, return a pointer pointing at this cstr(heap)
  
  bool getRedir() const{
    return needRedir;
  }
 myProgram(): programName(),commandName(),argv(NULL),argc(0),status(0),cpid(0),w(0),hasProgram(false),pathError(false),isSet(false),vec(),needRedir(false),dirStatus(-1),in(),out(),cdError(false),exportErr(false){}

  void Delete(){
    for (int i = 0; i < argc; ++i){
      delete[] argv[i];
    }
    delete[] argv;
  }

  ~myProgram(){
    Delete();
  }

  void copy(char ** dest, char ** src,int num){
    if ( num != 0){
      char ** temp = new char*[num]();
      for (int i = 0; i<num;++i){
	temp[i] = strdup(src[i]);
      }
      for (int i = 0; i<num;++i){
	dest[i] = temp[i];
      }
      delete[] temp;
    }
    
  }

 myProgram(const myProgram & rhs):programName(rhs.programName),commandName(rhs.commandName),argv(new char* [rhs.argc+1]()),argc(rhs.argc),status(rhs.status),cpid(rhs.cpid),w(rhs.w),hasProgram(rhs.hasProgram),pathError(rhs.pathError),isSet(rhs.isSet),vec(rhs.vec),needRedir(rhs.needRedir),dirStatus(rhs.dirStatus),in(rhs.in),out(rhs.out),cdError(rhs.cdError),exportErr(rhs.exportErr){ //copy constructor
    copy(argv,rhs.argv,rhs.argc);
  }
    
  myProgram & operator=(const myProgram & rhs){ //assignment operator
     if ( this != &rhs){
       char ** temp=new char*[rhs.argc]();
       copy(temp,rhs.argv,rhs.argc);
       Delete();
       argv = new char*[rhs.argc+1]();
       for (int i = 0; i < rhs.argc; ++ i){
	 argv[i] = temp[i];
       }
       programName = rhs.programName;
       commandName = rhs.commandName;
       argc = rhs.argc;
       status = rhs.status;
       cpid = rhs.cpid;
       w = rhs.w;
       hasProgram = rhs.hasProgram;
       pathError = rhs.pathError;
       isSet = rhs.isSet;
       vec = rhs.vec;
       needRedir = rhs.needRedir;
       dirStatus = rhs.dirStatus;
       in = rhs.in;
       out = rhs.out;
       cdError = rhs.cdError;
       exportErr = rhs.exportErr;
       delete[] temp;
     }
     return(*this);
   }
  vector<string> seperate(stringstream &ss); //seperate is used in parse. It seperates the line
                                             //read by parseInput into arguments.
  
  void storeArgv(vector<string> & argument);//storeArgv is used in parseInput. It stores each element
                                            //of argument vector into argv field of myProgram class

  void parse(string & line,map<string,string> &varMap); //parse string between two pipeline | |
  void forkAndExecve(char ** environment); 
  void redirection();
  void doAllButDir(map<string,string> & mapVar);
  bool isPath(); // if the program has slash symbol
  void replaceRealPath(); 
  void replaceRealProgram(); 
  void changeDIR();
  void PWD(const char * pwd);
  void setCommand(stringstream & setVar,map<string,string> & varMap);
  void exportVar(map<string,string> & varMap);//export enviornment variable into list
  vector<string> redirect(); //This function is used to rearrange the argv/argc/programName and change std::cin,std::cout,std::cerr
  void redirect_helper(size_t head,size_t tail,const string & mother);
  void direct_op(int type, string filename);
  void executeRedir();  //execute Redirection
  char * relative2Absolute(const char *dir); //change relative path to absolute path
};

class myShell{
  vector<string> pipProgram;
  int programNum;
  myProgram * arrProgram_ptr;
  vector<int *> pipArray; //pipe file descriptors
 public:
  bool pipeError; //if it is invalid pipe format
 myShell():pipProgram(),programNum(0),arrProgram_ptr(),pipArray(),pipeError(false){} 
  void del(){
    delete [] arrProgram_ptr;
    for (int i = 0; i < programNum -1 ; ++i){
	  delete[] pipArray[i];
    }
  }

  ~myShell(){
    del();
  }
  
  int getNum() const{
    return programNum;
  }
  void parseInput(); //parse Input from the user
  void requestInput(){ //print prompt
    //cout<<"*****************************"<<endl; //just used to format test_result.txt
    //cout<<endl;    
    const char * pwd = getenv("PWD");
    cout<< "myShell:"<<pwd <<" $ ";
  }
  string getProgram(int i) const{
    return pipProgram[i];
  }
  void pipePrograms(map<string,string> & varMap, char ** envp); //deal with pipe
};

void replaceVar(string & toReplace, map<string,string> & varMap);
void addEnvp(map<string,string> &mapVar, char ** ENVP);
void replace_helper(string & toReplace, map<string,string> & varMap);
#endif

  
