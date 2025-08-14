// ODBC Headers
#include <windows.h>
#include <stdint.h>
#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>

// STD Lib Headers
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>

/*
** Define Some useful defines
*/

// Not needed.  NULL is defined in stdlib.h and stdio.h
// #if !defined(NULL)
// #define NULL 0
// #endif

/*
** function: ODBC_error
**
** Purpose: Display to stdout current ODBC Errors
**
** Arguments: henv _ ODBC Environment handle.
** hdbc - ODBC Connection Handle error generated on.
** hstmt - ODBC SQL Handle error generated on.
**
** Returns: void
**
*/
void ODBC_error(                 /* Get and print ODBC error messages */
                SQLHANDLE henv,  /* ODBC Environment */
                SQLHANDLE hdbc,  /* ODBC Connection Handle */
                SQLHANDLE hstmt) /* ODBC SQL Handle */
{
    UCHAR sqlstate[10];
    UCHAR errmsg[SQL_MAX_MESSAGE_LENGTH];
    SQLINTEGER nativeerr;
    SQLSMALLINT actualmsglen;
    RETCODE rc;

/*
Below could be rewritten using a while loop.
Something like:

    while(rc != SQL_ERROR) {
        rc = SQLGetDiagRec()
        if (rc == SQL_NO_DATA) {
            break;
        }
        // do logic
    }
    printf("SQLError failed!\n");
    return;
*/
loop:
    // SQLError is depreciated in ODBC 3.0
    // rc = SQLError(henv,
    //               hdbc,
    //               hstmt,
    //               (SQLCHAR *)sqlstate,
    //               &nativeerr,
    //               (SQLCHAR *)errmsg,
    //               SQL_MAX_MESSAGE_LENGTH - 1,
    //               &actualmsglen);

    /*
    SQLGetDiagRec maps to SQLError in ODBC 3.0
    SQLRETURN SQLGetDiagRec(
     SQLSMALLINT     HandleType,
     SQLHANDLE       Handle,
     SQLSMALLINT     RecNumber,
     SQLCHAR *       SQLState,
     SQLINTEGER *    NativeErrorPtr,
     SQLCHAR *       MessageText,
     SQLSMALLINT     BufferLength,
     SQLSMALLINT *   TextLengthPtr);
    */
    rc = SQLGetDiagRec(
        SQL_HANDLE_ENV,
        hdbc,
        1,
        (SQLCHAR *)sqlstate,
        &nativeerr,
        (SQLCHAR *)errmsg,
        SQL_MAX_MESSAGE_LENGTH - 1,
        &actualmsglen);

    if (rc == SQL_ERROR)
    {
        printf("SQLError failed!\n");
        return;
    }

    // SQL_NO_DATA_FOUND is returned by SQLError, not SQLGetDiagRec
    // if (rc != SQL_NO_DATA_FOUND)
    if (rc != SQL_NO_DATA)
    {
        printf("SQLSTATE = %s\n", sqlstate);
        printf("NATIVE ERROR = %d\n", nativeerr);
        errmsg[actualmsglen] = '\0';
        printf("MSG = %s\n\n", errmsg);
        goto loop;
    }
}

/*
** function: EnvClose
**
** Purpose: Frees environment and connection handles.
**
** Arguments: henv _ environment handle
** hdbc - connection to handle
*/

void EnvClose(SQLHANDLE henv, SQLHANDLE hdbc)
{
    SQLDisconnect(hdbc);
    // need to also free stmt handle
    SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
    SQLFreeHandle(SQL_HANDLE_ENV, henv);
}

/*
** function: fgets_wrapper
**
** Purpose: Handles newline for fgets from stdin.
**
** Arguments: buffer _ character array ptr
** buflen - max characters
*/

