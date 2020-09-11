#include <stdio.h>
#include "../test/munit.h"
#include "connector.h"
#include "../bmd_handler/bmd.h"

/* Test setup function */
static void *
insert_to_esb_request_setup(const MunitParameter params[], void *user_data)
{
  char *file = "bmd.xml";
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
  munit_assert(rc == 1);

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


static void *
get_active_route_id_setup(const MunitParameter params[], void *user_data)
{
  char *file = "bmd.xml";
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
       NULL,     /* setup function for the test */
        NULL, /* tear_down */
        MUNIT_TEST_OPTION_NONE,         /* options */
        NULL                            /* parameters */
    },

    {
        "/has_transform_config",        /* name */
        test_has_transform_config,      /* test function */
        NULL,     /* setup function for the test */
        NULL, /* tear_down */
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