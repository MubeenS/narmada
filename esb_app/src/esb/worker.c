/**
 * @file worker.c
 * @author MubeenS
 * @brief A worker thread performs following operations:
 * 1.Fetches new request from database whose status = 'RECEIVED'
 * 2.Transforms if needed.
 * 3.Transports the payload to destination.
 * 4.Updates status of request in database.
 * 
 * @version 0.1
 * @date 2020-09-08
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <string.h>

#include <unistd.h>

#include "esb.h"

#include "../db_access/connector.h"

#include "../adapter/transform.h"

#include "../adapter/transport.h"

#include <pthread.h>

#define STRING_SIZE 100

char* create_file(char *data) {
         FILE *fp;
         char *file = "../assets/ToBeMailed.json";
        fp = fopen(file, "w");
        if (fp == NULL)
        {
            printf("file opening failed");
            exit(0);
        }
        /* Writes into json file */
        fprintf(fp, "%s", data);
        return strdup(file);
}
void *poll_database_for_new_requets(void *vargp)
{
#if 0
    // Step 1: Open a DB connection
    int i = 0;
    while (i < 99)
    {
        i++;
        /**
         * Step 2: Query the esb_requests table to see if there
         * are any newly received BMD requets.
         */
        task_t *req;
        /**
         * Step 3:
         */
        if (fetch_new_request_from_db(req))
        {
            /**
              * Found a new request, so we will now process it.
              * See the ESB specs to find out what needs to be done
              * in this step. Basically, you will be doing:
              * 1. Find if there is any transformation to be applied to
              *    the payload before transporting it to destination.
              * 2. If needed, transform the request.
              * 3. Transport the transformed data to destination.
              * 4. Update the status of the request in esb_requests table
              *    to mark it as done (or error) depending on the outcomes
              *    of this step.
              * 5. Cleanup
              */
            printf("Applying transformation and transporting steps.\n");
        }
        /**
         * Sleep for polling interval duration, say, 5 second.
         * DO NOT hard code it here!
         */
        printf("Sleeping for 5 seconds.\n");
        sleep(5);
    }
#endif
    task_t *request = fetch_new_esb_request();
    if (request == NULL)
    {
        fprintf(stderr, "Request fetching failed.");
        exit(0);
    }
    printf("New request fetched from esb_request table.");
    /* Get the route_id to handle the request */
    int route_id = get_active_route_id(request->sender,
                                       request->destination,
                                       request->message_type);
    
    /* update status as processing */
    int check = update_esb_request("PROCESSING",route_id);
    
    if(!check) {
        printf("Request status update failed.");
        exit(0);
    }
    
    /* Get transformation and transportation configuration */
    transform_t *transform = fetch_transform_config(route_id);
    transport_t *transport = fetch_transport_config(route_id);

    /* Parse xml file to get a bmd */
    bmd *bmd_file = parse_bmd_xml(request->data_location);
    /* String to store path of file to be sent */

    /** TODO: 
     * 1.Contact destination sevice.
     * 2.Transform and transport accordingly.
     * 
     */
    /** Skeleton */

    char *to_be_sent;

    if (!strcmp(transform->key,"IFSC"))
    {
        /* No transform Needed*/
    }

        /* Generate HTTP url required to call
           destination service */
        char url[STRING_SIZE];

        sprintf(url,"%s%s",transport->value,bmd_file->payload);
        /* Get data from destination service 
        that should be sent */
        to_be_sent = call_destination_service(url);
        if(!to_be_sent){
            printf("Calling destination service failed");
        }
        char* file_path = create_file(to_be_sent);
        int rc = send_mail(bmd_file->envelop_data->Destination, 
                           file_path);
     
    sleep(5);
}

int main () {
    
    pthread_t thread_id; 
    printf("Before Thread\n"); 
    pthread_create(&thread_id, NULL, poll_database_for_new_requets, NULL); 
    pthread_join(thread_id, NULL); 
    printf("After Thread\n"); 

    return 0;
}