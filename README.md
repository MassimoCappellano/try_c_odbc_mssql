# TRY C ODBC MS SQL SERVER 

Start here:

https://blogs.msdn.microsoft.com/sqlblog/2012/01/26/use-existing-msdn-c-odbc-samples-for-microsoft-linux-odbc-driver/

https://stackoverflow.com/questions/33020646/gcc-odbc-on-linux-is-not-linking

https://www.easysoft.com/developer/languages/c/odbc_tutorial.html

## PREREQUISITE

[Installing the Microsoft ODBC Driver for SQL Server on Linux and macOS](https://docs.microsoft.com/en-us/sql/connect/odbc/linux-mac/installing-the-microsoft-odbc-driver-for-sql-server)  

[Install SQL Server and create a database on Ubuntu](https://docs.microsoft.com/en-us/sql/linux/quickstart-install-connect-ubuntu)

## CONFIGURE DATA SOURCE

Trying to connect to MS SQL SERVER:

```
massimo@massimo-VirtualBox:~/workspace/try_c_odbc_mssql$ isql -v MSSQLTest massimo massimo123#ANB
[IM002][unixODBC][Driver Manager]Data source name not found, and no default driver specified
[ISQL]ERROR: Could not SQLConnect
massimo@massimo-VirtualBox:~/workspace/try_c_odbc_mssql$
```
solution:  

https://docs.microsoft.com/en-us/sql/connect/odbc/linux-mac/connection-string-keywords-and-data-source-names-dsns

Create in the home directory a file `.odbc.ini` like in the example `.odbc.ini_example`.

```
massimo@massimo-VirtualBox:~/workspace/try_c_odbc_mssql$isql -v MSSQLTest massimo massimo123#ABC
```

## EXAMPLES

* [BindParameter.c](BindParameter.c) simple inserts;
* [SQLBindColtest](SQLBindColtest.c)  simple select;
* [SQLInsertColtest](SQLInsertColtest.c) insert in `LIGHTS_DATA` table;
* [SQLStoreProcedureColtest](SQLStoreProcedureColtest.c) call store procedure;
* [OutputParams](OutputParams.c) call store procedure;  

Schemas: [schema.sql](schema.sql), [schema_store_procedure.sql](schema_store_procedure.sql).

### TUTORIALS

https://www.easysoft.com/developer/languages/c/examples/BindParameter.html 

https://www.easysoft.com/developer/languages/c/examples/index.html

http://docs.raima.com/rdme/9_1/Content/SQL/SQLBindParameter.htm

[ODBC Applications: Writing Good Code](http://cdn.ttgtmedia.com/searchDataManagement/downloads/DataAccessHandbook_CH05.pdf)

[Use Date and Time Types](https://docs.microsoft.com/en-us/sql/relational-databases/native-client-odbc-how-to/use-date-and-time-types)

[Running Stored Procedures - Process Return Codes and Output Parameters](https://docs.microsoft.com/en-us/sql/relational-databases/native-client-odbc-how-to/running-stored-procedures-process-return-codes-and-output-parameters)

[Looking for one liner example how to bind and insert a null value into a database using ODBC API](https://stackoverflow.com/questions/6486746/looking-for-one-liner-example-how-to-bind-and-insert-a-null-value-into-a-databas)









