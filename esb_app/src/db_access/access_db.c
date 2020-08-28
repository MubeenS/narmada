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
 * selects required fields based on 
 * sender and message_type 
 * @param sender 
 * @param message_type 
 */
void select_all_routes(char *sender, char *message_type) {
    sqlite3 *db; //database handle
    char *err_msg = 0; //to store errormessage
    sqlite3_stmt *stmnt;//single sql statement
    
    int rc = sqlite3_open("test.db", &db);

    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return 1;
    }
    
    char *sql = "SELECT * FROM routes WHERE sender = ?                   \
                 AND message_type = ? AND is_active = ?"; 
    
    rc = sqlite3_prepare_v2(db,sql,sizeof(sql),&stmnt,NULL);

    if (rc == SQLITE_OK) {
        //binds the values to their respective place holders
        sqlite3_bind_text(res, 1, sender);
        sqlite3_bind_text(res, 2, message_type);
    } else {
        
        fprintf(stderr, "Failed to execute statement: %s\n",\
        sqlite3_errmsg(db));
    }

    int step = sqlite3_step(stmnt);
    
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