#include<stdio.h>
#include "email.h"
#include "esb.h"

/**
 * TODO: This is to be implemented separately.
 */
bmd parse_bmd_xml(char* bmd_file_path) {
    bmd b;
    bmd_envelop envl;
    envl.sender_id = "TEST-GUID-1";
    envl.destination_id = "TEST-GUID-2";
    envl.message_type = "TEST-GUID-3";

    b.envelop = envl;
    b.payload = "Some data here";
    return b;
}

int is_bmd_valid(bmd b)
{
    int valid = 1; // 1 => vaild, -1 => invalid
    // TODO: Implement the validation logic here

    return valid;
}