// Since buffer is passed as a pointer,
// this does not need to return anything.
// Could lead to a memory leak since it's returning buffer?
// char *fgets_wrapper(char *buffer, size_t buflen)
// {
//     if (fgets(buffer, buflen, stdin) != 0)
//     {
//         buffer[strcspn(buffer, "\n")] = '\0';
//         return buffer;
//     }
//     return 0;
// }

void fgets_wrapper(char *buffer, size_t buflen)
{
    if (fgets(buffer, buflen, stdin) != 0)
    {
        buffer[strcspn(buffer, "\n")] = '\0';
    }
}

/*
** Defines used by main program.
*/
#define PWD_LEN 32
#define UID_LEN 32
#define DSN_LEN 32
// This macro is only used once and not needed.
// #define USAGE_MSG1 "Usage: %s \n"

/*
** Program: odbc demo
**
** Purpose: ODBC Demo routine.
*/
typedef struct
{
    UCHAR charCol1[1024];
    // Could keep this since we cast length1 to SQLLEN anyway
    // Using long could cause issues if on 64 bit system
    // SQLLEN length1;
    long length1;
    short length2;
} DataInfoStruct;

// Why do we need an array of dataStructs if we only ever use element 0?
DataInfoStruct dataStruct[32];
DataInfoStruct dataStruct2[32];
DataInfoStruct dataStruct3[32];

