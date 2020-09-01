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

void select_all_routes(char **sender, char **message_type) {      

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

   strcpy(sql_str,"SELECT * FROM routes WHERE sender = ? AND message_type = ? ");

   if(mysql_stmt_prepare(statement,sql_str,strlen(sql_str))) {
       fprintf(stderr,"\nError[%d]: %s  \n",
       mysql_stmt_errno(statement),mysql_stmt_error(statement));
       exit(1); 
   }
   fprintf(stdout, " prepare, SELECT successful\n");
   int param_count;
   /* Get the parameter count from the statement */
   param_count= mysql_stmt_param_count(statement);
   
   fprintf(stdout, " total parameters in SELECT: %d\n", param_count);
   
   /* validate parameter count */
   if (param_count != 2) {
   fprintf(stderr, " invalid parameter count returned by MySQL\n");
   exit(0);
   }
    
  MYSQL_BIND input_bind[2];
  memset(input_bind,0,sizeof(input_bind));
  unsigned long sender_len ;
  unsigned long message_type_len;
  bool input_is_null[2];
  char sender_data[STRING_SIZE];
  char message_type_data[STRING_SIZE];

  input_bind[0].buffer_type = MYSQL_TYPE_STRING;
  input_bind[0].buffer = (char*)&sender_data;
  input_bind[0].buffer_length = STRING_SIZE;
  input_bind[0].length = &sender_len;
  input_bind[0].is_null = 0;

  input_bind[1].buffer_type = MYSQL_TYPE_STRING;
  input_bind[1].buffer = (char*)&message_type_data;
  input_bind[1].buffer_length = STRING_SIZE;
  input_bind[1].length = &message_type_len;
  input_bind[1].is_null = 0;

  if (mysql_stmt_bind_param(statement, input_bind)) {
        fprintf(stderr, "ERROR:mysql_stmt_bind_param failed\n");
        exit(1);
    }
  strcpy(sender_data,*sender);
  sender_len = strlen(sender_data);
  strcpy(message_type_data,*message_type);
  message_type_len = strlen(message_type_data);

  if (mysql_stmt_execute(statement)) {
        fprintf(stderr, "mysql_stmt_execute(), failed.\nError %d:%s\n",mysql_stmt_errno(statement),mysql_stmt_error(statement));
        exit(1);
    }
  
  MYSQL_BIND result_bind[5];
  MYSQL_RES *prepare_meta_result;
  unsigned long result_len[5];
  int row_count;
  int route_id_data;
  char res_sender_data[STRING_SIZE];
  char destination_data[STRING_SIZE];
  char res_message_type_data[STRING_SIZE];
  char is_active_data[STRING_SIZE];
  bool result_is_null[5];
  bool error[5];

  memset(result_bind,0,sizeof(result_bind));

  /*route_id column*/
  result_bind[0].buffer_type = MYSQL_TYPE_LONG;
  result_bind[0].buffer = (char *)&route_id_data;
  result_bind[0].is_null = &result_is_null[0];
  result_bind[0].length = &result_len[0];
  result_bind[0].error = &error[0];

  /*sender column*/
  result_bind[1].buffer_type = MYSQL_TYPE_STRING;
  result_bind[1].buffer = (char *)&res_sender_data;
  result_bind[1].is_null = &result_is_null[1];
  result_bind[1].length = &result_len[1];
  result_bind[1].error = &error[1];

  /*destination column*/
  result_bind[2].buffer_type = MYSQL_TYPE_STRING;
  result_bind[2].buffer = (char *)&destination_data;
  result_bind[2].is_null = &result_is_null[2];
  result_bind[2].length = &result_len[2];
  result_bind[2].error = &error[2];
  
  /*message_type column*/
  result_bind[3].buffer_type = MYSQL_TYPE_VAR_STRING;
  result_bind[3].buffer = (char *)&res_message_type_data;
  result_bind[3].is_null = &result_is_null[3];
  result_bind[3].length = &result_len[3];
  result_bind[3].error = &error[3];

  /*is_active column*/
  result_bind[4].buffer_type = MYSQL_TYPE_BIT;
  result_bind[4].buffer = (char *)&is_active_data;
  result_bind[4].is_null = &result_is_null[4];
  result_bind[4].length = &result_len[4];
  result_bind[4].error = &error[4];
  
  if(mysql_stmt_bind_result(statement,result_bind)) {
      fprintf(stderr, " mysql_stmt_bind_result(), failed\n");
      fprintf(stderr, "Error[%d] %s\n",
      mysql_stmt_errno(statement),mysql_stmt_error(statement));
      exit(1);
   }   
   
   /* Now buffer all results to client (optional step) */
if (mysql_stmt_store_result(statement))
{
  fprintf(stderr, " mysql_stmt_store_result() failed\n");
  fprintf(stderr, " %s\n", mysql_stmt_error(statement));
  exit(0);
}
row_count = 0;

fprintf(stdout,"Fetching results...\n");

while(!mysql_stmt_fetch(statement)) {
  row_count++;
  fprintf(stdout, "  row %d\n", row_count);

    /* column 1 */
  fprintf(stdout, "   column1 (integer)  : ");
  if (result_is_null[0])
    fprintf(stdout, " NULL\n");
  else
    fprintf(stdout, " %d\n", route_id_data);

  /* column 2 */
  fprintf(stdout, "   column2 (string)   : ");
  if (result_is_null[1])
    fprintf(stdout, " NULL\n");
  else
    fprintf(stdout, " %s\n", res_sender_data);
  /*column 3 */
  fprintf(stdout, "   column2 (string)   : ");
  if (result_is_null[2])
    fprintf(stdout, " NULL\n");
  else
    fprintf(stdout, " %s\n", destination_data);
  /*column 4*/
  fprintf(stdout, "   column2 (string)   : ");
  if (result_is_null[3])
    fprintf(stdout, " NULL\n");
  else
    fprintf(stdout, " %s\n", res_message_type_data);
  /*column 5*/
  printf("   column2 (string)   : ");
  if (result_is_null[4])
    fprintf(stdout, " NULL\n");
  else
    fprintf(stdout, " %s\n", is_active_data);
  
  }
  if (mysql_stmt_close(statement)){
  /* mysql_stmt_close() invalidates stmt, so call          */
  /* mysql_error(mysql) rather than mysql_stmt_error(stmt) */
  fprintf(stderr, " failed while closing the statement\n");
  fprintf(stderr, " %s\n", mysql_error(con));
  exit(0);
  }
   /*frees the result*/
  mysql_free_result(prepare_meta_result);
  /*closes the database connection*/
  mysql_close(con);
  
  exit(0);
}

int main () {
    char *sender="A";
    char *message_type="xml";
    select_all_routes(&sender,&message_type);
    return 0;
}