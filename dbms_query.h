#ifndef DBMS_QUERY_H
#define DBMS_QUERY_H

enum DBMS_TYPE
{
    DBMS1,
    DBMS2,
    DBMS3,
};


/*
** function: dbms_format_substring_query
**
** Purpose: Formats substring query based on DBMS type
**
** Arguments: 
** query - query to create
** str - string to pass to substring query
** start - starting index
** length - number of characters to search, starting from start
** dbms - DBMS type
**
*/
void dbms_format_substring_query(char *query, char *str, int start, int length, enum DBMS_TYPE dbms);

#endif
