//
//  testPostgreSqlAPI.h
//  pg02_with_libpq
//
//  Created by Tim on 2016/6/26.
//  Copyright © 2016年 Tim. All rights reserved.
//  Build Settings >> Enable Bitcode >> YES to no
//  http://www.yolinux.com/TUTORIALS/PostgreSQL-Programming-C-API.html
//  https://www.postgresql.org/docs/9.1/static/libpq-example.html

#ifndef testPostgreSqlAPI_h
#define testPostgreSqlAPI_h

#include <stdio.h>

#endif /* testPostgreSqlAPI_h */



#include <stdio.h>
#include <stdlib.h>
#include <libpq/libpq-fe.h>
#include <string.h> // correct header
#include <strings.h> // incorrect header - change this in your code to string.h


static void
exit_nicely(PGconn *conn, PGresult   *res)
{
    PQclear(res);
    PQfinish(conn);
    exit(1);
}

// Assembly text tested

char
create_script(char *userid,char *time,char *userloc,char *keyword,char *selectresult,char *selectloc)
{
    char AssemblySqlScript[200] = "INSERT INTO mispell2 (userid,time,userloc,keyword,selectresult,selectloc) VALUES ('";

    strcat(AssemblySqlScript, userid);
    strcat(AssemblySqlScript,"', '");
    strcat(AssemblySqlScript,time);
    strcat(AssemblySqlScript,"', '");
    strcat(AssemblySqlScript,userloc);
    strcat(AssemblySqlScript,"', '");
    strcat(AssemblySqlScript,keyword);
    strcat(AssemblySqlScript,"', '");
    strcat(AssemblySqlScript,selectresult);
    strcat(AssemblySqlScript,"', '");
    strcat(AssemblySqlScript,selectloc);
    strcat(AssemblySqlScript,"')");
    
    fprintf(stderr, "SQL Script : %s", AssemblySqlScript);

    return AssemblySqlScript;
}

// connect to the server and insert data
int
mainConn(char *userid,char *time,char *userloc,char *keyword,char *selectresult,char *selectloc)
{
    

    
    const char *conninfo = "hostaddr=Server_IP_or_Addr  port=Server_Port user=User_NM password=Postgres_Password dbname=DB_NM sslmode=disable";
    PGconn     *conn;
    PGresult   *res;
    int         nFields;
    int         i,
    j;
    
    // check data
    fprintf(stderr, "Getting id : %s", userid);
    printf("\n\n");
    fprintf(stderr, "Getting id : %s", time);
    printf("\n\n");
    fprintf(stderr, "Getting id : %s", userloc);
    printf("\n\n");
    fprintf(stderr, "Getting id : %s", keyword);
    printf("\n\n");
    fprintf(stderr, "Getting id : %s", selectresult);
    printf("\n\n");
    fprintf(stderr, "Getting id : %s", selectloc);
    printf("\n\n");
    
    // Make a connection to the database
    conn = PQconnectdb(conninfo);
    
    // Check to see that the backend connection was successfully made
    if (PQstatus(conn) != CONNECTION_OK)
    {
        fprintf(stderr, "Connection to database failed: %s", PQerrorMessage(conn));
        printf("\n\n");
        PQfinish(conn);
        exit(1);
    }
    else
    {
         fprintf(stderr, "Connection to database OK");
         printf("\n\n");
        
    }
   
    // Assembly text into sql script.
    char AssemblySqlScript[200] = "INSERT INTO mispell2 (userid,time,userloc,keyword,selectresult,selectloc) VALUES ('";
    
    strcat(AssemblySqlScript, userid);
    strcat(AssemblySqlScript,"', '");
    strcat(AssemblySqlScript,time);
    strcat(AssemblySqlScript,"', '");
    strcat(AssemblySqlScript,userloc);
    strcat(AssemblySqlScript,"', '");
    strcat(AssemblySqlScript,keyword);
    strcat(AssemblySqlScript,"', '");
    strcat(AssemblySqlScript,selectresult);
    strcat(AssemblySqlScript,"', '");
    strcat(AssemblySqlScript,selectloc);
    strcat(AssemblySqlScript,"')");
    
    // print out check again.
    fprintf(stderr, "SQL Script : %s", AssemblySqlScript);
    
    // exec Sql Script
    res = PQexec(conn, AssemblySqlScript);
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "INSERT failed: %s", PQerrorMessage(conn));
        printf("\n\n");
        exit_nicely(conn,res);
    }
    PQclear(res);
    
    
    // Use cursor inside a transaction block
    
    // Start a transaction block
    res = PQexec(conn, "BEGIN");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "BEGIN command failed: %s", PQerrorMessage(conn));
        printf("\n\n");
        exit_nicely(conn,res);
    }
    PQclear(res);  // Clear memory
    
    res = PQexec(conn, "DECLARE mydata CURSOR FOR SELECT * from mispell2 ");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        
        fprintf(stderr, "_DECLARE CURSOR failed: %s", PQerrorMessage(conn));
        printf("\n\n");
//        PQclear(res);
        exit_nicely(conn,res);

    }
    else
    {
     fprintf(stderr, "_DECLARE CURSOR OK:");
        printf("\n\n");
    
    }
    PQclear(res);

    res = PQexec(conn, "FETCH ALL in mydata");
    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        fprintf(stderr, "FETCH ALL failed: %s", PQerrorMessage(conn));
        exit_nicely(conn,res);
    }
    
    // first, print out the table collumn attribute names
    nFields = PQnfields(res);
    for (i = 0; i < nFields; i++)
        printf("%-15s", PQfname(res, i));
    printf("\n\n");
    
    // next, print out the rows of data
    for (i = 0; i < PQntuples(res); i++)
    {
        for (j = 0; j < nFields; j++)
            printf("%-15s", PQgetvalue(res, i, j));
        printf("\n");
    }
    
    PQclear(res);
    
    // close the portal ... we don't bother to check for errors ...
    res = PQexec(conn, "CLOSE mydata");
    PQclear(res);
    
    // End the transaction
    res = PQexec(conn, "END");
    PQclear(res);
    
    // close the connection to the database and cleanup
    PQfinish(conn);
    
    return 0;
}