This txt file is used to show all the test cases that I come up with.


STEP1: SOME WORDS BEFORE WE BEGIN
- First of all, You can find all of the test cases in ./testMyShell directory. There are 37 test files in that folder, each of which contains one or multiple commands that I would like to test with. To make your life easy, open Description file in the same folder. In this file, I map each test file into specific name of what command(s) I am testing so that it is more human readable. Then please pay attention to another folder ./TEST_HERE. Inside of this folder, I wrote some files which will be useful to see the effect of serveral commands in couple of tests(redirection,rm,mv,cp).Also all the redirection test results will be found inside of this foler(After you type the command).

- Secondly, I wrote serveral tiny programs to test some of the commands. They are the following:
 i.   parseArgument
 ii.  sayHi
 iii. helloWorld
 iv.  printHelloWorld
 v.   kill
 
NOTE: You can find the code of these programs in the corresponding cpp file. We will come to these programs in the upcoming test journey.

- Thirdly, I wrote a ./run_all.sh bash script to run all the test cases in myShell and format the test results into a file called ./test_result.txt. When you are testing, you can REFERENCE to the input and output format in ./test_result.txt

* You DO NOT NEED to run ./run_all.sh.
* You SHOULD test all of the test cases by manually type them in myShell

WARNING: One of the restriction of runing ./run_all.sh is that env command can't show the OLDPWD env var in the env list because it is running myShell in a bash script. However, if you type in the command mannually, this won't be the problem. When you are checking the output of command to the result in test_result.txt, please take this point into consideration.


STEP2: CONFIGURATION
myShell consists of nine seperate files, they are:
 i.     myShell.h   (header file)
 ii.    myShell.cpp (Top level entity,including main)
 iii.   parseInput.cpp (step1 and step3_set)
 iv.    changeDIR.cpp  (step3_cd)
 v.     findProgram.cpp (step2)
 vi.    accessVar.cpp  (step3)
 vii.   redirPipe.cpp  (step4_redirection)
 viii.  doAllButDir.cpp (step4_pipeline)
 xi.    pipeProgram.cpp (step4_pipeline)

- To make it easier for you to find the implementation of function when you are reading my code, I provide a list of function implementation in each cpp file:

parseInput.cpp:
- appendEscape
- dealEscape
- seperate
- str2cstr
- storeArgv
- isValidKey
- setCommand
- parse


changeDIR.cpp:
-PWD
-changeDIR


findProgram.cpp:
-cstr2str
-relative2Absolute
-walkThroughDIR
-extractDIR
-isPath
-replaceRealPath
-findYourName
-replaceRealProgram


accessVar.cpp:
-replace_helper
-replaceVar
-split
-addEnvp
-exportVar


redirPipe.cpp:
-manfd
-direct_op
-executeRedir
-redirect_helper
-redirect

pipeProgram.cpp:
-pipePrograms

doAllButDir.cpp:
-doAllButDir


STEP3: MAKE
 - In bash, type make and then hit enter. You should see five executeable files genreated:
 i.      myShell
 ii.     parseArgument
 iii.    helloWorld
 iv.     printHelloWorld
 v.      kill
 - Open myShell, you should see the following prompt:
 myShell: /home/yz395/ece551/mp_miniproject $


 - Now we are ready to test, enjoy.


STEP4: TEST

(1) kill signal and exit (test01)
-Look up the program kill.cpp. The program throws an exception but without try...catch clause. So the exception will progagate out of main and call terminate() to kill itself. myShell should print: program was killed by signal X

-I assume you already know the behavior of exit command

(2) User enter ctrl+D (test02)

(3) User hit enter multiple times(test03)

(4) test Argument parsing (test04)
-Look up the program parseArgument.cpp. The functionality of this program is to print all of the command line arguments to stdout followed by the number of spaces and tabs that appears in this argument.
-Look up test04. You should type the same commands line by line as those in test04

For example:
You can type:
      ./parseArgument ./testArg3 a \  b

in myShell and hit enter. You will see the following output:
      argv[0]: ./parseArgument (space = 0, tab = 0 )
      argv[1]: ./testArg3 (space = 0, tab = 0 )
      argv[2]: a (space = 0, tab = 0 )
      argv[3]:   (space = 1, tab = 0 )
      argv[4]: b (space = 0, tab = 0 )
      Program exited with status 0

NOTE: I design myShell in such way that it only deals with whitespaces(tab and space), which means slash followed by characters other than tab and space won't escape. This is not like bash.

(5) ls command (test05)
-I assume that you already know the behaviour of ls


(6) echo command (test06)
-I assume that you already know the behaviour of echo


(7) clear command (test07)
-I assume that you already know the behaviour of clear

(8) make command (test08)
-I assume that you already know the behaviour of make

NOTE: Hopefully you didn't modify any of the cpp files so that make will output the following:
      	make: 'myShell' is up to date

