#include <stdio.h>
#include "../test/munit.h"
#include "connector.h"
#include "../bmd_handler/bmd.h"

/* Test setup function */
static void *
insert_to_esb_request_setup(const MunitParameter params[], void *user_data)
{
  char *file = "../bmd_files/bmd1.xml";
  bmd *b = parse_bmd_xml(file);

  return b;
}

/* Test function */
static MunitResult
test_insert_to_esb_request(const MunitParameter params[], void *fixture)
{
  bmd *b = (bmd *)fixture;
  /* Check the return code */
  int rc = insert_to_esb_request(b->envelop_data->Sender,
                                 b->envelop_data->Destination,
                                 b->envelop_data->MessageType,
                                 b->envelop_data->ReferenceID,
                                 b->envelop_data->MessageID,
                                 "Routes", "RECEIVED",
                                 "received successfully",
                                 b->envelop_data->CreationDateTime);
  munit_assert(rc != 0);

  return MUNIT_OK;
}

static void
insert_to_esb_request_tear_down(void *fixture)
{
  bmd *b = (bmd *)fixture;
  free(b->envelop_data);
  free(b->payload);
  free(b);
}

static MunitResult
test_has_transform_config(const MunitParameter params[], void *fixture)
{;
  /* Check the return code */
  int rc = has_transform_config(1);
  munit_assert(rc != 0);
  return MUNIT_OK;
}

static MunitResult
test_has_transport_config(const MunitParameter params[], void *fixture)
{
  /* Check the return code */
  int rc = has_transport_config(1);
  munit_assert(rc != 0);
  return MUNIT_OK;
}

static MunitResult
test_select_all_transport_config(const MunitParameter params[], void *fixture)
{
  /* Check the return code */
  int rc = select_all_transport_config(1);
  munit_assert(rc != 0);
  return MUNIT_OK;
}


static void *
get_active_route_id_setup(const MunitParameter params[], void *user_data)
{
  char *file = "../bmd_files/bmd1.xml";
  bmd *b = parse_bmd_xml(file);
  return b;
}

static MunitResult
test_get_active_route_id(const MunitParameter params[], void *fixture)
{
  bmd *b = (bmd *)fixture;
  /* Check the return code */
  int rc = get_active_route_id(b->envelop_data->Sender,
                              b->envelop_data->Destination,
                              b->envelop_data->MessageType);
  munit_assert(rc != 0);
  return MUNIT_OK;
}

static void
get_active_route_id_tear_down(void *fixture)
{
  bmd *b = (bmd *)fixture;
  free(b->envelop_data);
  free(b->payload);
  free(b);
}


static void *
select_active_routes_setup(const MunitParameter params[], void *user_data)
{
  char *file = "../bmd_files/bmd1.xml";
  bmd *b = parse_bmd_xml(file);
  return b;
}

static MunitResult
test_select_active_routes(const MunitParameter params[], void *fixture)
{
  bmd *b = (bmd *)fixture;
  /* Check the return code */
  int rc = select_active_routes(b->envelop_data->Sender,
                              b->envelop_data->Destination,
                              b->envelop_data->MessageType);
  munit_assert(rc != 0);
  return MUNIT_OK;
}

static void
select_active_routes_tear_down(void *fixture)
{
  bmd *b = (bmd *)fixture;
  free(b->envelop_data);
  free(b->payload);
  free(b);
}

static MunitResult
test_update_esb_request(const MunitParameter params[], void *fixture)
{;
  /* Check the return code */
  int rc = update_esb_request("RECEIVED",1);
  munit_assert(rc != 0);
  return MUNIT_OK;
}


