#include "lib_mySql.h"


MYSQL connexion(char server[100],char name[100],char password[100])
{
 MYSQL mysql;

    mysql_init(&mysql);
    mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "your_prog_name");
    if (!mysql_real_connect(&mysql, server, name,password, "GEL", 0, NULL, 0))
    {
        fprintf(stderr, "Failed to connect to database: Error: %s\n",
                mysql_error(&mysql));
    }

    MYSQL *con;
    con = mysql_init(NULL);

    if (mysql_real_connect(con, server, name,password, "GEL", 3306, NULL, 0) == NULL)
    {
       printf("The authentication failed with the following message:\n");
        printf("%s\n", mysql_error(con));
    }
return *con;
}

int deconnexion(MYSQL *con)
{
 mysql_close(con);
 return 1;
}

int requete(MYSQL *con,char name[100],char password[100],char requete[100])
{
     char sql_statement[2048];
    // Construct the SQL statement
     sprintf(sql_statement,requete, name, password);
     if (mysql_query(con, sql_statement) != 0)
     {
        printf("Query failed  with the following message:\n");
        printf("%s\n", mysql_error(con));
        return 0;
    }
return 1;
}
