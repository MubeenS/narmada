/**
 * @brief Parameters required for 
 * mysql_real_connect() function are declared as
 * global variables.
 * 
 */
#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <stdio.h>
#include <mysql.h>

#include "../bmd_assets/bmd.h"

#include "../esb/esb.h"


#define HOST "localhost"   /*hostname*/
#define USER  "root"       /*username*/
#define PASS    ""         /*blank password this user*/
#define DB_NAME "esb_db"   /*name of the database*/
#define PORT  3306         /*port number*/
#define UNIX_SOCKET NULL   /*unix socket*/
#define FLAG 0             /*last parameter to mysql_real_connect*/

int insert_to_esb_request(char *sender_id,char *dest_id,
char *message_type,char *reference_id,char *message_id, 
char *data_location, char *status,char *status_details,char *received_on);

int select_active_routes(char *sender, char * ,char *);
void finish_with_error(MYSQL *con) ;
int get_active_route_id(char *sender,char* destination,char *message_type);
int has_transform_config(int route_id);
int has_transport_config(int route_id);
task_t *select_new_esb_request(void);

#endif

