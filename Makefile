
all: SQLBindColtest SQLInsertColtest SQLStoreProcedureColtest OutputParams

SQLBindColtest: SQLBindColtest.c
	cc -m64 -g -I/usr/include -o SQLBindColtest SQLBindColtest.c -L/usr/lib -lodbc 

SQLInsertColtest: SQLInsertColtest.c util.h util.c
	cc -m64 -g -I/usr/include -o SQLInsertColtest util.c SQLInsertColtest.c  -L/usr/lib -lodbc 

SQLStoreProcedureColtest: SQLStoreProcedureColtest.c util.h util.c
	cc -m64 -g -I/usr/include -o SQLStoreProcedureColtest util.c SQLStoreProcedureColtest.c  -L/usr/lib -lodbc 

OutputParams: OutputParams.c util.h util.c
	cc -m64 -g -I/usr/include -o OutputParams util.c OutputParams.c  -L/usr/lib -lodbc 

clean:
	rm SQLBindColtest SQLInsertColtest SQLStoreProcedureColtest OutputParams
