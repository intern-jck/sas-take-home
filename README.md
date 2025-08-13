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


Question 1
Different data base engines have different definitions for string manipulation functions such as getting a substring for example. Supposing that DBMS1 uses substr, DBMS2 uses substring, and DBMS3 uses sbstr, can you write a function using C that would take a query and the DBMS as a parameter and rebuild the query using the adequate function for that particular engine?

*Please list out/document your assumptions


Question 2:

Using the Microsoft ODBC API Reference please find the issues with the following c based odbc demo application.

Issues Found
* formatted code for better readability
    * added spaces between blocks of code
    * formatted for column width of about 80
    
* added some haeder files which were missing
```
    #include <windows.h>
    #include <stdint.h>
    #include <sql.h>
    #include <sqlext.h>
    #include <sqltypes.h>
```

* added a few missing params in SQLConnect()
    * used driver for ServerName and SQL_NTS for NameLength1

* SQLError is depreciated in ODBC 3.0
    * Replaced with SQLGetDiagRec


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


SQLBindCol


EnvClose


SQLFetch


SQLFreeStmt
