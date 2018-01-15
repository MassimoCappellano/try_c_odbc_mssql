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

## ESEMPIO INSERT BIND PARAMETERS

https://www.easysoft.com/developer/languages/c/examples/BindParameter.html 

Here [BindParameter.c](BindParameter.c)

## ALL EXAMPLES

https://www.easysoft.com/developer/languages/c/examples/index.html

### EXAMPLE integer binding

http://docs.raima.com/rdme/9_1/Content/SQL/SQLBindParameter.htm

### TUTORIALS

[ODBC Applications: Writing Good Code](http://cdn.ttgtmedia.com/searchDataManagement/downloads/DataAccessHandbook_CH05.pdf)








