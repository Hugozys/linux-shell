#include "myShell.h"
void appendEscape(string & temp, int num){
  while ( num >= 1){
    temp+=92;
    --num;
  }
}
void dealEscape(stringstream & ss, string & temp, int times){
  int c = ss.get(); //read one more character
  
  if ( c == 32 || c == 9){    //base case 1: if it is space or Tab, append n-1 escapes plus 1 space or Tab
    appendEscape(temp,times - 1);
    temp+=c;	
    return;
  }      
  //else
  else if ( (c != 92) && (c != -1)){        //base case 2: if it is not space and Tab and 92 and -1, append n escapes
    appendEscape(temp,times);
    temp+= c;
    return;
  }
  //this has been modified
  else if (c == -1){                  //base case 3: if it is eof, append all the thing before and return
    appendEscape(temp,times);
    return;
  }
  else{
    dealEscape(ss, temp, ++times); //recursive case, this is a 47, call dealEscape to deal with it
    return;
  }
}


       
vector<string> myProgram::seperate( stringstream & ss){
  //ss doesn't have new line character!
  vector<string> ans;
  string temp;
  int c;
  //As long as ss is not eof
  while (!ss.eof()){
  //read one char
    c = ss.get();
    //if eof
    if (ss.eof()){
      //if string is empty
      if (!temp.empty()){
          //push string into vector,clear the string
	ans.push_back(temp);
	temp.clear();
      }
    }
   //else if the char is space or tab
    else if( c == 32 || c == 9){
      if (!temp.empty()){
         //push string into vector, clear the string
	ans.push_back(temp);
	temp.clear();
      }
    }
  //else if the char is 92
    else if ( c == 92){
      dealEscape(ss,temp,1); //call dealEscape function to deal with escape
      if (ss.eof()){
	ans.push_back(temp);//in case 92 is the last character
      }
    }
  //else
    else{
      temp+= c;
    }
  }
  return ans;
}

char * myProgram::str2cstr(const string & str){
  size_t size = str.size();
  char *cstr = new char[size+1](); //create an array of char in the heap, set the size to str.size()+ 1 (null terminator)
  strcpy(cstr,str.c_str());
  return cstr;
}
void myProgram::storeArgv(vector<string> & argument){
  if (argument.empty()){
    argv = new char * [1]();
    argc = 0;
  }
  else{
    programName = argument[0]; //store programName(In case we need relative name to display error message)
    argv = new char * [argument.size()+1]();
    vector<string>::const_iterator it = argument.begin();
    argc = (int) argument.size();
    int index = 0;
    while (it != argument.end()){
      argv[index] = str2cstr(*it); //change the argument string to c_string(array of char)
      ++index;
      ++it;
    }
  }
}

bool isValidKey(const string & check){
  string::const_iterator it = check.begin();
  while(it != check.end()){
    if(!(( *it>=48 && *it<=57) || (*it>=97 && *it<=122) || (*it>= 65 && *it<= 90) || *it == 95)){
      return false;
    }
    ++it;
  }
  return true;
}
void myProgram::setCommand(stringstream & setVar, map<string,string> &varMap){
  //fetch once, see if it's set, if not
  string temp;
  setVar >> temp;
  if (temp != "set"){
    return;
  }
  else{    
   //second fetch,see if it's empty
    isSet = 1; //for myProgram.cpp to tell it's a SET command
    string varKey;
    setVar >> varKey;
  
    if (varKey.empty()){
     
      cerr<<"-myShell: set: Usage: set <varKey> <varValue...>"<<endl;
      return;
      
    }
    else if(!isValidKey(varKey)){
      cerr<<"-myShell: "<<varKey<<": "<<"invalid identifier"<<endl;
      return;
    }

    else{
      string varValue;
      setVar >> varValue;
      while(!setVar.eof()){
	int c = setVar.get();
	if (c == -1){
	  break;
	}
	else{
	  varValue+=c;
	}
      }
      replace_helper(varValue,varMap);//replace the possible variable in varValue
      
   //fetch rest of the shit and store the result into varValue
   //store Key-Value pair into the map
      //check if varKey exists in the environment list
      //if it is, that is a old key, you need to change the value in the environment list and the map
      if (getenv(varKey.c_str()) != NULL){
	if(varKey != "PWD" && varKey != "OLDPWD"){ //user cannot change PWD and OLDPWD
	  setenv(varKey.c_str(),varValue.c_str(),1);
	}     
      }
      varMap[varKey] = varValue;      
      
    }
 
  }
}

void myProgram:: parse(string & line,map<string,string> & varMap){  
    if (line.find('<')!=string::npos || line.find('>')!=string::npos){ //if there is < or > in the line, it needs redirection 
      needRedir = 1;
    }
    replaceVar(line,varMap);
    stringstream ss;
    ss << line;
    //This extra setVar sstream is used to deal with set command
    stringstream setVar;
    setVar << line;
    setCommand(setVar,varMap);
    //seperate the string
    vector<string> argv_vec = seperate(ss);
    //replaceVar(argv_vec,varMap); //replace Varaible with their actual value
    vec = argv_vec; //make a copy of vector for future possible redirection, this is the field of myProgram
    //Store each element in the vector into argv
    storeArgv(argv_vec);
}

