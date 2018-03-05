#include "myShell.h"
#include <fstream>
int main(int argc, char ** argv){
  myShell newShell;
  int i = 1;
  //newShell.requestInput();
  ifstream f(argv[1],ifstream::in);
  while (!f.eof()){
    string str;
    getline(f,str);
    cout<<"Test case "<< i<<": "<<str<<endl;
    stringstream ss;
    ss<<str;
    vector<string> test_vec = newShell.seperate(ss);
    cout<< "size of vec = "<<test_vec.size()<<endl;
    vector<string>::const_iterator it = test_vec.begin();
    while (it != test_vec.end()){
      string::const_iterator it_str = (*it).begin();
      int space = 0;
      int tab   = 0;
      while ( it_str != (*it).end()){
	if (*it_str == 32){
	  ++space;
	}
	else if(*it_str == 9){
	  ++tab;
	}
	++it_str;
      }
      cout<< *it <<" (space = "<<space<<", tab = "<<tab<<" )"<<endl;
      ++it;
    }
    ++i;
    cout<<"========================================"<<endl;
  }
  f.close();
  return(EXIT_SUCCESS);
}

