/**
 * @file select_all_routes.c
 * @author MubeenS 
 * @brief  The program is a C API for the SQL query 
 * SELECT * FROM routes WHERE sender=? AND message_type=? and is_active=1;
 * @version 0.1
 * @date 2020-08-29
 * 
 * @copyright Copyright (c) 2020
 * 
 */

/*Required C standard libraries*/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
/* Contains necessary C functions of mysql */
#include <mysql.h>

/**
 * Holds the info to connect to DB and
 * error specifying function for 
 * databse connection handle 
 */
#include "connector.h"

#define INSERT_SAMPLE "INSERT INTO                            \
routes(route_id,sender,destination,message_type,is_active)    \
VALUES(?,?,?,?,1)"




void insert_to_routes(char **sender,
char **destination,char **message_type,char **is_active) {
MYSQL_STMT    *stmt;
MYSQL_BIND    bind[4];
my_ulonglong  affected_rows;
int           param_count;
int           id; 
char          sender_data[STRING_SIZE];
char          destination_data[STRING_SIZE];
char          message_type_data[STRING_SIZE];
unsigned long str_length[3];
bool          is_null;

  MYSQL *con ;  /*database connection handle*/
  /**
   * @brief Allocates or initialises a MYSQL object 
   * suitable for mysql_real_connect() function
   * 
   */
  con = mysql_init(NULL);

  /**
   * @brief Prints error message incase
   * initialisation of con fails.
   */
  if (con == NULL) {

      fprintf(stderr, "mysql_init() failed\n");
      exit(1);
  }  
  
  /**
   * @brief Checks if connection is 
   * properly established.
   * 
   */
  if (mysql_real_connect(con, g_host, g_user, g_password,       
          g_db_name, g_port, g_unix_socket, g_flag) == NULL) {
      finish_with_error(con);
  } 
/* Prepare an INSERT query with 3 parameters */
stmt = mysql_stmt_init(con);
if (!stmt) {
  fprintf(stderr, " mysql_stmt_init(), out of memory\n");
  exit(0);
}

if (mysql_stmt_prepare(stmt, INSERT_SAMPLE, strlen(INSERT_SAMPLE))) {
  fprintf(stderr, " mysql_stmt_prepare(), INSERT failed\n");
  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
  exit(0);
}
fprintf(stdout, " prepare, INSERT successful\n");

/* Get the parameter count from the statement */
param_count= mysql_stmt_param_count(stmt);
fprintf(stdout, " total parameters in INSERT: %d\n", param_count);

/* validate parameter count */
if (param_count != 4) {
  fprintf(stderr, " invalid parameter count returned by MySQL\n");
  exit(0);
}

/* Bind the data for all 3 parameters */
memset(bind, 0, sizeof(bind));

/* This is a number type, so there is no need to specify buffer_length */
/* INTEGER PARAM */
bind[0].buffer_type= MYSQL_TYPE_LONG;
bind[0].buffer= (char *)&id;
bind[0].is_null= 0;
bind[0].length= 0;

/* STRING PARAM */
bind[1].buffer_type= MYSQL_TYPE_STRING;
bind[1].buffer= (char *)&sender_data;
bind[1].is_null= 0;
bind[1].length= &str_length[0];
bind[1].buffer_length= STRING_SIZE;


/* STRING PARAM */
bind[2].buffer_type= MYSQL_TYPE_STRING;
bind[2].buffer= (char *)destination_data;
bind[2].buffer_length= STRING_SIZE;
bind[2].is_null= 0;
bind[2].length= &str_length[1];

/* STRING PARAM */
bind[3].buffer_type= MYSQL_TYPE_STRING;
bind[3].buffer= (char *)&message_type_data;
bind[3].is_null= 0;
bind[3].buffer_length= STRING_SIZE;
bind[3].length= &str_length[2];

/* Bind the buffers */
if (mysql_stmt_bind_param(stmt, bind)) {
  fprintf(stderr, " mysql_stmt_bind_param() failed\n");
  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
  exit(0);
}

if (mysql_query(con, "SELECT * FROM routes")) {
      finish_with_error(con);
}
  
MYSQL_RES *result = mysql_store_result(con);
  
if (result == NULL) {
      finish_with_error(con);
}
  
int row_id;
MYSQL_ROW row;
while ((row = mysql_fetch_row(result))) {               
         row_id = atoi(row[0]);
}

  mysql_free_result(result);
row_id+=1;
id=row_id;
strncpy(sender_data,*sender, STRING_SIZE);
strncpy(destination_data,*destination, STRING_SIZE);
str_length[0]= strlen(sender_data);
str_length[1]=strlen(destination_data);
strncpy(message_type_data,*message_type,STRING_SIZE);        /* smallint */
str_length[2]=strlen(message_type_data);
//is_null= 0;               /* reset */

/* Execute the INSERT statement - 2*/
if (mysql_stmt_execute(stmt)) {
  fprintf(stderr, " mysql_stmt_execute, 2 failed\n");
  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
  exit(0);
}

/* Get the total rows affected */
affected_rows= mysql_stmt_affected_rows(stmt);
fprintf(stdout, " total affected rows(insert 2): %lu\n",
                (unsigned long) affected_rows);

/* validate affected rows */ 
if (affected_rows != 1) {
  fprintf(stderr, " invalid affected rows by MySQL\n");
  exit(0);
}

/* Close the statement */
if (mysql_stmt_close(stmt)) {
  fprintf(stderr, " failed while closing the statement\n");
  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
  exit(0);
} printf("connection id: %ld\n", mysql_thread_id(con));

  mysql_close(con);
}

/*testing with a sample input*/
int main() {
  char *s,*d,*mt,*ia;
  s="b"; d = "u"; mt = "Credit"; ia = "1";
 insert_to_routes(&s,&d,&mt,&ia);
 return 0;
}