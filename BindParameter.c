/**********************************************************************
* FILENAME :        BindParameter.c
*
* DESCRIPTION :
*       Example uses SQLBindParameter to insert a record
*       into a table
*
* ODBC USAGE :
*       SQLBindParameter - to bind data areas to parameter marker in
*                          the INSERT
*       SQLPrepare       - to prepare the INSERT for execution
*       SQLExecute       - to run the INSERT
*
*/
#include <stdio.h>
#include <stdlib.h>
#include <sql.h>
#include <sqlext.h>
#include <string.h>

#include "util.c"

#define PERSONID_LEN  2
#define LASTNAME_LEN  255
#define FIRSTNAME_LEN 255
#define ADDRESS_LEN 255
#define CITY_LEN  255

SQLHENV   henv  = SQL_NULL_HENV;   // Environment
SQLHDBC   hdbc  = SQL_NULL_HDBC;   // Connection handle
SQLHSTMT  hstmt = SQL_NULL_HSTMT;  // Statement handle
SQLRETURN retcode;

SQLLEN cPersonId;
SQLCHAR strFirstName[FIRSTNAME_LEN];
SQLCHAR strLastName[LASTNAME_LEN];
SQLCHAR strAddress[ADDRESS_LEN];
SQLCHAR strCity[CITY_LEN];
SQLLEN lenFirstName=0, lenLastName=0, lenAddress=0, lenCity=0;

SQLSMALLINT     NumParams;

int main () {
    // Allocate environment
    retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
    CHECK_ERROR(retcode, "SQLAllocHandle(SQL_ATTR_ODBC_VERSION)",
                henv, SQL_HANDLE_ENV);

    // Set ODBC Version
    retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION,
                            (SQLPOINTER*)SQL_OV_ODBC3, 0);
    CHECK_ERROR(retcode, "SQLSetEnvAttr(SQL_ATTR_ODBC_VERSION)",
                henv, SQL_HANDLE_ENV);

    // Allocate Connection
    retcode = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);
    CHECK_ERROR(retcode, "SQLAllocHandle(SQL_HANDLE_DBC)",
                hdbc, SQL_HANDLE_DBC);

    // Set Login Timeout
    retcode = SQLSetConnectAttr(hdbc, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0);
    CHECK_ERROR(retcode, "SQLSetConnectAttr(SQL_LOGIN_TIMEOUT)",
                hdbc, SQL_HANDLE_DBC);

    // Connect to DSN
    retcode = SQLConnect(hdbc, (SQLCHAR*) "DATASOURCE", SQL_NTS,
                         (SQLCHAR*) NULL, 0, NULL, 0);
    CHECK_ERROR(retcode, "SQLConnect(DATASOURCE)",
                hdbc, SQL_HANDLE_DBC);

    // Allocate Statement Handle
    retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
    CHECK_ERROR(retcode, "SQLAllocHandle(SQL_HANDLE_STMT)",
                hstmt, SQL_HANDLE_STMT);

    // Bind Parameters to all fields
    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR,
                    SQL_CHAR, FIRSTNAME_LEN, 0, strFirstName, FIRSTNAME_LEN,
                    &lenFirstName);
    retcode = SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR,
                    SQL_CHAR, LASTNAME_LEN, 0, strLastName, LASTNAME_LEN,
                    &lenLastName);
    retcode = SQLBindParameter(hstmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR,
                    SQL_CHAR, ADDRESS_LEN, 0, strAddress, ADDRESS_LEN,
                    &lenAddress);
    retcode = SQLBindParameter(hstmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR,
                    SQL_CHAR, CITY_LEN, 0, strCity, CITY_LEN,
                    &lenCity);

    retcode = SQLPrepare(hstmt, (SQLCHAR*)"INSERT INTO TestTBL1"
                        "(FirstName, LastName, Address, City)"
                        "VALUES (?, ?, ?, ?)", SQL_NTS);

    CHECK_ERROR(retcode, "SQLSetEnvAttr(SQL_ATTR_ODBC_VERSION)",
                henv, SQL_HANDLE_ENV);

    SQLNumParams(hstmt, &NumParams);
    CHECK_ERROR(retcode, "SQLSetEnvAttr(SQL_ATTR_ODBC_VERSION)",
                hstmt, SQL_HANDLE_ENV);

    printf ("Num params : %i\n", NumParams);
    // Setup data and lengths
    strcpy(strFirstName, "John"); lenFirstName=strlen(strFirstName);
    strcpy(strLastName, "Smith"); lenLastName=strlen(strLastName);
    strcpy(strAddress, "Laira");  lenAddress=strlen(strAddress);
    strcpy(strCity, "Plymouth");  lenCity=strlen(strCity);

    retcode = SQLExecute(hstmt);
    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
        printf ("Status : Success\n");
    } else {
        CHECK_ERROR(retcode, "SQLExecute()", hstmt, SQL_HANDLE_STMT);
    }

exit:

    printf ("\nComplete.\n");

    // Free handles
    // Statement
    if (hstmt != SQL_NULL_HSTMT)
        SQLFreeHandle(SQL_HANDLE_STMT, hstmt);

    // Connection
    if (hdbc != SQL_NULL_HDBC) {
        SQLDisconnect(hdbc);
        SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
    }

    // Environment
    if (henv != SQL_NULL_HENV)
        SQLFreeHandle(SQL_HANDLE_ENV, henv);

    return 0;
}