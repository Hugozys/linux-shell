CXX = g++ -std=gnu++98 -ggdb3 -Wall -Werror -pedantic -o $@  parseInput.cpp
FILE = parseInput.cpp myShell.h
COMMAND = g++ -std=gnu++98 -ggdb3 -Wall -Werror -pedantic -o $@  findProgram.cpp
COFILE = findProgram.cpp myShell.h
TEST = g++ -std=gnu++98 -ggdb3 -Wall -Werror -pedantic -o $@  $<
.PHONY: clean
all: seperate str2cstr storeArgv parseInput myShell replaceRealPath walkThroughDIR findYourName accessVar setCommand

parseArgument: parseArgument.cpp
	g++ -std=gnu++98 -Wall -Werror -pedantic -o $@ parseArgument.cpp
printHelloWorld: printHelloWorld.cpp
	g++ -std=gnu++98 -Wall -Werror -pedantic -o $@ printHelloWorld.cpp
seperate: $(FILE) seperate_test.cpp accessVar.cpp findProgram.cpp
	$(CXX) seperate_test.cpp accessVar.cpp findProgram.cpp

str2cstr: $(FILE) str2cstr_test.cpp
	$(CXX) str2cstr_test.cpp 

storeArgv: $(FILE) storeArgv_test.cpp
	$(CXX)  storeArgv_test.cpp 

parseInput: $(FILE) parseInput_test.cpp
	$(CXX) parseInput_test.cpp

helloWorld: helloWorld.cpp
	$(TEST)
sillyLoop: sillyLoop.cpp
	$(TEST)

myShell: myShell.h myShell.cpp forkAndExecve.cpp parseInput.cpp findProgram.cpp changeDIR.cpp accessVar.cpp redirPipe.cpp pipeProgram.cpp doAll.cpp 
	g++ -std=gnu++98 -ggdb3 -Wall -Werror -pedantic -o $@  parseInput.cpp myShell.cpp forkAndExecve.cpp findProgram.cpp changeDIR.cpp accessVar.cpp redirPipe.cpp pipeProgram.cpp doAll.cpp

# The above has been done



replaceRealPath: $(COFILE) replaceRealPath_test.cpp parseInput.cpp
	$(COMMAND) replaceRealPath_test.cpp parseInput.cpp

walkThroughDIR: $(COFILE) walkThroughDIR_test.cpp parseInput.cpp
	$(COMMAND) walkThroughDIR_test.cpp parseInput.cpp

findYourName: $(COFILE) findYourName_test.cpp parseInput.cpp
	$(COMMAND) findYourName_test.cpp parseInput.cpp


replaceRealProgram: $(COFILE) replaceRealProgram_test.cpp parseInput.cpp
	$(COMMAND) replaceRealProgram_test.cpp parseInput.cpp

# The above has been finished

setCommand: $(FILE) setCommand_test.cpp accessVar.cpp findProgram.cpp
	$(CXX) setCommand_test.cpp accessVar.cpp findProgram.cpp

accessVar: myShell.h accessVar.cpp accessVar_test.cpp parseInput.cpp findProgram.cpp
	$(TEST) accessVar.cpp accessVar_test.cpp parseInput.cpp findProgram.cpp

redirect_op: redirect_op_test.cpp redirPipe.cpp
	g++ -std=gnu++98 -Wall -Werror -pedantic -o $@ redirect_op_test.cpp redirPipe.cpp

restore: myShell.h  parseInput.cpp findProgram.cpp redirPipe.cpp restore_test.cpp accessVar.cpp
	g++ -std=gnu++98 -Wall -Werror -pedantic -o $@ parseInput.cpp findProgram.cpp redirPipe.cpp restore_test.cpp accessVar.cpp


clean:
	rm -f *~ *# seperate str2cstr storeArgv parseInput myShell replaceRealPath walkThroughDIR findYourName replaceRealProgram setCommand accessVar restore redriect_op 
