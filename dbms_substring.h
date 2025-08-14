#ifndef DBMS_SUBSTRING_H
#define DBMS_SUBSTRING_H

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
** query - query to create, use a char array created in calling function
** str - string to pass to substring query
** start - starting index
** length - number of characters to search, starting from start
** dbms - DBMS type
**
*/
void dbms_format_substring_query(char *query, char *str, int start, int length, enum DBMS_TYPE dbms);

#endif
