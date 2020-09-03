/**
 * @brief Parameters required for 
 * mysql_real_connect() function are declared as
 * global variables.
 * 
 */
#include <stdio.h>
#ifndef CONNECTOR_H
#define CONNECTOR_H
int insert_to_esb_request(char *sender_id,char *dest_id,
char *message_type,char *reference_id,char *message_id, 
char *data_location, char *status,char *status_details);

static char *g_host = "localhost";/*hostname*/
static char *g_user = "root";     /*username*/
static char *g_password=""; /*blank password this user*/
static char *g_db_name ="esb_db";/*name of the database*/
#define g_port  3306 /*port number*/
static char *g_unix_socket = NULL; /*unix socket*/
#define g_flag 0 /*last parameter to mysql_real_connect*/
#endif
/**
 * @brief Whenever there is an error opening a database
 * or executing a query finish_with_error prints error
 * specifying error number and error message
 * 
 * @param con database connection handle
 */
