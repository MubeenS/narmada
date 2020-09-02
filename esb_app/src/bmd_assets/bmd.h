/**
 * @brief contains envelope details.
 * 
 */

typedef struct bmd_envelope {
  const unsigned char *MessageID;
  const unsigned char *MessageType;
  const unsigned char *Sender;
  const unsigned char *Destination;
  const unsigned char *CreationDateTime;
  const unsigned char *Signature;
  const unsigned char *ReferenceID;
  const unsigned char *User_properties;

}envelope;

/**
 * @brief Payload details
 * 
 */

typedef struct bmd_payload {
  const unsigned char *data;
} payload;
