/**
 * @file insert_to_esb_request.c
 * @author MubeenS 
 * @brief  The program is a C API for the SQL query 
 * "INSERT INTO                            
 * esb_requestsender_id,dest_id,message_type,reference_id,      
 * message_id,data_location,status,status_details)               
 * VALUES(?,?,?,?,?,?,?,?)"
 * @version 0.1
 * @date 2020-09-1
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
#define STRING_SIZE 1000

#define INSERT "INSERT INTO                                  \
esb_request(sender_id,dest_id,message_type,reference_id,     \
message_id,data_location,status,status_details)              \
VALUES(?,?,?,?,?,?,?,?)"

void insert_to_esb_request(char *sender_id,char *dest_id,
char *message_type,char *reference_id,char *message_id, 
char *data_location, char *status,char *status_details) {

MYSQL_STMT    *stmt;
MYSQL_BIND    bind[8];
my_ulonglong  affected_rows;
int           param_count;
int           id; 
char          sender_id_data[STRING_SIZE];
char          dest_id_data[STRING_SIZE];
char          message_type_data[STRING_SIZE];
char          reference_id_data[STRING_SIZE];
char          message_id_data[STRING_SIZE];
char          data_location_data[STRING_SIZE];
char          status_data[STRING_SIZE];
char          status_details_data[STRING_SIZE];
unsigned long str_length[8];
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

if (mysql_stmt_prepare(stmt, INSERT, strlen(INSERT))) {
  fprintf(stderr, " mysql_stmt_prepare(), INSERT failed\n");
  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
  exit(0);
}
fprintf(stdout, " prepare, INSERT successful\n");

/* Get the parameter count from the statement */
param_count= mysql_stmt_param_count(stmt);
fprintf(stdout, " total parameters in INSERT: %d\n", param_count);

/* validate parameter count */
if (param_count != 8) {
  fprintf(stderr, " invalid parameter count returned by MySQL\n");
  exit(0);
}

/* Bind the data for all 8 parameters */
memset(bind, 0, sizeof(bind));

/* Sender id */
bind[0].buffer_type= MYSQL_TYPE_STRING;
bind[0].buffer= (char *)&sender_id_data;
bind[0].is_null= 0;
bind[0].length= &str_length[0];
bind[0].buffer_length= STRING_SIZE;


/* dest_id */
bind[1].buffer_type= MYSQL_TYPE_STRING;
bind[1].buffer= (char *)dest_id_data;
bind[1].buffer_length= STRING_SIZE;
bind[1].is_null= 0;
bind[1].length= &str_length[1];

/* message_type */
bind[2].buffer_type= MYSQL_TYPE_STRING;
bind[2].buffer= (char *)&message_type_data;
bind[2].is_null= 0;
bind[2].buffer_length= STRING_SIZE;
bind[2].length= &str_length[2];

/* reference_id */
bind[3].buffer_type= MYSQL_TYPE_STRING;
bind[3].buffer= (char *)&reference_id_data;
bind[3].is_null= 0;
bind[3].buffer_length= STRING_SIZE;
bind[3].length= &str_length[3];

/* message_id  */
bind[4].buffer_type= MYSQL_TYPE_STRING;
bind[4].buffer= (char *)&message_id_data;
bind[4].is_null= 0;
bind[4].buffer_length= STRING_SIZE;
bind[4].length= &str_length[4];

/* data_location */
bind[5].buffer_type= MYSQL_TYPE_STRING;
bind[5].buffer= (char *)&data_location_data;
bind[5].is_null= 0;
bind[5].buffer_length= STRING_SIZE;
bind[5].length= &str_length[5];

/* status */
bind[6].buffer_type= MYSQL_TYPE_STRING;
bind[6].buffer= (char *)&status_data;
bind[6].is_null= 0;
bind[6].buffer_length= STRING_SIZE;
bind[6].length= &str_length[6];

/* status details */
bind[7].buffer_type= MYSQL_TYPE_STRING;
bind[7].buffer= (char *)&status_details_data;
bind[7].is_null= 0;
bind[7].buffer_length= STRING_SIZE;
bind[7].length= &str_length[7];


/* Bind the buffers */
if (mysql_stmt_bind_param(stmt, bind)) {
  fprintf(stderr, " mysql_stmt_bind_param() failed\n");
  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
  exit(0);
}
strncpy(sender_id_data,sender_id, STRING_SIZE);
str_length[0]= strlen(sender_id_data);
strncpy(dest_id_data,dest_id, STRING_SIZE);
str_length[1]=strlen(dest_id_data);
strncpy(message_type_data,message_type,STRING_SIZE);        
str_length[2]=strlen(message_type_data);
strncpy(reference_id_data,reference_id,STRING_SIZE);        
str_length[3]=strlen(reference_id_data);
strncpy(message_id_data,message_id,STRING_SIZE);        
str_length[4]=strlen(message_id_data);
strncpy(data_location_data,data_location,STRING_SIZE);        
str_length[5]=strlen(data_location_data);
strncpy(status_data,status,STRING_SIZE);        
str_length[6]=strlen(status_data);
strncpy(status_details_data,status_details,STRING_SIZE);        
str_length[7]=strlen(status_details_data);

/* Execute the INSERT statement*/
if (mysql_stmt_execute(stmt)) {
  fprintf(stderr, " mysql_stmt_execute, failed\n");
  fprintf(stderr, " [%d]%s\n",mysql_stmt_errno(stmt),
  mysql_stmt_error(stmt));
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
  char *s,*d,*mt,*rid,*mid,*dl,*st,*std;
  s="sender2"; d = "dest2"; mt = "CreditReport"; mid = "2";
  dl = "dat_loc"; st ="Active"; std="process";
  rid = "ref_id1";
 insert_to_esb_request(s,d,mt,rid,mid,dl,st,std);
 return 0;
}