#include <stdio.h>
#include "../bmd_handler/bmd.h"

#ifndef ESB_H
#define ESB_H
/* A task tag that has request information */
typedef struct task {
    int id; /* Unique request_ID */
    char *sender;
    char *destination;
    char *message_type;
    char *data_location;
    int processing_attempts;
}task_t;

int queue_the_request(bmd *b,char *file_path);
int process_esb_request(char* bmd_file_path);
int fetch_new_request_from_db(task_t*request);
void *poll_database_for_new_requets(void *vargp);

#endif