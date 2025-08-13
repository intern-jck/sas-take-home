#ifndef DBMS_QUERY_H
#define DBMS_QUERY_H

enum DBMS_TYPE
{
    DBMS1,
    DBMS2,
    DBMS3,
};

char* dbms_query(char *query, enum DBMS_TYPE dbms);

#endif
