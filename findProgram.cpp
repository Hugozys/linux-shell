#include "myShell.h"


string cstr2str(const char * cstr){ //transfer cstring to string object
  stringstream ss;
  ss<<cstr;
  string ans = ss.str();
  return ans;
}
 

char * myProgram::relative2Absolute(const char *dir){ //change relative path to absolute path
  char *resolved = NULL;
  if ((resolved = realpath(dir,NULL))==NULL){
    cerr<< "-myShell: " <<dir<<": ";
    perror("");
  }
  return resolved;
}

void walkThroughDIR(const char *dir, vector<string> & cache){
  DIR * d = opendir(dir);
  if (d == NULL){ //error checking
    cerr<<"-myShell: "<<dir<<": ";
    perror("");
    return;
  }
  else{
    dirent * info = NULL;
    while ( (info = readdir(d)) != NULL){ //iterate through dir stream
      if (info->d_type != DT_DIR){
	string filename(dir);
	string::const_iterator str_it = filename.end() -1;
	if ( *str_it != '/'){ //ensure the correct path format
	  filename.append("/");
	}

	filename.append(info->d_name);
	cache.push_back(filename); //push path name to the vector
      }
    }
    closedir(d);
  }
}


 
vector<string> extractDIR(const char *linuxPATH){ //extract all the directory in PATH(environment variable)
  vector<string> ans;
  stringstream ss;
  string temp;
  ss<< linuxPATH;
  while(!ss.eof()){
    getline (ss, temp, ':');
    ans.push_back(temp);
  }
  return ans;
}


bool myProgram::isPath(){
  char *inspector = NULL;
  inspector = strchr(argv[0], 47);
  if (inspector != NULL){
    return true;
  }
  else{
    return false;
  }
}

void myProgram:: replaceRealPath(){
  //The following code was cited from previous assignment( 097_dedup/dirWalkTree.cpp)
  char *resolved = relative2Absolute(argv[0]);
  if (resolved == NULL){
    pathError = 1;
  }
  else{
    struct stat fileInfo;
    lstat(resolved,&fileInfo);
    if((fileInfo.st_mode & S_IFMT) == S_IFDIR){
      //if we call replaceRealPath when redirecting and error happens, restore 
      cerr<<"-myShell: "<<argv[0]<<": is a directory"<<endl;
      pathError = true;
    }
    free(resolved);
    }
  }



string findYourName(const string & program){ //find the name of every possible program in PATH 
  size_t pos = program.find_last_of('/') + 1;
  size_t length = program.size();
  return program.substr(pos,length - pos);
}

void myProgram::replaceRealProgram(){
  const char * linuxPATH = getenv("PATH");
  //extract all the directories in linuxPATH to one vector, all it wareHouse
  vector<string> wareHouse = extractDIR(linuxPATH);
  vector<string> programCache;
  vector<string>::const_iterator it = wareHouse.begin();
  while (it != wareHouse.end()){
  //for each directory in wareHouse,go through it and extract all the filenames in it, store them into a vector called programCache
    char * resolved = realpath((*it).c_str(),NULL);
    if (resolved == NULL){ //if evil user set some badpath
      ++it;
      continue;
    }
    //find absolute path
    walkThroughDIR(resolved,programCache);
    ++it;
    free(resolved);
  }
  //for each element in programCache
  vector<string>::const_iterator it_cache = programCache.begin();
  while (it_cache != programCache.end()){
    string lastWord = findYourName(*it_cache);
  //compare argv[0] with it
    if (!strcmp(argv[0],lastWord.c_str())){
  //if equal, this is the program we're gonna execute
      commandName = *it_cache;
      hasProgram = true; 
      break;
    }
    ++it_cache;
  }
}

