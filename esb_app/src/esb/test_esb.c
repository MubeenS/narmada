#include <stdio.h>

#include "../test/munit.h"
#include "esb.h"
/** Include Module that has bmd handling 
 * functions and  bmd structure declaration 
 * 
 */ 
#include "../bmd_assets/bmd.h"

/** Module that has mysql C API functions */

#include "../db_access/connector.h"


static void *
queue_the_request_setup(const MunitParameter params[], void *user_data)
{ /* Creates bmd and returns */
   bmd *b = parse_bmd_xml("bmd.xml");
   return b;
}

static void
queue_the_request_tear_down(void *fixture)
{
    /* Receives the pointer to the data if that that was created in
    queue_the_request_setup function. */
    bmd *b = (bmd *) fixture;
    free(b->envelop_data);
    free(b->payload);
    free(b);
}

static MunitResult
test_queue_the_request(const MunitParameter params[], void *fixture)
{
    bmd *b = (bmd *)fixture;

    munit_assert(queue_the_request(b)==1);
    return MUNIT_OK;
}


static MunitResult
test_process_esb_request(const MunitParameter params[], void *fixture)
{
    bmd *b = (bmd *)fixture;

    munit_assert(process_esb_request("bmd1.xml")==1);
    return MUNIT_OK;
}

/* Put all unit tests here. */
MunitTest esb_tests[] = {
     {
        "/process_esb_request",   /* name */
        test_process_esb_request,  /* test function */
        NULL,    /* setup function for the test */
        NULL,    /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL                    /* parameters */
    },
    
    {
        "/queue_the_request",   /* name */
        test_queue_the_request,  /* test function */
        queue_the_request_setup,    /* setup function for the test */
        queue_the_request_tear_down,    /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL                    /* parameters */
    },
    /* Mark the end of the array with an entry where the test
   * function is NULL */
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

/* Arrange the test cases into a test suite. */
static const MunitSuite suite = {
  "/esb_tests", /* name */
  esb_tests, /* tests */
  NULL, /* suites */
  1, /* iterations */
  MUNIT_SUITE_OPTION_NONE /* options */
};

/* Run the the test suite */
int main (int argc, const char* argv[]) {
  return munit_suite_main(&suite, NULL, argc, NULL);
}