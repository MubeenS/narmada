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

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
/* Contains necessary C functions of mysql */
#include <mysql/mysql.h>
#define STRING_SIZE 300
/**
 * @brief Declare parameters required for 
 * mysql_real_connect() as global variables.
 * 
 */
static char *g_host = "localhost";/*hostname*/
static char *g_user = "root";     /*username*/
static char *g_password=""; /*blank password this user*/
static char *g_db_name ="esb_db";/*name of the database*/

unsigned int g_port = 3306; /*port number*/
static char *g_unix_socket = NULL; /*unix socket*/
unsigned int g_flag = 0; /*last parameter to mysql_real_connect*/

/**
 * @brief Whenever there is an error opening a database
 * or executing a query finish_with_error prints error
 * specifying error number and error message
 * 
 * @param con database connection handle
 */
void finish_with_error(MYSQL *con) {

  fprintf(stderr, "Error [%d]: %s \n",mysql_errno(con),mysql_error(con));
  mysql_close(con);

  exit(1);        
}

void select_all_routes(char *sender, char *message_type) {      

  /**
   * @brief Allocate and initialise a MYSQL object 
   * suitable for mysql_real_connect() function
   * 
   */
  MYSQL *con = mysql_init(NULL);

  /* Print an error message incase
   * initialisation of con fails.
   */
  if (con == NULL) {

      fprintf(stderr, "mysql_init() failed\n");
      exit(1);
  }  
  
  /* Check if connection is 
   * properly established.
   */
  if (mysql_real_connect(con, g_host, g_user, g_password,       
          g_db_name, g_port, g_unix_socket, g_flag) == NULL) {
      finish_with_error(con);
  }    
  
  MYSQL_STMT *statement = NULL;
  statement = mysql_stmt_init(con);
   
  if(statement == NULL) {
     finish_with_error(con);
   }
   char sql_str[STRING_SIZE];

   strcpy(sql_str,"SELECT * FROM routes WHERE sender = ? AND message_type = ? AND is_active = 1");

   if(mysql_stmt_prepare(statement,sql_str,strlen(sql_str))) {
           finish_with_error(con);
   }
    
  MYSQL_BIND input_bind[1];
  memset(input_bind,0,sizeof(input_bind));
  unsigned long sender_len = sizeof(sender);
  unsigned long message_type_len = sizeof(message_type);

  /*Bind parameters to the statement*/
  input_bind[0].buffer_type = MYSQL_TYPE_STRING;
  input_bind[0].buffer = &sender;
  input_bind[0].buffer_length = sizeof(sender);
  input_bind[0].length = &sender_len;
  input_bind[0].is_null = (bool*)0;

  input_bind[1].buffer_type = MYSQL_TYPE_STRING;
  input_bind[1].buffer = &message_type;
  input_bind[1].buffer_length = sizeof(message_type);
  input_bind[1].length = &message_type_len;
  input_bind[1].is_null = (bool*)0;

  if (mysql_stmt_bind_param(statement, input_bind)) {
        fprintf(stderr, "ERROR:mysql_stmt_bind_param failed\n");
        exit(1);
    }

  if (mysql_stmt_execute(statement)) {
        fprintf(stderr, "mysql_stmt_execute(), failed.\nError:%s\n", mysql_stmt_error(statement));
        exit(1);
    }
  
  /* Fetch reuslt set meta information*/
  MYSQL_RES *result;
  result = mysql_stmt_result_metadata(statement);

  /* if there is no result error will be returned*/
  if (result == NULL) {
      printf("Result is NULL");
      finish_with_error(con);
  }

  /* stores number of fields in the result*/ 
  int num_fields = mysql_num_fields(result);
  /*mysql structure that holds a row*/
  MYSQL_ROW row;
  /*mysql structure that holds field values*/
  MYSQL_FIELD *field;

  /*prints all the rows from the result*/
  while ((row = mysql_fetch_row(result))) { 
      printf("Enters While");
      for(int i = 0; i < num_fields; i++) { 
          printf("Enters For");
          if(i==0) {
              while(field = mysql_fetch_field(result)) {
                  printf(" %s |", field->name);
              } 
              printf("\n");
            }

          printf(" %s |", row[i] ? row[i] : "NULL"); 
      } 
          printf("\n"); 
  }
  
  /*frees the result*/
  mysql_free_result(result);
  /*closes the database connection*/
  mysql_close(con);
  
  exit(0);
}

int main () {
    char sender[4],message_type[4];
    printf("Enter sender:");
    scanf("%s",sender);
    printf("Enter message_type:");
    scanf("%s",message_type);

    select_all_routes(sender,message_type);
    return 0;
}