(9) rm command (test09)
-There is one file called file2Remove in ./TEST_HERE folder. After you type rm ./TEST_HERE/file2Remove, this file should be deleted.


(10) mv command (test10)
-There is one file called file2Move in ./TEST_HERE folder. After you type in the first line, file2Move will disappear and be moved to fileMoved

(11) cp command (test11)
-There is one file called file2Copy in ./TEST_HERE folder.
- I assume you already know the behaviour of cp


(12) env command (test12)
-Assume that you know.


(13) slash Program (test13)

NOTE: For the last line ./sayHi, look up the sayHi.cpp source file, the functionality of this program is super simple, printing one line to stdout and one line to stderr.

(14) cd command (test14)

- I assume you already know


(15) set command (test15-24)
- I assume you already know

NOTE:
 -For test22, I design in such way that $ followed by any non-letters and non-numbers and non-underscored such as '$&*#!@' will be replaced by ""

 - '$' followed by whitespaces will also be interpreted as ""

For example:
	echo $-
	myShell: /home/yz395/ece551/mp_miproject $

 - echo $System Environment Var will replace it with the initial value in the environment list



(16) export command (test25-26)

NOTE: I design export in such way that:

      i.For new var that never appear in the environment list before:
       -set var will change their value but they won't be added into environment list unless you use export explicitly.

      ii.For var that already exists in the environment list (like PATH)
      -set var will change their value and the value in the environment list will be updated at the same time without export
 
(17) redirection (test27-30)

-For these four tests, you should look up two cpp files and one txt file:
     	   -sayHi (Hopefully you remember what it does)
	   -helloWorld(*)
	   -./TEST_HERE/input_exist.txt(#)
	   -./TEST_HERE/output_exist.txt(##)
	   -./TEST_HERE/error_exist.txt(###)
, knowing what they do in order to understand the test result.

(*): helloWorld reads one line from stdin and then output it to stdout. After that it output argc and all ofthe argvs it reads(one per line)

(#): there is one line:"redirect stdin to input_exist in that file".
(##): Nothing in this file, used to redirect stdout
(###): Nothing in this file, used to redirect stderr
NOTE:
 I design redirection in such way that:
  i.  It supports redirection symbol without space
         ./myProgram<input>output

  ii. 2> only supports two foramts:
        -(1) divided by space: ./myProgram 2> output
	-(2) At the beginning of one argument:
	     ./myProgram 2>output
      ./myProgram2>output will be interpreted as
      ./myProgram2 > output

  iii. If multiple '>'s appear, myShell will create files for each '>', but only the file followd by last '>' will be the true destination of output:
     ./myProgram >output1 >output2
     create output1 and output2 and redirect stdout to output2

  iv. If multiple '<'s appear, myShell will inspect if any of the "in" redirect file doesn't exist. If any, then redirection stops and myShell will print error message:
      -myShell: input: No such file or directory

      If all of the files exist, myShell will choose to operate "in" redirection at the last file

   v. If redirection fails, none of the ">","2>" redirection files will be created


  vi. The following format are considered as syntax error:
     ./myProgram > output.txt <>
     ./myProgram > output.txt <
     
 vii. In the case below, arg1,arg2,arg3 will be treated as three command line arguments of myProgram
      ./myProgram arg1>output.txt arg2 arg3<input.txt
      
Open test27-30 and type in the command into myShell manually, comparing the result to test_result.txt
      
NOTE: If you do the same as what test file designates, you should look for the output file in ./TEST_HERE directory





(18) pipeline command (test31-36)
 

-For these six tests, you should look up two cpp files and two txt files:
     	   -helloWorld 
	   -printHelloWorld (*)
	   -./TEST_HERE/input_exist.txt
, knowing what they do in order to understand the test result.
  	   -./TEST_HERE/output_exist.txt

(Hopefully you remember what they do)

(*) printHelloWorld output all things that it reads from its stdin.

I design my pipeline functionality in such way that
  1. in-built command won't affect parent process.(They run in seperate child processes)That is:
  - cd | ls won't change current working directory
  - set ABC123 SOMETHING | wc won't set the value for ABC123 in myShell
  - exit| ls won't exit myShell

  2. it supports no space mode:
  - ./myProgram1|./myProgram2

  3. The following formats are considered as illegal format:
  - ./myProgram || ./myProgram2
  - ./myProgram |
  - |
  
  4. If you have n pipes(|), there will be n + 1 child processes, so there will be n + 1 status messages
     program exits with status X

(19) rmdir command (test37)

- I assume you know

 
STEP5: AND BEYOND

Thank you for reading this tedious and boring TESTING.txt file. Please give my as much feedback as possible. This will help me improve my programming skills in my future study. ECE551 is a flipped class with intense pace, which is annoying and tiring, but I definitely learn a lot from this course. It's painful but with a lot of fun. Let's meet in the final exam! Best wishes for all the TAs and instructors. :)


Hugo Zhang
12.02.2017
