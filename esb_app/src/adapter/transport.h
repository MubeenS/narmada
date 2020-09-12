#ifndef TRANSPORT_H
#define TRANSPORT_H

typedef struct transport_config {
    char *key;
    char *value;
}transport_t;


/* Email */
int send_mail(char *to, char *file_path);

/* Destination Service ifsc */
char* call_destination_service(char *url);
#endif