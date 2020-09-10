#include <stdio.h>

typedef struct transform_config{
    char *key;
    char *value;
}transform_t;

char * xml_to_json(bmd *bmd_file);