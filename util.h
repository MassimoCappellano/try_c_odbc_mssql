#ifndef _UTIL_TRY_ODBC_H
#define _UTIL_TRY_ODBC_H

#include <sqlext.h>
#include <sql.h>

#define CHECK_ERROR(e, s, h, t) ({\
            if (e!=SQL_SUCCESS && e != SQL_SUCCESS_WITH_INFO) {extract_error(s, h, t); goto exit;} \
})

void extract_error(char *fn, SQLHANDLE handle, SQLSMALLINT type);

#endif
