/**
 * @brief Parameters required for 
 * mysql_real_connect() function are declared as
 * global variables.
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
 