/**
 * @brief contains envelope details.
 * 
 */

typedef struct bmd_envelop {
  const unsigned char *MessageID;
  const unsigned char *MessageType;
  const unsigned char *Sender;
  const unsigned char *Destination;
  const unsigned char *CreationDateTime;
  const unsigned char *Signature;
  const unsigned char *ReferenceID;
  const unsigned char *User_properties;

}envelop;


typedef struct bmd_ {
  envelop envolop_data;
  char * payload;
}bmd;