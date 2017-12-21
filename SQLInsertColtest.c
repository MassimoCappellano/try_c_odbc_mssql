#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlext.h>
#include <sql.h>

#define NAME_LEN 50
#define PHONE_LEN 20

void show_error() {
   printf("errorn");
}

int main() {
   SQLHENV henv;
   SQLHDBC hdbc;
   SQLHSTMT hstmt = 0;
   SQLRETURN retcode;

   SQLSMALLINT     NumParams;

   int FIRSTNAME_LEN = 20;
   SQLCHAR strFirstName[FIRSTNAME_LEN];
   SQLLEN lenFirstName=0;

   SQLINTEGER lParam1; 
   SQLLEN lParam1Ind = 0; 

   // Allocate environment handle
   retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);

   // Set the ODBC version environment attribute
   if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
      retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER*)SQL_OV_ODBC3, 0);

      // Allocate connection handle
      if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
         retcode = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);

         // Set login timeout to 5 seconds
         if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
            SQLSetConnectAttr(hdbc, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0);

            // Connect to data source
            retcode = SQLConnect(hdbc, (SQLCHAR*) "MSSQLTest", SQL_NTS, (SQLCHAR*) "SA", 2, (SQLCHAR*) "Allix2010", 9);

            // Allocate statement handle
            if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
               retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);

               // Bind Parameters to all fields
    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR,
                    SQL_CHAR, FIRSTNAME_LEN, 0, strFirstName, FIRSTNAME_LEN,
                    &lenFirstName);
    retcode = SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, 
                          				SQL_C_SLONG, SQL_INTEGER, 0, 0, 
                          				&lParam1, sizeof(lParam1), 
                          				&lParam1Ind);

    retcode = SQLPrepare(hstmt, (SQLCHAR*)"INSERT INTO LIGHTS_DATA (MAC_ADDRESS, LIGHT_VALUE, capture_time) VALUES (?, ?, CURRENT_TIMESTAMP)"
                        , SQL_NTS);

    SQLNumParams(hstmt, &NumParams);

    strcpy(strFirstName, "John"); lenFirstName=strlen(strFirstName);
    lParam1 = 10; lParam1Ind = sizeof(lParam1);

      retcode = SQLExecute(hstmt);

              // Process data
               if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
                  SQLCancel(hstmt);
                  SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
               }

               SQLDisconnect(hdbc);
            } else {
                  printf("SONO ERROR %d\n", retcode);
            }

            SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
         }
      }
      SQLFreeHandle(SQL_HANDLE_ENV, henv);
   }
} 