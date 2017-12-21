
all: SQLBindColtest SQLInsertColtest

SQLBindColtest: SQLBindColtest.c
	cc -m64 -g -I/usr/include -o SQLBindColtest SQLBindColtest.c -L/usr/lib -lodbc 

SQLInsertColtest: SQLInsertColtest.c
	cc -m64 -g -I/usr/include -o SQLInsertColtest SQLInsertColtest.c -L/usr/lib -lodbc 
