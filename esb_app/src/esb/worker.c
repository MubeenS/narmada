
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

#include "../adapter/adapter.h"

#include <pthread.h>

#define STRING_SIZE 100

void *poll_database_for_new_requests(void *vargp)
{
    int i = 0;
    while (i < 99)
    {
        i++;
        printf("\n%%%%\nWorker started..\n%%%%\n");
        task_t *request = fetch_new_esb_request();
        if (request == NULL)
        {
            printf("No requests available.\n");
            goto sleep;
 
        }
        else
        { /* Update request is being processed */
            update_esb_request("PROCESSING", request->id);
        }

        /* Get the route_id to handle the request */
        int route_id = get_active_route_id(request->sender,
                                           request->destination,
                                           request->message_type);

        /* Get transformation and transportation configuration */
        transform_t *transform = fetch_transform_config(route_id);
        transport_t *transport = fetch_transport_config(route_id);

        /**
          * TODO: If there is any transformation required,
          * we need to invoke those function's accordingly.
          * 
          */
        if (!(strcmp(transform->value, "No Transform")))
        {
            /** TODO: Invoke transform function.
              * For IFSC no transform is needed.
              */
        }
        /* Parse xml file to get a bmd */
        bmd *bmd_file = parse_bmd_xml(request->data_location);
        /* String to store path of file to be sent */

        char *to_be_sent;
        /* Generate HTTP url required to call
           destination service */
        char url[STRING_SIZE];

        sprintf(url, "%s%s", transport->value, bmd_file->payload);
        //to_be_sent = (char *)call_function(transport->key, (void *)url,
        //  (void *)transport->key);
        /** Payload to json contacts destination service
          * Stores the received data in a file and returns
          * the file path.*/
        to_be_sent = payload_to_json(bmd_file, url);

        if (to_be_sent == NULL)
        {
            printf("Json creation failed.");
        }

        char *rc = call_function("EMAIL", "testmailtm02@gmail.com",
                                 to_be_sent);
        if (rc != NULL)
        {
            printf("Email sending failed.!\n");
            int status = update_esb_request("RECEIVED", request->id);
            if (status == 0)
            {
                printf("Update failed.!\n");
            }
        }
        else
        {
            printf("Mail sent.!\n");
        }

        char *response;
        /**
         * @brief REQ.RES is an api that gives
         * response to HTTP request. The response 
         * contains data sent along with creation time.
         * Choosen for testing purposes.
         * 
         */

        response = (char *)call_function("HTTP_POST",
                                         "https://reqres.in/api/users",
                                         to_be_sent);

        if (response == NULL)
        {
            printf("HTTP posting failed.!\n");
            int status = update_esb_request("RECEIVED", request->id);
            if (status == 0)
            {
                printf("Update failed.!\n");
            }
        }
        else
        {
            printf("Posted via HTTP.\n");
            printf("\n\nFile response from REQ.RES:\n");
            int check = print_file(response);
            if(check !=0) {
                printf("Printing response failed..\n");
            }
            printf("\n");
            update_esb_request("DONE", request->id);
        }
        sleep:
        printf("Sleeping for 5 seconds.\n");
        sleep(5);
    }
    printf("Worker exited..\n");
    return NULL;
}

/*int main()
{

    pthread_t thread_id;
    printf("Before Thread\n");
    pthread_create(&thread_id, NULL, poll_database_for_new_requests, NULL);
    pthread_join(thread_id, NULL);
    printf("After Thread\n");
    return 0;
}*/