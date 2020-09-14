#ifndef TRANSPORT_H
#define TRANSPORT_H

typedef struct transport_config {
    char *key;
    char *value;
}transport_t;


/* Email */
void* send_mail(void *toptr, void *file_path_ptr);

/* Destination Service ifsc */
void* call_destination_service(void *urlptr,void *apiptr);

/* Posts to destination */
void* http_post(void *toptr, void *dataptr);

/* Can be used to print HTTP response */
int print_file(char *file_name);
#endif