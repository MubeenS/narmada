#include <stdio.h>
#include "../test/munit.h"
#include "bmd.h"


static MunitResult
test_xml_to_json(const MunitParameter params[], void *fixture)
{
    bmd *b = parse_bmd_xml("bmd.xml");

    char *file_created = xml_to_json(b)
    munit_assert_string_equal(file_created, "payload_test.json");

    return MUNIT_OK;
}

/** TODO: tear down deleting files created during test.
 * 
 */

/* Put all unit tests here. */
MunitTest bmd_tests[] = {
    {
        "/xml_to_json_test",   /* name */
        test_xml_to_json,  /* test function */
        NULL,    /* setup function for the test */
        NULL,    /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL                    /* parameters */
    },
    /* Mark the end of the array with an entry where the test
   * function is NULL */
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
    };

/* Arrange the test cases into a test suite. */
static const MunitSuite suite = {
  "/my-tests", /* name */
  bmd_tests, /* tests */
  NULL, /* suites */
  1, /* iterations */
  MUNIT_SUITE_OPTION_NONE /* options */
};

/* Run the the test suite */
int main (int argc, const char* argv[]) {
  return munit_suite_main(&suite, NULL, argc, argv);
}
