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

    int FIRSTNAME_LEN = 20;
    SQLCHAR strFirstName[FIRSTNAME_LEN];
    SQLLEN lenFirstName = 0;

    SQLINTEGER lParam1;
    SQLLEN lParam1Ind = 0;

    SQL_TIMESTAMP_STRUCT datetime2;
    SQLLEN cbdatetime2;   // size of datetime2  

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
                    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT,
                                               SQL_C_CHAR, SQL_CHAR, FIRSTNAME_LEN, 0,
                                               strFirstName, FIRSTNAME_LEN,
                                               &lenFirstName);

                    retcode = SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT,
                                               SQL_C_SLONG, SQL_INTEGER, 0, 0,
                                               &lParam1, sizeof(lParam1),
                                               &lParam1Ind);
                    
                    retcode = SQLBindParameter(hstmt, 3, SQL_PARAM_INPUT, 
                                                SQL_C_TIMESTAMP, SQL_TYPE_TIMESTAMP, 27, 7, 
                                                &datetime2, 0, &cbdatetime2);  

                    retcode = SQLPrepare(hstmt, (SQLCHAR *)"INSERT INTO LIGHTS_DATA (MAC_ADDRESS, LIGHT_VALUE, capture_time) VALUES (?, ?, ?)", SQL_NTS);

                    SQLNumParams(hstmt, &NumParams);

                    strcpy(strFirstName, "John");
                    lenFirstName = strlen(strFirstName);
                    lParam1 = 10;
                    lParam1Ind = sizeof(lParam1);

                    // Initialize the datetime2 structure  

                    time_t rawtime;
                    time(&rawtime);

                    struct tm * timeinfo;

                    timeinfo = localtime (&rawtime);
                    
                    /*
                    datetime2.year = timeinfo-> tm_year;  
                    datetime2.month = timeinfo->tm_mon;  
                    datetime2.day = timeinfo->tm_mday;  
                    datetime2.hour = timeinfo->tm_hour;  
                    datetime2.minute = timeinfo->tm_min;  
                    datetime2.second = timeinfo->tm_sec;  
                    */

                    datetime2.year = 2018;  
                    datetime2.month = 1;  
                    datetime2.day = 22;  
                    datetime2.hour = 5;  
                    datetime2.minute = 12;  
                    datetime2.second = 26;
                    // datetime2.fraction = 100;

                    cbdatetime2 = sizeof(SQL_TIMESTAMP_STRUCT);

                    retcode = SQLExecute(hstmt);

                    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
                    {
                        printf("Status : Success\n");
                    }
                    else
                    {
                        CHECK_ERROR(retcode, "SQLExecute()", hstmt, SQL_HANDLE_STMT);
                    }

                    /*
              // Process data
               if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
                  SQLCancel(hstmt);
                  SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
               }

               SQLDisconnect(hdbc);
               */
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