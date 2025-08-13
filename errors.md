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

