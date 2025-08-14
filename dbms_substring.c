#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dbms_substring.h"

#define MAX_QUERY_SIZE 1024

// Example for SQL Server
static void DBMS_substring(char *query, char *str, int start, int length)
{
    snprintf(query, MAX_QUERY_SIZE, "SUBSTRING(%s, %d, %d)", str, start, length);
};

// Example for MYSQL
static void DBMS2_substr(char *query, char *str, int start, int length) {
    if (length == NULL) {
        snprintf(query, MAX_QUERY_SIZE, "SUBSTRING(%s, %d)", str, start);
    } else {
        snprintf(query, MAX_QUERY_SIZE, "SUBSTRING(%s, %d, %d)", str, start, length);
    }
}

// Example for Postgres
static void DBMS3_sbstr(char *query, char *str, int start, int length) {
    if (length == NULL) {
        snprintf(query, MAX_QUERY_SIZE, "SUBSTRING(%s FROM %d)", str, start);
    } else {
        snprintf(query, MAX_QUERY_SIZE, "SUBSTRING(%s FROM %d FOR %d)", str, start, length);
    }
};

void dbms_format_substring_query(char *query, char *str, int start, int length, enum DBMS_TYPE dbms)
{
    char *r_str;
    char *dbms_query;
    char substring_query[MAX_QUERY_SIZE] = {0};

    switch (dbms)
    {
    case DBMS1:
        DBMS1_substr(substring_query, str, start, length);
        break;

    case DBMS2:
        DBMS2_substring(substring_query, str, start, length);
        break;

    case DBMS3:
        DBMS3_sbstr(substring_query, str, start, length);
        break;

    default:
        break;
    }

    snprintf(query, MAX_QUERY_SIZE, "%s", substring_query);
}
