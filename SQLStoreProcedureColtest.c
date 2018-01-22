#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlext.h>
#include <sql.h>
#include <time.h>

#include "util.h"

#define NAME_LEN 50
#define PHONE_LEN 20

void show_error()
{
    printf("errorn");
}

int main()
{
    SQLHENV henv;
    SQLHDBC hdbc;
    SQLHSTMT hstmt = 0;
    SQLRETURN retcode;

    SQLSMALLINT NumParams;

    int MAC_ADDRESS_LEN = 20;

    SQLCHAR strMacAddress[MAC_ADDRESS_LEN];
    SQLLEN lenMacAddress = 0;

    SQLINTEGER intTensione;
    SQLLEN lenIntTensione = 0;

    SQL_TIMESTAMP_STRUCT datetime2;
    SQLLEN cbdatetime2;   // size of datetime2  

    SQLINTEGER intTipoMisura;
    SQLLEN lenIntTipoMisura = 0;

    int SERVICE_NAME_LEN = 20;
    
    SQLCHAR strServiceName[SERVICE_NAME_LEN];
    SQLLEN lenServiceName = 0;

    // output param
    SWORD sParm1 = 0, sParm2 = 1;  
    SQLLEN cbParm1 = SQL_NTS;  
    SQLLEN cbParm2 = SQL_NTS;  

    // Allocate environment handle
    retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);

    // Set the ODBC version environment attribute
    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
    {
        retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER *)SQL_OV_ODBC3, 0);

        // Allocate connection handle
        if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
        {
            retcode = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);

            // Set login timeout to 5 seconds
            if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
            {
                SQLSetConnectAttr(hdbc, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0);

                // Connect to data source
                retcode = SQLConnect(hdbc, (SQLCHAR *)"MSSQLTest", SQL_NTS, (SQLCHAR *)"SA", 2, (SQLCHAR *)"Allix2010", 9);

                // Allocate statement handle
                if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
                {
                    retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);

                    // Bind Parameters to all fields
                    // MAC TO DO
                    retcode = SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT,
                                               SQL_C_CHAR, SQL_CHAR, MAC_ADDRESS_LEN, 0,
                                               strMacAddress, MAC_ADDRESS_LEN,
                                               &lenMacAddress);
                    retcode = SQLBindParameter(hstmt, 3, SQL_PARAM_INPUT,
                                               SQL_C_SLONG, SQL_INTEGER, 0, 0,
                                               &intTensione, sizeof(intTensione),
                                               &lenIntTensione);
                    
                    retcode = SQLBindParameter(hstmt, 4, SQL_PARAM_INPUT, 
                                                SQL_C_TIMESTAMP, SQL_TYPE_TIMESTAMP, 27, 7, 
                                                &datetime2, 0, &cbdatetime2);  
                    // tipo misura
                    retcode = SQLBindParameter(hstmt, 5, SQL_PARAM_INPUT,
                                               SQL_C_SLONG, SQL_INTEGER, 0, 0,
                                               &intTipoMisura, sizeof(intTipoMisura),
                                               &lenIntTipoMisura);
                    // service name
                    retcode = SQLBindParameter(hstmt, 6, SQL_PARAM_INPUT,
                                               SQL_C_CHAR, SQL_CHAR, MAC_ADDRESS_LEN, 0,
                                               strServiceName, MAC_ADDRESS_LEN,
                                               &lenServiceName);
                    
                    
                    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_OUTPUT, 
                                                SQL_C_SSHORT, SQL_INTEGER, 0, 0, 
                                                &sParm1, 0, &cbParm1);  
                   

                    printf("SONO QUI\n");

                    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
                    {
                        printf("Status : Success1\n");
                    }
                    else
                    {
                        CHECK_ERROR(retcode, "SQLBindParameter()", hstmt, SQL_HANDLE_STMT);
                    }

                    /*
                    @macAddress VARCHAR(20), 
	                @tensione NUMERIC(19, 4), 
	                @dataRilevazione DATETIME,
	                @tipoMisura INT, 
	                @serviceName NVARCHAR(50)
                    */

                    // {? = CALL AxCreateLightMeasure (?,?, ?, ?, ?)}

                    SQLNumParams(hstmt, &NumParams);
                    
                    printf("NUM PARAMS: %d\n", NumParams);
                    // initialize values

                    // MAC_ADDRESS
                    strcpy(strMacAddress, "MAC12312444");
                    lenMacAddress = strlen(strMacAddress);

                    //TENSIONE
                    intTensione = 10;
                    lenIntTensione = sizeof(intTensione);

                    // Initialize the datetime2 structure  
                    time_t rawtime;
                    time(&rawtime);

                    struct tm * timeinfo;

                    timeinfo = localtime (&rawtime);
                    
                    datetime2.year = timeinfo-> tm_year + 1900;  
                    datetime2.month = timeinfo->tm_mon + 1;  
                    datetime2.day = timeinfo->tm_mday;  
                    datetime2.hour = timeinfo->tm_hour;  
                    datetime2.minute = timeinfo->tm_min;  
                    datetime2.second = timeinfo->tm_sec;  

                    // datetime2.fraction = 100;

                    cbdatetime2 = sizeof(SQL_TIMESTAMP_STRUCT);

                    // tipo misura
                    intTipoMisura = 20;
                    lenIntTipoMisura = sizeof(intTipoMisura);

                    // service name
                    strcpy(strServiceName, "TEST_SERVICE_NAME");
                    lenServiceName = sizeof(strServiceName);

                    // "{? = CALL [dbo].[AxCreateLightMeasure](?,?, ?, ?, ?)}"
                    retcode = SQLExecDirect(hstmt, (UCHAR*)"{? = CALL [dbo].[AxCreateLightMeasure] (?,?, ?, ?, ?)}", SQL_NTS);

                    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
                    {
                        printf("Status : Success\n");
                    }
                    else
                    {
                        CHECK_ERROR(retcode, "SQLExecute()", hstmt, SQL_HANDLE_STMT);
                    }
                    
                    printf("Before result sets cleared: RetCode = %d, OutParm = %d.\n", sParm1, sParm2);

                    // Clear any result sets generated.  
   
   while ( ( retcode = SQLMoreResults(hstmt) ) != SQL_NO_DATA )  {
       printf("SONO IN WHILE\n");
   }
        
   

   // Show parameters are now filled.  
   printf("After result sets drained: RetCode = %d, OutParm = %d.\n", sParm1, sParm2);  

                }
                else
                {
                    printf("SONO ERROR %d\n", retcode);
                }

                SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
            }
        }
        SQLFreeHandle(SQL_HANDLE_ENV, henv);
    }

exit:

    printf("\nComplete.\n");

    // Free handles
    // Statement
    if (hstmt != SQL_NULL_HSTMT)
    {
        SQLCancel(hstmt); // MY ADDITION
        SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
    }

    // Connection
    if (hdbc != SQL_NULL_HDBC)
    {
        SQLDisconnect(hdbc);
        SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
    }

    // Environment
    if (henv != SQL_NULL_HENV)
        SQLFreeHandle(SQL_HANDLE_ENV, henv);

    return 0;
}