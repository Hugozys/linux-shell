/* else if ((buf.st_mode & S_IFMT) == S_IFLNK){
    //the following code is cited from previous assignment: 060_stat/mystat.c [line 144-150]
    //if it's a symbolic link, return path
    char * resolved = dealWithSymbolic(dir);
    if (resolved == NULL){
      return;
    }
    else{
      
      //walkThroughDIR(resolved,cache);//recursion
      free(resolved);
      return;
    }
  }
  */


/*
char * dealWithSymbolic(const char * dir){
  char linktarget[256];
  ssize_t len = 0;
  if ((len = readlink(dir,linktarget,256)) == -1){
    cerr<<"-myShell: "<<dir<<": ";
    perror("");
    return NULL;
  }
  else{
    linktarget[len] = '\0';
    string trueIncomPath = cstr2str(linktarget); // .. risk
    string fakePath  = cstr2str(dir); //parent info
    if (trueIncomPath.find('/') == string::npos){
      return NULL; // file in the same directory
    }
    else if(trueIncomPath.find('.') == string::npos){
      return strdup(linktarget);
      // normal path(lstat doesn't screw up)
    }
    else{
      //lstat screws up which means there are relative path in the return path of readlink
      size_t parPosition = fakePath.find_last_of('/',(fakePath.find_last_of('/')-1));
      size_t discardDot = trueIncomPath.find('/');
      string finalPath = fakePath.substr(0,parPosition)+ trueIncomPath.substr(discardDot,(trueIncomPath.size()-discardDot)); // the function of above three lines are to manipulate two strings(extracat some parts of two strings respectively and stick them together to get the absolute path of the file which symbolic link points at
      const char *truePath = finalPath.c_str();
      return strdup(truePath);
    }
  }
}
*/

