#include <stdlib.h>
#include <stdio.h>
#include <mysql.h>

static char *host = "localhost";
static char *user = "root";
static char *password="";
static char *db_name ="esb_db";

unsigned int port = 3306;
static char *unix_socket = NULL;
unsigned int flag = 0;

int main () {
    MYSQL *con;

    con = mysql_init(NULL);

    if(!(mysql_real_connect(con,host,user, password,db_name, port, unix_socket, flag))){
         fprintf(stderr,"\nError: %s [%d] \n",mysql_error(con),mysql_errno(con));
         exit(1);
    }
    printf("Connection Successful\n\n");

    return EXIT_SUCCESS;
}