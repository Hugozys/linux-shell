#include "myShell.h"
void manfd(string & curr, int type){ //function used to redirect stdin and stdout(actuall execution)
  if (!curr.empty()){
    int MODE;
    if (type == 0){
      MODE = O_RDONLY;
    }
    else{
      MODE = O_WRONLY;
    }
    int in_fd = open(curr.c_str(),MODE);
    close(type);
    dup2(in_fd,type);
    close(in_fd);
  }
}

void myProgram::direct_op(int type, string filename){
  if (type == 0){
    int fd_in;
    if((fd_in = open(filename.c_str(),O_RDONLY)) == -1){
      cerr<<"-myShell: "<<filename<<": ";
      perror(""); //input direction doesn't exist
      throw(redirectExcep());
    }
    else{
      close(fd_in);
      in.push(filename); //stdin queque
    }
  }
  else{
    out.push(pair<int,string>(type,filename)); //stdout and stderr queue
  }
}


void myProgram::executeRedir(){
  string curr_in;
  string curr_out;
  string curr_err;
  while (!in.empty()){
    string temp = in.front();
      curr_in = temp;
      in.pop();      
  }
  manfd(curr_in,0);
  //while queue_out is not empty
  while (!out.empty()){
    //If this file doesn't exist
    if ((out.front()).first == 1){
     //look up the type in the queue
    //if it is 1,open it to create that file and then immediately close it
	curr_out = (out.front()).second;
	int fd_out = open(curr_out.c_str(),O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);
	close(fd_out);
      }
    //set current_out = filename
    //else if it is 2,open it to create that file and then immediately close it
      else{
	curr_err = (out.front()).second;
	int fd_err = open(curr_err.c_str(),O_WRONLY|O_CREAT,S_IRUSR|S_IWUSR);
	close(fd_err);
      }
      out.pop();
    }
  //out of loop
    manfd(curr_out,1);
  //if current_out is not empty
    manfd(curr_err,2);
}

void myProgram::redirect_helper(size_t head,size_t tail,const string & mother){
  int type; // 0 stands for stdin
            //1 stands for stdout
  
  if((head == 1) && mother[head] == '>' && mother[0] == '2'){
    type = 2;
  }
  else if (mother[head] == '>'){
    type = 1;
  }
  else{
    type = 0;
  }
  //if tail - head = 1
  if ((tail - head) == 1){  //base case (error)
     //throw exception
    char err;
    if (type == 0){
      err = '<';
    }
    else{
      err = '>';
    }
    cerr<<"-myShell: syntax error near unexpected token '"<<err<<"'"<<endl;
    throw(redirectExcep());
  }
  //else if tail is npos(not found)  //base case
  else if (tail == string::npos){
  //redirect [head,size)
    if ( head == mother.size() - 1){ //This means something like ./program < input_exist.txt> ....
      dirStatus = type;
      return;
    }
    else{
      string temp = mother.substr(head + 1, mother.size() - head);
      direct_op(type,temp);
      dirStatus = -1;
  //return
      return;
    }
  }
  //else if tail is the last    //base case 2
  else if ( tail == mother.size() - 1){
  //set dirStatus according to tail
    if (mother[tail] == '>'){
      dirStatus = 1;
    }
    else{
      dirStatus = 0;
    }
    string temp = mother.substr(head+1,tail-head-1);
    direct_op(type,temp);
    return;
  }
  else{
    string temp = mother.substr(head+1,tail-head-1);
    direct_op(type,temp);
  //recurse
    redirect_helper(tail,mother.find_first_of("<>",tail+ 1),mother);
  }
}

vector<string> myProgram::redirect(){
  //you need to check each argument in vec
  //create a new vector called ans
  vector<string> ans;
  //for each element in vec:
  vector<string>::const_iterator it = vec.begin();
  while (it != vec.end()){
  //if > < 2> and (dirStatus = 1 or 0 or 2)
    if ((*it == ">" || *it == "<" || *it == "2>") && (dirStatus == 0 || dirStatus == 1 || dirStatus == 2)){
    //error ./program > <
      cerr<<"-myShell: syntax error near unexpected token '"<<*it<<"'"<<endl;
      throw(redirectExcep());
    }
  //else if > dirStatus = 1 last is >
    else if ( *it == ">" ){
      dirStatus = 1;
      ++it;
      continue;
    }
  //else if < dirStatus = 0 last is <
    else if ( *it == "<" ){
      dirStatus = 0;
      ++it;
      continue;
    }
  //else if 2> dirStatus = 2 last is 2>
    else if ( *it == "2>"){
      dirStatus = 2;
      ++it;
      continue;
    }
    else{
     //find">" or "<", call it angleTail
      size_t angleTail = (*it).find_first_of("<>");
      if (angleTail == string::npos){
	if (dirStatus == -1){
        //push [0,angleTail) into new vector
	  ans.push_back(*it);
	}
	else{
	// push into queue
	  direct_op(dirStatus,(*it));
	  dirStatus = -1;
	}
      }
     //if angleTail is 0th and dirStatus != -1
      else if (angleTail == 0 && dirStatus != -1){
	cerr<<"-myShell: syntax error near unexpected token '"<<*it<<"'"<<endl;
       //this is error   // ./program > >fuckYou
       //return
	throw(redirectExcep());
      }
     //else if angleTail is not 0th
      else if ( angleTail != 0){
	string temp = (*it).substr(0,angleTail);
      //if dirStatus = -1
	if ( (*it)[0] == '2' && ((*it)[1] == '>')){
	  if (dirStatus != -1){
	    cerr<< "-myShell: syntax error near unexpected token '2'"<<endl;
	    throw(redirectExcep());
	  }
	  else{
	    size_t angleHead = angleTail;
	    angleTail = (*it).find_first_of("<>",angleHead + 1);
	    redirect_helper(angleHead,angleTail,*it);
	  }
	}
	else{
	  if (dirStatus == -1){
        //push [0,angleTail) into new vector
	  ans.push_back(temp);
	}
	  else{
	// redirect stdin or stdout or stderr
	    direct_op(dirStatus,temp);
	}
	size_t angleHead = angleTail;
	angleTail = (*it).find_first_of("<>",angleHead + 1);
    //redirect_helper(angleTail,findNext,string)
	redirect_helper(angleHead,angleTail,*it);
	}
      }
      else{
	redirect_helper(angleTail,(*it).find_first_of("<>",angleTail + 1),*it);
      }
    }
    ++it;
  }
  if (dirStatus != -1){
    if (dirStatus == 0){
      cerr<<"-myShell: syntax error near unexpected token '<'"<<endl;
    }
    else if (dirStatus == 1){
      cerr<<"-myShell: syntax error near unexpected token '>'"<<endl;
    }
    else{
      cerr<<"-myShell: syntax error near unexpected token '2'"<<endl;
    }
    throw(redirectExcep());
  }
  
  return ans;
}

