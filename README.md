# ESEMPIO

https://blogs.msdn.microsoft.com/sqlblog/2012/01/26/use-existing-msdn-c-odbc-samples-for-microsoft-linux-odbc-driver/

https://stackoverflow.com/questions/33020646/gcc-odbc-on-linux-is-not-linking

https://www.easysoft.com/developer/languages/c/odbc_tutorial.html

```
massimo@massimo-VirtualBox:~/workspace/try_c_odbc_mssql$ isql -v MSSQLTest massimo massimo123#ANB
[IM002][unixODBC][Driver Manager]Data source name not found, and no default driver specified
[ISQL]ERROR: Could not SQLConnect
massimo@massimo-VirtualBox:~/workspace/try_c_odbc_mssql$
```

## CONFIGURE DATA SOURCE

https://docs.microsoft.com/en-us/sql/connect/odbc/linux-mac/connection-string-keywords-and-data-source-names-dsns

Prima configurare sotto home il file .odbc.ini come nell'esempio `.odbc.ini_example`

```
massimo@massimo-VirtualBox:~/workspace/try_c_odbc_mssql$isql -v MSSQLTest massimo massimo123#ABC
```