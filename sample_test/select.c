#include <stdio.h>
#include <mysql/mysql.h>
#include <string.h>
#include <stdbool.h>

#define STRING_SIZE 50

void select_all (char **sender) {
    MYSQL *con;
    con = mysql_init(NULL);

    if(!(mysql_real_connect(con,"localhost","root", "","test", 3306, NULL, 0))){
         fprintf(stderr,"\nError: %s [%d] \n",mysql_error(con),mysql_errno(con));
         exit(1);
    }
    printf("Connection Successful\n");
  
  MYSQL_STMT *statement = NULL;
  statement = mysql_stmt_init(con);

  if(statement == NULL) {
     printf("statement failed");
     exit(0);
   }
   char sql_str[STRING_SIZE];

   strcpy(sql_str,"SELECT * FROM send WHERE sender = ?");

   if(mysql_stmt_prepare(statement,sql_str,strlen(sql_str))) {
       fprintf(stderr,"\nError[%d]: %s  \n",
       mysql_stmt_errno(statement),mysql_stmt_error(statement));
       exit(1); 
    }
  int param_count = mysql_stmt_param_count(statement);
  if (param_count != 1) /* validate parameter count */
{
  fprintf(stderr, " invalid parameter count returned by MySQL\n");
  exit(0);
}
  MYSQL_BIND input_bind[1];
  memset(input_bind,0,sizeof(input_bind));
  unsigned long str_len ;
  bool input_is_null[1];
  char str_data[STRING_SIZE];

  input_bind[0].buffer_type = MYSQL_TYPE_STRING;
  input_bind[0].buffer = (char *)&str_data;
  input_bind[0].buffer_length = STRING_SIZE;
  input_bind[0].length = &str_len;
  input_bind[0].is_null = 0 ;

    if (mysql_stmt_bind_param(statement, input_bind)) {
        fprintf(stderr, "ERROR:mysql_stmt_bind_param failed\n");
        exit(1);
    }
  strcpy(str_data,*sender);
  str_len = strlen(str_data);
    if (mysql_stmt_execute(statement)) {
        fprintf(stderr, "mysql_stmt_execute(), failed.\nError %d:%s\n",mysql_stmt_errno(statement),mysql_stmt_error(statement));
        exit(1);
    }

  MYSQL_BIND res_bind[2];
  MYSQL_RES *prepare_meta_result;
  unsigned long length[2];
  int row_count;
  char res_str_data[STRING_SIZE];
  int res_int_data;
  bool res_is_null[2];
  bool error[2];
  res_bind[0].buffer_type = MYSQL_TYPE_LONG;
  res_bind[0].buffer = (char *)&res_int_data;
  res_bind[0].is_null = &res_is_null[0];
  res_bind[0].length = &length[0];
  res_bind[0].error = &error[0];

  res_bind[1].buffer_type = MYSQL_TYPE_STRING;
  res_bind[1].buffer = (char *)&res_str_data;
  res_bind[1].is_null = &res_is_null[1];
  res_bind[1].length = &length[1];
  res_bind[1].error = &error[1];


/* Bind the result buffers */
if (mysql_stmt_bind_result(statement,res_bind))
{
  fprintf(stderr, " mysql_stmt_bind_result() failed\n");
  fprintf(stderr, " %s\n", mysql_stmt_error(statement));
  exit(0);
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
  if (res_is_null[0])
    fprintf(stdout, " NULL\n");
  else
    fprintf(stdout, " %d(%ld)\n", res_int_data, length[0]);

  /* column 2 */
  fprintf(stdout, "   column2 (string)   : ");
  if (res_is_null[1])
    fprintf(stdout, " NULL\n");
  else
    fprintf(stdout, " %s(%ld)\n", res_str_data, length[1]);
}
  if (mysql_stmt_close(statement))
{
  /* mysql_stmt_close() invalidates stmt, so call          */
  /* mysql_error(mysql) rather than mysql_stmt_error(stmt) */
  fprintf(stderr, " failed while closing the statement\n");
  fprintf(stderr, " %s\n", mysql_error(con));
  exit(0);
}
  mysql_free_result(prepare_meta_result);
  mysql_close(con);
  
  }

int main () {
  char *s;
  printf("Enter sender:");
  
  scanf("%s",s);
  select_all(&s);
  return 0;
}