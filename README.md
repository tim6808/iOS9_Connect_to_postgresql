# iOS9_Connect_to_postgresql
How to connect to postgresql from iOS9. http://goo.gl/nXzeGy

#What in there?

"libpq.framework"
"testPostgreSqlAPI.c"
"testPostgreSqlAPI.h"
"pg02_with_libpq-Bridging-Header.h"
"ViewController.swift" 

"libpq.framework" is the framework which download from the https://www.postgresql.org/

"pg02_with_libpq-Bridging-Header.h" Bridging-Header file is the a bridge for access your Objective-C code from Swift and your Swift code from Objective-C.(pg02_with_libpq usually is the project NM.) Usually this file will automatically generated when you create a Objective-C file.

"testPostgreSqlAPI.c", "testPostgreSqlAPI.h" This two is the key point to connect to "libpq.framework", and why use C? That is because "libpq.framework" is C.

"ViewController.swift" Your ViewController file.

#How to do it?
1.Go find a libpq.framework.
2.You have to create a C type file(because libpq is not Obj-c.) as C API to connect libpq.
3.After that create a Bridging-Header to connect it.(It Bridging will not generate its own)
4.Back to the C type file you created.
5.Follow this "PostgreSQL C Language API" tutorial this tutorial saved me a lot of time .(C has been a very far away from me.)
6.If need, go to Build Settings >> Enable Bitcode >> YES
7.Make sure test it on the device.

#What's in there?
#"ViewController" 
In "ViewController" there is a function call "mainConn" it main function is send data to C API function "mainConn" which in the "testPostgreSqlAPI_h".

#"testPostgreSqlAPI_h"
The "testPostgreSqlAPI_h" file is base on this http://goo.gl/u2XRQj and https://goo.gl/hQiwnb tutorial.


In "testPostgreSqlAPI_h" to connect to the PGSQL you will need to use:


    // Make a connection to the database
    conn = PQconnectdb(conninfo);
And "conninfo" is the connect information like Server IP or Addr, Port, UserNM, DBNM...


After connecttion you can start sending sql script by using:


    // exec Sql Script
    res = PQexec(conn, AssemblySqlScript);
In there "AssemblySqlScript" is your SQL script.


About the rest of it you can check this tutorial http://goo.gl/u2XRQj


