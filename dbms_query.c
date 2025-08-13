#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>

#include "dbms_query.h"

char* DBMS1_substr(char *query);
char* DBMS2_substring(char *query);
char* DBMS3_sbstr(char *query);

char* dbms_get_substring(char *query, enum DBMS_TYPE dbms)
{
    char *r_str;
    char *dbms_query;

    switch (dbms)
    {
    case DBMS1:
        dbms_query = DBMS1_substr(query);
        break;

    case DBMS2:
        dbms_query = DBMS2_substring(query);
        break;

    case DBMS3:
        dbms_query = DBMS3_sbstr(query);
        break;

    default:
        dbms_query = "NULL";
        break;
    }

    return dbms_query;
}
