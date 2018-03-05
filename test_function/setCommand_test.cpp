#include "myShell.h"
#include "fstream"
void printMap(map<string,string> & varMap){
  cout<<"Print Map"<<endl;
  cout<<"Size of Map: "<<varMap.size()<<endl;
  map<string,string>::const_iterator it = varMap.begin();
  while(it != varMap.end()){
    cout<<"[Key: "<<it->first<<", Value: "<<it->second<<"]"<<endl;
    ++it;
  }
}
int main(int argc,char **argv){
  myShell newShell;
  map<string,string> varMap;
  string str;
  int index = 1;
  ifstream f(argv[1],ifstream::in);
  while (!f.eof()){
    getline(f,str);
    cout<<"-------------------------------------"<<endl;
    cout<<"Test case "<<index<<": "<<str<<endl;
    stringstream ss;
     ss << str;
    newShell.setCommand(ss,varMap);
    ++index;
  }
  printMap(varMap);
}   
