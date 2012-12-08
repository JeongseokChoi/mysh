mysh: mysh.o mysh_execute.h mysh_parse.h mysh_common.h
	gcc -o mysh mysh.o mysh_execute.o mysh_parse.o mysh_common.o

mysh.o: mysh.c\
	mysh_execute.h mysh_execute.o\
        mysh_parse.h   mysh_parse.o\
        mysh_common.h  mysh_common.o
	gcc -c mysh.c -g

mysh_execute.o: mysh_execute.h mysh_execute.c\
                mysh_common.h  mysh_common.c
	gcc -c mysh_execute.c -g

mysh_parse.o: mysh_parse.h mysh_parse.c
	gcc -c mysh_parse.c -g

mysh_common.o: mysh_common.h mysh_common.c
	gcc -c mysh_common.c -g

