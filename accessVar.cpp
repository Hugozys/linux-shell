#include "myShell.h"

bool isValidKey(const string & check);
string cstr2str(const char *cstr);
void replace_helper(string & toReplace, map<string,string> & varMap){
  //find $ in toReplace, call the position start
  size_t start = toReplace.find_first_of('$');
  //if not find, that means we don't have var in this string, simply return
  if (start == string::npos){
    return; //base case
  }

  else{    
  //set a tempPos = start+1, as long as tempPos is letter or num or underscore or not end,append it to temp string
    size_t tempPos = start + 1;
    string temp;
    int c = toReplace[tempPos];
    while (((( c>=48 && c<=57) || (c>=97 && c<=122) || (c>= 65 && c<= 90) || c == 95)) && (tempPos != toReplace.size())){
      temp+=c;
      ++tempPos;
      c = toReplace[tempPos];
    }      
    map<string,string>::const_iterator map_it = varMap.find(temp);
    //search map to find the temp's corresponding value
    //if not find, this var is not defined, you have some cases to deal with
    if ( map_it == varMap.end()){
	toReplace.replace(start,tempPos+1-start,"");
    }
    else{
      //if find, you replace the [start,tempPos) with ans
      toReplace.replace(start,tempPos-start,map_it->second);
    }
    //call replace_helper again to recurse
    replace_helper(toReplace,varMap);
      
  }
}



void replaceVar(string & toReplace, map<string,string> & varMap){
  replace_helper(toReplace,varMap);
}

void split(char * cstr, string & k, string & v){
  string toSplit = cstr2str(cstr);
  size_t size = toSplit.size();
  size_t delim = toSplit.find_first_of('=');
  k = toSplit.substr(0,delim);
  v = toSplit.substr(delim+1,size - delim - 1);
}

void addEnvp(map<string,string> & mapVar, char **envp){
  int index = 0;
  //for each element in envp
  while (envp[index] != NULL){
    string KEY;
    string VALUE;
  //split it into KEY and VALUE
    split(envp[index],KEY,VALUE);
  //STORE IT INTO MAP
    mapVar[KEY] = VALUE;
    ++index; 
  //WE ARE DONE
  }
}

void myProgram::exportVar(map<string,string> & varMap){
  if(argc == 1){
    cerr<<"-myShell: "<<"Usage: export <var>"<<endl;
    exportErr = 1;
  }
  else{
    if (!isValidKey(cstr2str(argv[1]))){
      cerr<<"-myShell: "<<"invalid variable"<<endl;
      exportErr = 1;
    }
    else{
      map<string,string>::const_iterator map_it = varMap.find(argv[1]);
      if (map_it != varMap.end()){
	if (strcmp(argv[1],"PWD") != 0 && strcmp(argv[1],"OLDPWD") != 0){ //user cannot change PWD and OLDPWD
	  setenv((map_it->first).c_str(),(map_it->second).c_str(),1);
	}
      }
      else{
	setenv(argv[1],"",1);
      }
    }
  }
}
