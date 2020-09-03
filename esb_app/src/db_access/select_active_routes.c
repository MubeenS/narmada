#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdio.h>

/* Contains necessary C functions of mysql */
#include <mysql.h>
/**
 * Holds the info to connect to DB and
 * error specifying function for 
 * databse connection handle 
 */
#include "connector.h"

#define STRING_SIZE 100
#define SELECT_QUERY "SELECT sender,destination,message_type FROM routes WHERE sender = ? AND message_type = ? and is_active=1"

void finish_with_error(MYSQL *con) {

  fprintf(stderr, "Error [%d]: %s \n",mysql_errno(con),mysql_error(con));
  mysql_close(con);

  exit(1);        
}
 
 
void select_active_routes(char *sender, char *message_type)
{
    printf("%s\t%s\n", sender, message_type);

    MYSQL_STMT *stmt;
    MYSQL_BIND input_bind[2];
    char input_data[2][STRING_SIZE];
    unsigned long input_length[2];
    MYSQL_BIND bind[3];
    my_ulonglong affected_rows;
    MYSQL_RES *prepare_meta_result;
    MYSQL_TIME ts;
    unsigned long length[4];
    int param_count, column_count, row_count;
    char small_data[STRING_SIZE];
    int int_data;
    char str_data[2][STRING_SIZE];
    bool is_null[3];

    MYSQL *con; /*database connection handle*/
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
                           g_db_name, g_port, g_unix_socket, g_flag) == NULL)
    {
        finish_with_error(con);
    }

    stmt = mysql_stmt_init(con);
    if (!stmt)
    {
        fprintf(stderr, " mysql_stmt_init(), out of memory\n");
        exit(0);
    }
    if (mysql_stmt_prepare(stmt, SELECT_QUERY, strlen(SELECT_QUERY)))
    {
        fprintf(stderr, " mysql_stmt_prepare(), SELECT failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        exit(0);
    }
    fprintf(stdout, " prepare, SELECT successful\n");

    /* Get the parameter count from the statement */
    param_count = mysql_stmt_param_count(stmt);
    fprintf(stdout, " total parameters in SELECT: %d\n", param_count);

    /* validate parameter count */
    if (param_count != 2)
    {
        fprintf(stderr, " invalid parameter count returned by MySQL\n");
        exit(0);
    }

    /* Fetch result set meta information */
    prepare_meta_result = mysql_stmt_result_metadata(stmt);
    if (!prepare_meta_result)
    {
        fprintf(stderr,"mysql_stmt_result_metadata(),           \
        returned no meta information\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        exit(0);
    }

    /* Get total columns in the query */
    column_count = mysql_num_fields(prepare_meta_result);
    fprintf(stdout, " total columns in SELECT statement: %d\n", column_count);

    /* validate column count */
    if (column_count != 3)
    {
        fprintf(stderr, " invalid column count returned by MySQL\n");
        exit(0);
    }

    memset(input_bind, 0, sizeof(input_bind));

    /* STRING COLUMN */
    input_bind[0].buffer_type = MYSQL_TYPE_STRING;
    input_bind[0].buffer = (char *)input_data[0];
    input_bind[0].buffer_length = STRING_SIZE;
    input_bind[0].is_null = 0;
    input_bind[0].length = &input_length[0];

    /* STRING COLUMN */
    input_bind[1].buffer_type = MYSQL_TYPE_STRING;
    input_bind[1].buffer = (char *)&input_data[1];
    input_bind[1].is_null = 0;
    input_bind[1].length = &input_length[1];
    input_bind[1].buffer_length = STRING_SIZE;

    /* Bind the buffers */
    if (mysql_stmt_bind_param(stmt, input_bind))
    {
        fprintf(stderr, " mysql_stmt_bind_param() failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        exit(0);
    }

    strncpy(input_data[0], sender, STRING_SIZE);
    strncpy(input_data[1], message_type, STRING_SIZE);
    input_length[0] = strlen(input_data[0]);
    input_length[1] = strlen(input_data[1]);

    if (mysql_stmt_execute(stmt))
    {
        fprintf(stderr, " mysql_stmt_execute, 2 failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        exit(0);
    }

    /* Bind the result buffers for all 4 columns before fetching them */

    memset(bind, 0, sizeof(bind));

    /* INTEGER COLUMN */
    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)str_data[0];
    bind[0].buffer_length = STRING_SIZE;
    bind[0].is_null = 0;
    bind[0].length = &length[0];

    /* STRING COLUMN */
    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = (char *)str_data[1];
    bind[1].buffer_length = STRING_SIZE;
    bind[1].is_null = 0;
    bind[1].length = &length[1];

    /* SMALLINT COLUMN */
    bind[2].buffer_type = MYSQL_TYPE_STRING;
    bind[2].buffer = (char *)&small_data;
    bind[2].is_null = 0;
    bind[2].length = &length[2];
    bind[2].buffer_length = STRING_SIZE;

    /* Bind the result buffers */
    if (mysql_stmt_bind_result(stmt, bind))
    {
        fprintf(stderr, " mysql_stmt_bind_result() failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        exit(0);
    }

    /* Now buffer all results to client */
    if (mysql_stmt_store_result(stmt))
    {
        fprintf(stderr, " mysql_stmt_store_result() failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        exit(0);
    }

    /* Fetch all rows */
    row_count = 0;
    fprintf(stdout, "Fetching results ...\n");
    while (!mysql_stmt_fetch(stmt))
    {
        row_count++;
        fprintf(stdout, "  row %d\n", row_count);

        /* column 1 */
        fprintf(stdout, "   column1 (integer)  : ");
        if (is_null[0])
        {
            fprintf(stdout, " NULL\n");
        }
        else
        {
            fprintf(stdout, " %s(%ld)\n", str_data[0], length[0]);
        }

        /* column 2 */
        fprintf(stdout, "   column2 (string)   : ");
        if (is_null[1])
        {
            fprintf(stdout, " NULL\n");
        }
        else
        {
            fprintf(stdout, " %s(%ld)\n", str_data[1], length[1]);
        }
        /* column 3 */
        fprintf(stdout, "   column3 (smallint) : ");
        if (is_null[2])
            fprintf(stdout, " NULL\n");
        else
            fprintf(stdout, " %s(%ld)\n", small_data, length[2]);

        fprintf(stdout, "\n");
    }

    /* Validate rows fetched */
    fprintf(stdout, " total rows fetched: %d\n", row_count);
    if (row_count != 1)
    {
        fprintf(stderr, " MySQL failed to return all rows\n");
        exit(0);
    }

    /* Free the prepared result metadata */
    mysql_free_result(prepare_meta_result);

    /* Close the statement */
    if (mysql_stmt_close(stmt))
    {
        fprintf(stderr, " failed while closing the statement\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        exit(0);
    }

    /*closes the database connection*/
    mysql_close(con);
}

int main(int argc, char **argv)
{
    char *sender = "A";
    char *message_type = "CreditReport";
    select_active_routes(sender, message_type);
    return 0;
}