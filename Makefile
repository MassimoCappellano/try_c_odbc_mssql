
all: SQLBindColtest SQLInsertColtest

SQLBindColtest: SQLBindColtest.c
	cc -m64 -g -I/usr/include -o SQLBindColtest SQLBindColtest.c -L/usr/lib -lodbc 

SQLInsertColtest: SQLInsertColtest.c util.h util.c
	cc -m64 -g -I/usr/include -o SQLInsertColtest util.c SQLInsertColtest.c  -L/usr/lib -lodbc 

clean:
	rm SQLBindColtest SQLInsertColtest
