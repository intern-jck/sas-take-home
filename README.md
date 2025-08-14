# sas take home

## Justin C Kirk
## 8/10/2025

### Overview

Take home assignment for SAS final round

Compile using gcc on Windows 11
```
gcc .\odbcdemo.c -o odbcdemo -lodbc32
```

Repo answers the following questions.

Question 1: 

Different data base engines have different definitions for string manipulation functions such as getting a substring for example. Supposing that DBMS1 uses substr, DBMS2 uses substring, and DBMS3 uses sbstr, can you write a function using C that would take a query and the DBMS as a parameter and rebuild the query using the adequate function for that particular engine?

*Please list out/document your assumptions

1. We want to create a substring query based on a database's substring query syntax.
2. We can create a few variables to pass to this function
3. The function will create a formated substring query based on the dbms type

For a draft of the function, see `dbms_substring.h` and `dbms_substring.c`

Question 2:

Using the Microsoft ODBC API Reference please find the issues with the following c based odbc demo application.

Issues Found
* Formatted code for better readability
    * Added spaces between blocks of code
    * Formatted for column width of about 80
    
* Added some header files which were missing
```
    #include <windows.h>
    #include <stdint.h>
    #include <sql.h>
    #include <sqlext.h>
    #include <sqltypes.h>
```

* Connection handle was not allocated
```
   rc = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);
    if ((rc != SQL_SUCCESS) && (rc != SQL_SUCCESS_WITH_INFO))
    {
        printf("Unable to allocate connection\n");
        // use EXIT_FAILURE code, 255 is not very clear
        // exit(255);
        exit(EXIT_FAILURE);
    }
```

* Added a few missing params in SQLConnect()
    * used driver for ServerName and SQL_NTS for NameLength1

* Since `SQL_OV_ODBC3` is passed to `SQLSetEnvAttr`, ODBC v3.x is assumed to be used
    * SQLError is depreciated in ODBC 3.0
        * Replaced with SQLGetDiagRec
    * SQLFreeStmt is depreciated in ODBC v3.x
        * Replaced with SQLFreeHandle(SQL_HANDLE_STMT, hstmt)

* Added `SQLFreeHandle` function to free statement handle in `EnvClose`
```
void EnvClose(SQLHANDLE henv, SQLHANDLE hdbc, SQLHANDLE hstmt)
{
    SQLDisconnect(hdbc);
    SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
    SQLFreeHandle(SQL_HANDLE_ENV, henv);
    SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
}
```

* Cleaned up code smells found throughout


MS ODBC API reference:

https://learn.microsoft.com/en-us/sql/odbc/reference/syntax/odbc-api-reference?view=sql-server-ver16


Function References

C Data Types
https://learn.microsoft.com/en-us/sql/odbc/reference/appendixes/c-data-types?view=sql-server-ver17

SQLError DEPRECIATED IN ODBC 3.0
https://learn.microsoft.com/en-us/sql/odbc/reference/syntax/sqlerror-function?view=sql-server-ver17

SQLGetDiagRec
https://learn.microsoft.com/en-us/sql/odbc/reference/syntax/sqlgetdiagrec-function?view=sql-server-ver17

SQLHANDLE
https://learn.microsoft.com/en-us/sql/odbc/reference/develop-app/handles?view=sql-server-ver17

SQLDisconnect
https://learn.microsoft.com/en-us/sql/odbc/reference/syntax/sqldisconnect-function?view=sql-server-ver17

SQLFreeHandle
https://learn.microsoft.com/en-us/sql/odbc/reference/syntax/sqlfreehandle-function?view=sql-server-ver16

SQLAllocHandle
https://learn.microsoft.com/en-us/sql/odbc/reference/syntax/sqlallochandle-function?view=sql-server-ver17

SQLSetEnvAttr
https://learn.microsoft.com/en-us/sql/odbc/reference/syntax/sqlsetenvattr-function?view=sql-server-ver17

SQLConnect
https://learn.microsoft.com/en-us/sql/odbc/reference/syntax/sqlconnect-function?view=sql-server-ver17

SQLGetInfo
https://learn.microsoft.com/en-us/sql/odbc/reference/syntax/sqlgetinfo-function?view=sql-server-ver17

SQLGetTypeInfo
https://learn.microsoft.com/en-us/sql/odbc/reference/syntax/sqlgettypeinfo-function?view=sql-server-ver17

SQLBindCol
https://learn.microsoft.com/en-us/sql/odbc/reference/syntax/sqlbindcol-function?view=sql-server-ver17

SQLFetch
https://learn.microsoft.com/en-us/sql/odbc/reference/syntax/sqlfetch-function?view=sql-server-ver17

SQLFreeStmt
https://learn.microsoft.com/en-us/sql/odbc/reference/syntax/sqlfreestmt-function?view=sql-server-ver17