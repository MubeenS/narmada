/**
 * @brief contains envelope and payload
 * details. Has complete bmd structure.
 * 
 */


/*envelop*  extract_envelop(char * filepath);
bmd* parse_bmd_xml(char *bmd_xml_file);*/


typedef struct bmdMessage_ {
   char *MessageID;
   char *MessageType;
   char *Sender;
   char *Destination;
   char *CreationDateTime;
   char *Signature;
   char *ReferenceID;
   char *User_properties;
}envelop;

typedef struct bmd_ {
  envelop *envelop_data;
  char * payload;
}bmd;
