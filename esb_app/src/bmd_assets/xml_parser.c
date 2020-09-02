/**
 * @file xml_parser.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-09-02
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <string.h>

/*xml handling library*/
#include <libxml/parser.h>
#include <libxml/tree.h>
/* Contains envelope and payload structs*/
#include "bmd.h"


<<<<<<< HEAD
envelope_data extract_envelop(xmlDocPtr doc, xmlNsPtr ns, xmlNodePtr cur) {
=======
envelop extract_envelop(char* bmd_xml) {
>>>>>>> f57e02ca622c4304fd65e383cfb2cce63ee6a9e4
    /** TODO: code to extract data from xml and store in structuers*/
    /** TODO: see Real example and former xml_parser.c */
    envelope_data ret;
    ret = (envelope_data) malloc(sizeof(envelope));
    if (ret == NULL) {
        fprintf(stderr,"out of memory\n");
        return(NULL);
    }
    memset(ret, 0, sizeof(envelope));

 cur = cur->xmlChildrenNode;
    while (cur != NULL) {
        
        if ((!strcmp(cur->name, "MessageID")) && (cur->ns == ns))
            ret->MessageID = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
        if ((!strcmp(cur->, "MessageType")) && (cur->ns == ns))
            ret->MessageType = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
        if ((!strcmp(cur->name, "Sender")) && (cur->ns == ns))
            ret->Sender = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         if ((!strcmp(cur->name, "Destination")) && (cur->ns == ns))
            ret->Destination = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
        if ((!strcmp(cur->name, "CreationDateTime")) && (cur->ns == ns))
            ret->CreationDateTime = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
        if ((!strcmp(cur->name, "Signature")) && (cur->ns == ns))
            ret->Signature = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
        if ((!strcmp(cur->name, "Reference")) && (cur->ns == ns))
            ret->Reference = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
        cur = cur->next;
    }

    return(ret);

}

<<<<<<< HEAD
payload_data extract_payload(xmlDocPtr doc, xmlNsPtr ns, xmlNodePtr cur) {
=======
char * extract_payload(char* bmd_xml) {
>>>>>>> f57e02ca622c4304fd65e383cfb2cce63ee6a9e4
    /**extract payload details*/

     payload_data ret;
    ret = (payload_data) malloc(sizeof(payload));
    if (ret == NULL) {
        fprintf(stderr,"out of memory\n");
        return(NULL);
    }
    memset(ret, 0, sizeof(payload));

 cur = cur->xmlChildrenNode;
    while (cur != NULL) {
    if ((!strcmp(cur->name, "data")) && (cur->ns == ns))
            ret->data = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
        cur = cur->next;
}

}

int main()
{    /** TODO: Call functions from here*/
    /** TODO: write test cases*/
<<<<<<< HEAD


=======
>>>>>>> f57e02ca622c4304fd65e383cfb2cce63ee6a9e4
}
