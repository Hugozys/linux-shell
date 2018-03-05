CXX = g++ -o $@
CPP = g++ -std=gnu++98 -ggdb3 -Wall -Werror -pedantic -c $<
SRCS = myShell.cpp forkAndExecve.cpp parseInput.cpp findProgram.cpp changeDIR.cpp accessVar.cpp redirPipe.cpp doAllButDir.cpp pipeProgram.cpp
OBJS = $(patsubst %.cpp, %.o, $(SRCS))
.PHONY: clean depend
all: parseArgument printHelloWorld helloWorld myShell sayHi kill

kill: kill.o
	$(CXX) kill.o

sayHi: sayHi.o
	$(CXX) sayHi.o

parseArgument: parseArgument.o
	$(CXX) parseArgument.o

printHelloWorld: printHelloWorld.o
	$(CXX) printHelloWorld.o


helloWorld: helloWorld.o
	$(CXX) helloWorld.o


myShell: $(OBJS) 
	$(CXX) $(OBJS)

%.o : %.cpp
	$(CPP) 

clean:
	rm -f *.o *~ *# *.bak myShell parseArgument printHelloWorld helloWorld sayHi kill
depend:
	makedepend $(SRCS)


myShell.o : myShell.h
forkAndExecve.o: myShell.h
parseInput.o: myShell.h
findProgram.o: myShell.h
changeDIR.o: myShell.h
accessVar.o: myShell.h
redirPipe.o: myShell.h
pipeProgram.o: myShell.h
doAllButDir.o: myShell.h
