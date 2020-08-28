#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 

/**
 * @brief 
 * 
 * @param data holds eror data
 * @param argc number off columns in result
 * @param argv array of strings representing fields in the row
 * @param azColName array of strings represinting column names
 */
static int callback(void *data, int argc, char **argv, char **azColName){
   int i;
   fprintf(stderr, "%s: ", (const char*)data);
   
   for(i = 0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   
   printf("\n");
   return 0;
}

/**
 * @brief 
 * selects all fields from routes table
 * based on matching parameters
 * @param sender
 * @param message_type 
 */
void select_all_routes(char *sender, char *message_type) {
    sqlite3 *db; /*database handle*/
    char *err_msg = 0; /* stores errormessage */
    sqlite3_stmt *stmnt;/* single sql statement */
    
    int rc = sqlite3_open("test.db", &db);

    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return ;
    }
    
    char *sql = "SELECT * FROM routes WHERE sender = ?                   \
                 AND message_type = ? AND is_active = ?"; 
    
    rc = sqlite3_prepare_v2(db,sql,sizeof(sql),&stmnt,NULL);

    if (rc == SQLITE_OK) {
        //binds the values to their respective place holders
        sqlite3_bind_text(stmnt, 1, sender, -1, NULL);
        sqlite3_bind_text(stmnt, 2, message_type, -1, NULL);
    } else {
        
        fprintf(stderr, "Failed to execute statement: %s\n",\
        sqlite3_errmsg(db));
    }

    int step = sqlite3_step(stmnt);
    /**
     * @brief Consta new while objectruct 
     * 
     */
    while(step == SQLITE_ROW) {
        printf("%s: ",sqlite3_column_text(stmnt,0));
        printf("%s: ",sqlite3_column_text(stmnt,1));
        printf("%s: ",sqlite3_column_text(stmnt,2));
        printf("%s: ",sqlite3_column_text(stmnt,3));
        printf("%s: \n",sqlite3_column_text(stmnt,4));
    }
    
    sqlite3_finalize(stmnt);
    sqlite3_close(db);
}

int main (void) {
    char *sender;
    char *msg;
    printf("Enter sender:");
    scanf("%s",sender);
    printf("Enter message type:");
    scanf("%s",msg);
    select_all_routes(sender,msg);
    return 0;
}