int main(int argc, char *argv[])
{
    // These all shoudld be inialized to 0 or some value.
    // SQLHANDLE hdbc;
    // SQLHANDLE henv;
    // SQLHANDLE hstmt;
    // RETCODE rc;
    // UCHAR uid[UID_LEN];
    // UCHAR pwd[PWD_LEN];
    // UCHAR driver[DSN_LEN];
    // UCHAR ver[32];
    // SQLSMALLINT strLen;

    // i is an iterator, this is a code smell, unless C ver < 99
    // int i;

    // uid[0] = 0;
    // pwd[0] = 0;

    // Should also expliciting define handle types
    // SQLHDBC
    SQLHDBC hdbc = NULL;
    // SQLHENV
    SQLHENV henv = NULL;
    // SQLHSTMT
    SQLHSTMT hstmt = NULL;
    RETCODE rc = -1;
    UCHAR uid[UID_LEN] = {0};
    UCHAR pwd[PWD_LEN] = {0};
    UCHAR driver[DSN_LEN] = {0};
    UCHAR ver[32] = {0};
    SQLSMALLINT strLen = 0;

    // Not sure why this is needed.
    if (argc > 1)
    {
        // printf(USAGE_MSG1, argv[0]);
        // Parans not needed
        // return (1);
        printf("Usage: %s \n", argv[0]);
        return 1;
    }

    printf("\nEnter the DSN : ");
    // no need to cast as char pointers here.
    // fgets_wrapper((char *)driver, DSN_LEN);
    fgets_wrapper(driver, DSN_LEN);

    printf("\nEnter the UID : ");
    // fgets_wrapper((char *)uid, UID_LEN);
    fgets_wrapper(uid, UID_LEN);

    printf("\nEnter the PWD : ");
    // fgets_wrapper((char *)pwd, PWD_LEN);
    fgets_wrapper(pwd, PWD_LEN);

    printf("%s: will connect to data source '%s' as user '%s/%s'.\n",
           argv[0], driver, uid, pwd);

    rc = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
    if ((rc != SQL_SUCCESS) && (rc != SQL_SUCCESS_WITH_INFO))
    {
        printf("Unable to allocate environment\n");
        // use EXIT_FAILURE code, 255 is not very clear
        // exit(255);
        exit(EXIT_FAILURE);
    }

    // Sets environment to use ODBC ver 3
    rc = SQLSetEnvAttr(henv,
                       SQL_ATTR_ODBC_VERSION,
                       (SQLPOINTER)SQL_OV_ODBC3,
                       SQL_IS_INTEGER);

    // Must allocate connection handle before connecting
    rc = SQLConnect(hdbc,
                    (SQLCHAR *)driver,
                    SQL_NTS,
                    (SQLCHAR *)uid,
                    SQL_NTS,
                    (SQLCHAR *)pwd,
                    SQL_NTS);

    if ((rc != SQL_SUCCESS) && (rc != SQL_SUCCESS_WITH_INFO))
    {
        printf("SQLConnect: Failed...\n");
        ODBC_error(henv, hdbc, SQL_NULL_HSTMT);
        // exit(255); /* Exit with failure */
        exit(EXIT_FAILURE);
    }

    rc = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
    if ((rc != SQL_SUCCESS) && (rc != SQL_SUCCESS_WITH_INFO))
    {
        printf("Unable to Allocate a SQLHANDLE:\n");
        ODBC_error(henv, hdbc, hstmt);
        EnvClose(henv, hdbc);
        // exit(255);
        exit(EXIT_FAILURE);
    }

    rc = SQLGetInfo(hdbc, SQL_DRIVER_VER, (SQLPOINTER)ver, sizeof(ver), &strLen);
    if ((rc != SQL_SUCCESS) && (rc != SQL_SUCCESS_WITH_INFO))
    {
        printf("SQLGetInfo has Failed. RC=%d\n", rc);
        ODBC_error(henv, hdbc, hstmt);
    }

    printf("Driver version: %s\n", ver);
    printf("Calling SQLGetTypeInfo...\n");

    rc = SQLGetTypeInfo((SQLHSTMT)hstmt, SQL_ALL_TYPES);
    if ((rc != SQL_SUCCESS) && (rc != SQL_SUCCESS_WITH_INFO))
    {
        printf("SQLGetTypeInfo has Failed. RC=%d\n", rc);
        ODBC_error(henv, hdbc, hstmt);
        EnvClose(henv, hdbc);
        // exit(255);
        exit(EXIT_FAILURE);
    }

    rc = SQLBindCol(hstmt, 1, SQL_C_CHAR,
                    &dataStruct[0].charCol1[0],
                    (SDWORD)sizeof(dataStruct[0].charCol1),
                    (SQLLEN *)&dataStruct[0].length1);

    if ((rc != SQL_SUCCESS) && (rc != SQL_SUCCESS_WITH_INFO))
    {
        printf("SQLBindCol(1) has Failed. RC=%d\n", rc);
        ODBC_error(henv, hdbc, hstmt);
        EnvClose(henv, hdbc);
        // exit(255);
        exit(EXIT_FAILURE);
    }

    rc = SQLBindCol(hstmt, 4, SQL_C_CHAR,
                    &dataStruct2[0].charCol1[0],
                    (SDWORD)sizeof(dataStruct2[0].charCol1),
                    (SQLLEN *)&dataStruct2[0].length1);

    if ((rc != SQL_SUCCESS) && (rc != SQL_SUCCESS_WITH_INFO))
    {
        printf("SQLBindCol(4) has Failed. RC=%d\n", rc);
        ODBC_error(henv, hdbc, hstmt);
        EnvClose(henv, hdbc);
        // exit(255);
        exit(EXIT_FAILURE);
    }

    rc = SQLBindCol(hstmt, 5, SQL_C_CHAR,
                    &dataStruct3[0].charCol1[0],
                    (SDWORD)sizeof(dataStruct3[0].charCol1),
                    (SQLLEN *)&dataStruct3[0].length1);

    if ((rc != SQL_SUCCESS) && (rc != SQL_SUCCESS_WITH_INFO))
    {
        printf("SQLBindCol(5) has Failed. RC=%d\n", rc);
        ODBC_error(henv, hdbc, hstmt);
        EnvClose(henv, hdbc);
        // exit(255);
        exit(EXIT_FAILURE);
    }

    // Set to bogus
    dataStruct[0].length1 = -1;
    dataStruct2[0].length1 = -1;
    dataStruct3[0].length1 = -1;

    int count = 0;

    printf("Fetching result set...\n");
    while (SQLFetch(hstmt) == SQL_SUCCESS)
    {
        // char *ptr;
        // Initialize pointer to NULL
        char *ptr = NULL;
        if (count == 0)
        {
            printf("LITERAL PREFIX\n");
            printf("indicator(d): %d\n", dataStruct2[0].length1);
            printf("indicator(lld): %lld\n", dataStruct2[0].length1);
            printf("indicator(hex): ");

            /* assign to char so we can dump out each byte */
            ptr = (char *)&dataStruct2[0].length1;

            for (int i = 0; i < 8; i++)
            {
                printf("%x", ptr[i]);
            }
            printf("\n");
            // Ternaries should be kept short
            // Also, casting not needed
            // printf("%-32s\n\n", dataStruct2[0].length1 == SQL_NULL_DATA ? (UCHAR *)"NULL"
            //                                                             : dataStruct2[0].charCol1);

            // Better if replaced with if statement
            char *ds2Msg = "NULL";
            if (dataStruct2[0].length1 != SQL_NULL_DATA)
            {
                ds2Msg = dataStruct2[0].charCol1;
            }
            printf("%-32s\n\n", ds2Msg);

            printf("LITERAL SUFFIX\n");
            printf("indicator(d): %d\n", dataStruct3[0].length1);
            printf("indicator(lld): %lld\n", dataStruct3[0].length1);
            printf("indicator(hex): ");

            /* assign to char so we can dump out each byte */
            ptr = (char *)&dataStruct3[0].length1;
            for (int i = 0; i < 8; i++)
            {
                printf("%x", ptr[i]);
            }
            printf("\n");

            // printf("%-32s\n\n", dataStruct3[0].length1 == SQL_NULL_DATA ? (UCHAR *)"NULL"
            //                                                             : dataStruct3[0].charCol1);
            char *ds3Msg = "NULL";
            if (dataStruct3[0].length1 != SQL_NULL_DATA)
            {
                ds3Msg = dataStruct3[0].charCol1;
            }
            printf("%-32s\n\n", ds3Msg);
        }

        printf("indicator(d): %d\n", dataStruct[0].length1);
        printf("indicator(lld): %lld\n", dataStruct[0].length1);
        // Adds missing formatter
        // printf("indicator(hex): ");
        printf("indicator(hex): %lx\n", dataStruct[0].length1);

        /* assign to char so we can dump out each byte */
        ptr = (char *)&dataStruct[0].length1;

        for (int i = 0; i < 8; i++)
        {
            printf("%x", ptr[i]);
        }

        printf("\n");

        // printf("%-32s\n\n", dataStruct[0].length1 == SQL_NULL_DATA ? (UCHAR *)"NULL" : dataStruct[0].charCol1);
        char * ds1Msg = "NULL";
        if (dataStruct[0].length1 != SQL_NULL_DATA)
        {
            ds1Msg = dataStruct[0].charCol1;
        }
        printf("%-32s\n\n", ds1Msg);

        // Reset lengths
        dataStruct[0].length1 = -1;
        dataStruct2[0].length1 = -1;
        dataStruct3[0].length1 = -1;
        count++;
    }

    if (rc == SQL_NO_DATA_FOUND)
    {
        printf("SQLFetch returns: SQL_NO_DATA_FOUND\n");
        // goto not really needed
        // close environment and exit here
        goto end;
    }

    if ((rc != SQL_SUCCESS) && (rc != SQL_SUCCESS_WITH_INFO))
    {
        printf("SQLFetch has Failed. RC=%d\n", rc);
        ODBC_error(henv, hdbc, hstmt);
        // goto not really needed
        // close environment and exit here
        goto end;
    }

/*
** Free Bind Buffers
*/
end:
    // This should be in EnvClose()
    // Also, nothing is done with rc.
    rc = SQLFreeStmt(hstmt, SQL_UNBIND);
    EnvClose(henv, hdbc);

    return 0;
}