static MunitResult
test_bmd_xml(const MunitParameter params[], void* user_data) {
  const char* correct;

  correct = munit_parameters_get(params, "correct");
    
    //printf("%s\n",(char *) correct);

  /*if (strcmp(correct, "../bmd_files/bmd1.xml") == 0 ||
      strcmp(correct, "../bmd_files/bmd2.xml") == 0 ||
      strcmp(correct, "../bmd_files/bmd3.xml") == 0)
    return MUNIT_OK;*/

  bmd *test_bmd= parse_bmd_xml((char*)correct);

  printf("testing for each bmd file\n");

  if(strcmp(correct,"../bmd_files/bmd1.xml")==0)
  {
    munit_assert_string_equal(test_bmd->envelop_data->MessageID,"4ac268c2-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->MessageType,"CreditReport");
    munit_assert_string_equal(test_bmd->envelop_data->Sender,"4ac26b10-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->Destination,"4ac26c14-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->CreationDateTime,"2020-08-12T05:18:00+00001");
    munit_assert_string_equal(test_bmd->envelop_data->ReferenceID,"4ac26ce6-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->Signature,"S1");
    munit_assert_string_equal(test_bmd->payload,"SBIN0000882");
  }  

    if(strcmp(correct,"../bmd_files/bmd2.xml")==0)
  {
    munit_assert_string_equal(test_bmd->envelop_data->MessageID,"4ac26db8-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->MessageType,"CreditReport");
    munit_assert_string_equal(test_bmd->envelop_data->Sender,"4ac26e80-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->Destination,"4ac271fa-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->CreationDateTime,"2020-08-12T05:18:00+00001");
    munit_assert_string_equal(test_bmd->envelop_data->ReferenceID,"4ac272d6-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->Signature,"S2");
    munit_assert_string_equal(test_bmd->payload,"SBIN0000847");
  }    



    if(strcmp(correct,"../bmd_files/bmd3.xml")==0)
  {
    munit_assert_string_equal(test_bmd->envelop_data->MessageID,"4ac2739e-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->MessageType,"CreditReport");
    munit_assert_string_equal(test_bmd->envelop_data->Sender,"4ac27466-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->Destination,"4ac2752e-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->CreationDateTime,"2020-08-12T05:18:00+00001");
    munit_assert_string_equal(test_bmd->envelop_data->ReferenceID,"4ac275f6-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->Signature,"S3");
    munit_assert_string_equal(test_bmd->payload,"BKID0008605");
  }    

   if(strcmp(correct,"../bmd_files/bmd4.xml")==0)
  {
    munit_assert_string_equal(test_bmd->envelop_data->MessageID,"4ac278b2-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->MessageType,"CreditReport");
    munit_assert_string_equal(test_bmd->envelop_data->Sender,"4ac27984-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->Destination,"4ac27a42-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->CreationDateTime,"2020-08-12T05:18:00+00001");
    munit_assert_string_equal(test_bmd->envelop_data->ReferenceID,"4ac27af6-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->Signature,"S4");
    munit_assert_string_equal(test_bmd->payload,"IBKL0000001");
  }    
  

  if(strcmp(correct,"../bmd_files/bmd5.xml")==0)
  {
    munit_assert_string_equal(test_bmd->envelop_data->MessageID,"4ac27bb4-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->MessageType,"CreditReport");
    munit_assert_string_equal(test_bmd->envelop_data->Sender,"4ac27c68-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->Destination,"4ac27d26-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->CreationDateTime,"2020-08-12T05:18:00+00001");
    munit_assert_string_equal(test_bmd->envelop_data->ReferenceID,"4ac27de4-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->Signature,"S5");
    munit_assert_string_equal(test_bmd->payload,"ICIC0002652");
  }    
   

  if(strcmp(correct,"../bmd_files/bmd6.xml")==0)
  {
    munit_assert_string_equal(test_bmd->envelop_data->MessageID,"4ac27fe2-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->MessageType,"CreditReport");
    munit_assert_string_equal(test_bmd->envelop_data->Sender,"4ac280aa-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->Destination,"4ac28172-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->CreationDateTime,"2020-08-12T05:18:00+00001");
    munit_assert_string_equal(test_bmd->envelop_data->ReferenceID,"4ac2823a-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->Signature,"S6");
    munit_assert_string_equal(test_bmd->payload,"ICIC0006271");
  }    
     

  if(strcmp(correct,"../bmd_files/bmd7.xml")==0)
  {
    munit_assert_string_equal(test_bmd->envelop_data->MessageID,"4ac282f8-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->MessageType,"CreditReport");
    munit_assert_string_equal(test_bmd->envelop_data->Sender,"4ac283b6-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->Destination,"4ac2860e-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->CreationDateTime,"2020-08-12T05:18:00+00001");
    munit_assert_string_equal(test_bmd->envelop_data->ReferenceID,"4ac286cc-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->Signature,"S7");
    munit_assert_string_equal(test_bmd->payload,"ICIC0003239");
  }  

  if(strcmp(correct,"../bmd_files/bmd8.xml")==0)
  {
    munit_assert_string_equal(test_bmd->envelop_data->MessageID,"4ac2878a-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->MessageType,"CreditReport");
    munit_assert_string_equal(test_bmd->envelop_data->Sender,"4ac28848-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->Destination,"4ac28910-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->CreationDateTime,"2020-08-12T05:18:00+00001");
    munit_assert_string_equal(test_bmd->envelop_data->ReferenceID,"4ac289ce-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->Signature,"S8");
    munit_assert_string_equal(test_bmd->payload,"UTIB0000051");
  }  
 

  if(strcmp(correct,"../bmd_files/bmd9.xml")==0)
  {
    munit_assert_string_equal(test_bmd->envelop_data->MessageID,"4ac28c58-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->MessageType,"CreditReport");
    munit_assert_string_equal(test_bmd->envelop_data->Sender,"4ac28d16-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->Destination,"4ac28dde-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->CreationDateTime,"2020-08-12T05:18:00+00001");
    munit_assert_string_equal(test_bmd->envelop_data->ReferenceID,"4ac28e9c-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->Signature,"S9");
    munit_assert_string_equal(test_bmd->payload,"UTIB0001648");
  }  

  if(strcmp(correct,"../bmd_files/bmd9.xml")==0)
  {
    munit_assert_string_equal(test_bmd->envelop_data->MessageID,"4ac28c58-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->MessageType,"CreditReport");
    munit_assert_string_equal(test_bmd->envelop_data->Sender,"4ac28d16-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->Destination,"4ac28dde-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->CreationDateTime,"2020-08-12T05:18:00+00001");
    munit_assert_string_equal(test_bmd->envelop_data->ReferenceID,"4ac28e9c-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->Signature,"S9");
    munit_assert_string_equal(test_bmd->payload,"UTIB0001648");
  }

  if(strcmp(correct,"../bmd_files/bmd10.xml")==0)
  {
    munit_assert_string_equal(test_bmd->envelop_data->MessageID,"4ac28f5a-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->MessageType,"AvlBal");
    munit_assert_string_equal(test_bmd->envelop_data->Sender,"4ac29018-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->Destination,"4ac290d6-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->CreationDateTime,"2020-08-12T05:18:00+00001");
    munit_assert_string_equal(test_bmd->envelop_data->ReferenceID,"4ac292fc-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->Signature,"S7");
    munit_assert_string_equal(test_bmd->payload,"UTIB0003213");
  }

  
  return MUNIT_OK;
}



static char* correct_params[] = {
 (char*) "../bmd_files/bmd1.xml" ,
 (char*) "../bmd_files/bmd2.xml" ,
 (char*) "../bmd_files/bmd3.xml" ,
 (char*) "../bmd_files/bmd4.xml" ,
 (char*) "../bmd_files/bmd5.xml" ,
 (char*) "../bmd_files/bmd6.xml" ,
 (char*) "../bmd_files/bmd7.xml" ,
 (char*) "../bmd_files/bmd8.xml" ,
 (char*) "../bmd_files/bmd9.xml" ,
 (char*) "../bmd_files/bmd10.xml",
  NULL
};


static MunitParameterEnum test_params[] = {
  { (char*) "correct", correct_params }
};



/* Put all unit tests here. */
MunitTest db_access_tests[] = {
    {
        "/get_active_route_id",        /* name */
        test_get_active_route_id,      /* test function */
        get_active_route_id_setup,     /* setup function for the test */
        get_active_route_id_tear_down, /* tear_down */
        MUNIT_TEST_OPTION_NONE,        /* options */
        NULL                           /* parameters */
    },
    {
        "/has_transport_config",        /* name */
        test_has_transport_config,      /* test function */
        NULL,                           /* setup function for the test */
        NULL,                           /* tear_down */
        MUNIT_TEST_OPTION_NONE,         /* options */
        NULL                            /* parameters */
    },

    {
        "/has_transform_config",        /* name */
        test_has_transform_config,      /* test function */
        NULL,                           /* setup function for the test */
        NULL,                           /* tear_down */
        MUNIT_TEST_OPTION_NONE,         /* options */
        NULL                            /* parameters */
    },
    {
        "/insert_to_esb_request_test",   /* name */
        test_insert_to_esb_request,      /* test function */
        insert_to_esb_request_setup,     /* setup function for the test */
        insert_to_esb_request_tear_down, /* tear_down */
        MUNIT_TEST_OPTION_NONE,          /* options */
        NULL                             /* parameters */
    },
    {
        "/select_active_routes",        /* name */
        test_select_active_routes,      /* test function */
        select_active_routes_setup,     /* setup function for the test */
        select_active_routes_tear_down, /* tear_down */
        MUNIT_TEST_OPTION_NONE,        /* options */
        NULL                           /* parameters */
    },
    {
        "/select_all_transport_config",        /* name */
        test_select_all_transport_config,      /* test function */
        NULL,                                  /* setup function for the test */
        NULL,                                  /* tear_down */
        MUNIT_TEST_OPTION_NONE,                /* options */
        NULL                                   /* parameters */
    },
    {
        "/update_esb_request",        /* name */
        test_update_esb_request,      /* test function */
        NULL,                           /* setup function for the test */
        NULL,                           /* tear_down */
        MUNIT_TEST_OPTION_NONE,         /* options */
        NULL                            /* parameters */
    },
    {
        "/test_bmd_files" ,
        test_bmd_xml, 
        NULL,
        NULL,
        MUNIT_TEST_OPTION_NONE,
        test_params 
    },
    /* Mark the end of the array with an entry where the test
   * function is NULL */
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

/* Arrange the test cases into a test suite. */
static const MunitSuite suite = {
    "/db_access_tests",     /* name */
    db_access_tests,        /* tests */
    NULL,                   /* suites */
    1,                      /* iterations */
    MUNIT_SUITE_OPTION_NONE /* options */
};

/* Run the the test suite */
/*int main(int argc, const char *argv[])
{
  return munit_suite_main(&suite, NULL, argc, NULL);
}*/
