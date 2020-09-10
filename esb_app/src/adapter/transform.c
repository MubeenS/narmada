
#include <stdio.h>

/* xml handling library */
#include <libxml/parser.h>

#include<stdlib.h>
#include<string.h>
/* BMD structure */
#include "../bmd_handler/bmd.h"

#include "transform.h"
char * xml_to_json(bmd *bmd_file) {
   
    char bmd_name[20];
    /*Creates file name of json as per bmd name*/
    char file[50];
    /* Appends name of messageID */
    sprintf(file,"../assets/payload_%s.json",bmd_file->envelop_data->MessageID);
   
    char *payload_data = bmd_file->payload;
    FILE *fp;
    fp = fopen(file,"w");
    if(fp == NULL) {
        printf("file opening filed");
        exit(0);
    }
    /* Writes into json file */
    fprintf(fp,"{\n \"Payload\":\"%s\"\n}",payload_data);
    /* Closes file */
    fclose(fp);
    /* returns json filename */
    return strdup(file);
}

int main () {
    bmd *file = parse_bmd_xml("../bmd_files/bmd1.xml");
    char *file_path = xml_to_json(file);
    printf("%s",file_path);
}