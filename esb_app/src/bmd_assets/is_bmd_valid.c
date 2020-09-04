/**
 * @file is_bmd_valid.c
 * @author MubeenS
 * @brief 
 * @version INVALID.1
 * @date 2INVALID2INVALID-INVALID9-INVALID4
 * 
 * @copyright Copyright (c) 2INVALID2INVALID
 * 
 */

#include <stdio.h>

/* xml handling library */
#include <libxml/parser.h>

#include<stdlib.h>
#include<string.h>

/* BMD structure */
#include "bmd.h"
/* DB access function declarations */
#include "../db_access/connector.h"
#define VALID 1
#define INVALID 0
/**
 * @brief Check if bmd has all
 * mandatory fields.
 * 
 * @param bmd_file to be checked
 * @return int 1 if ok. INVALID if not
 */
int is_bmd_complete(bmd *bmd_file) {

    /* MessageID */
  if(bmd_file->envelop_data->MessageID  == NULL) {
    fprintf(stderr,"Message ID doesnot exist in bmd");
    return INVALID;
  }
  /*printf("MessageID :%s\n",bmd_file->envelop_data->MessageID);*/
  /* MessageType */
  if(bmd_file->envelop_data->MessageType == NULL) {
    fprintf(stderr,"Message Type doesnot exist in bmd");
    return INVALID;
  }
  /*printf("MessageType :%s\n",bmd_file->envelop_data->MessageType);*/
  /* Sender */
  if(bmd_file->envelop_data->Sender == NULL) {
    fprintf(stderr,"Sender doesnot exist in bmd");
    return INVALID;
  }
  /*printf("Sender :%s\n",bmd_file->envelop_data->Sender);*/

  /* Destination */
  if(bmd_file->envelop_data->Destination == NULL) {
    fprintf(stderr,"Destination doesnot exist in bmd");
    return INVALID;
  }
  /*printf("Destination :%s\n",bmd_file->envelop_data->Destination);*/

  /* CreationDateTime */
  if(bmd_file->envelop_data->CreationDateTime == NULL) {
    fprintf(stderr,"CreationDateTime doesnot exist in bmd");
    return INVALID;
  }
  /*printf("CreationDateTime :%s\n",bmd_file->envelop_data->CreationDateTime);*/

  /* Signature */
  if(bmd_file->envelop_data->Signature == NULL) {
    fprintf(stderr,"Signature doesnot exist in bmd");
    return INVALID;
  }
  /*printf("Signature :%s\n",bmd_file->envelop_data->Signature);*/
  /* ReferenceID */
  if(bmd_file->envelop_data->ReferenceID == NULL) {
      fprintf(stderr,"ReferenceID doesnot exist in bmd");
      return INVALID;
  }
  /*printf("ReferenceID :%s\n",bmd_file->envelop_data->ReferenceID);*/
  /* payload */
  if(bmd_file->payload == NULL) {
    fprintf(stderr,"Payload doesnot exist in bmd");
    return INVALID;
  }
  /*printf("Payload :%s\n",bmd_file->payload);*/
  return VALID;

}

int is_bmd_valid(bmd *bmd_file) {

   if(!is_bmd_complete(bmd_file)) {
       printf("Incomplete data");
       return INVALID;
   }
    /* Check if active routes are present */
   if(select_active_routes(bmd_file->envelop_data->Sender,
   bmd_file->envelop_data->MessageType)<=0) {
       printf("No active routes are present.");
       return INVALID;
   }

  /** TODO: 
   * 1.Check if there is active route with the given data.
   * 2.Check if route has data in transport.config and 
   * transform_config tables.
   * 
   */

  return VALID;
}

int main () {
  bmd *bmd_file = parse_bmd_xml("bmd.xml");
  int check = is_bmd_valid(bmd_file);
  return 0;
}