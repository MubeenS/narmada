#include <stdio.h>
#include <string.h>
#include <stdio.h>


#include <mysql.h>

#include "connector.h"

int connect_to_db(void) {
    
    MYSQL *con; 
    con = mysql_init(NULL);

    /**
   * @brief Prints error message incase
   * initialisation of con fails.
   */
    if (con == NULL) {

        fprintf(stderr, "mysql_init() failed\n");
        return -1;
    }

    /**
   * @brief Checks if connection is 
   * properly established.
   * 
   */
    if (mysql_real_connect(con, HOST, USER, PASS,DB_NAME, 
                            PORT, UNIX_SOCKET, FLAG) == NULL) {
    }
    return 1;
}

int finish_with_error(MYSQL *con) {

  fprintf(stderr, "Error [%d]: %s \n",mysql_errno(con),mysql_error(con));
  mysql_close(con);
  return -1;
}
