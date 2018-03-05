#include "myShell.h"
void printMap(map<string,string> & varMap){
  cout<<"Print Map"<<endl;
  cout<<"Size of Map: "<<varMap.size()<<endl;
  map<string,string>::const_iterator it = varMap.begin();
  while(it != varMap.end()){
    cout<<"[Key: "<<it->first<<", Value: "<<it->second<<"]"<<endl;
    ++it;
  }
}

void printVectorStr(vector<string> & str); //print vector, this is used to test function behavior
void replaceVar(vector<string> & argVector, map<string,string> & varMap);
using namespace std;
void replace_helper(string & toReplace, map<string,string> & varMap);
void printTestResult(int i,string & testStr,map<string,string> & varMap){
  cout<<"---------------------------------------"<<endl;
  cout<<"Test case "<<i<<": "<<testStr<<endl;
  cout<<"Replace Result: ";
  replace_helper(testStr,varMap);
  cout<<testStr<<endl;
}
int main(void){
  myShell newShell;
  map<string,string> varMap;
  varMap["abc123"] = "xterm";
  varMap["cock"] = "????";
  varMap["shit"] = "notFancy";
  varMap["empty"];
  string toReplace1("$abc123");
  string toReplace2("$abc123456");
  string toReplace3("$abc123-456");
  string toReplace4("someshit$abc123");
  string toReplace5("other$shit-%^$cock");
  string toReplace6("Barry$empty");
  string toReplace7("$$abc123");
  string toReplace8("$$$$abc123");
  string toReplace9("$123$abc123");
  
  printTestResult(1,toReplace1,varMap);
  printTestResult(2,toReplace2,varMap);
  printTestResult(3,toReplace3,varMap);
  printTestResult(4,toReplace4,varMap);
  printTestResult(5,toReplace5,varMap);
  printTestResult(6,toReplace6,varMap);
  printTestResult(7,toReplace7,varMap);
  printTestResult(8,toReplace8,varMap);
  printTestResult(9,toReplace9,varMap);
  return(EXIT_SUCCESS);
}
