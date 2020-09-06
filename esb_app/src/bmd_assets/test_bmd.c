#include <stdio.h>
#include "../test/munit.h"
#include "bmd.h"

char *get_str_data(char *file)
{
    long f_size;
    char *str_data;
    size_t code_s, result;
    FILE *fp = fopen(file, "r");
    fseek(fp, 0, SEEK_END);
    f_size = ftell(fp); /* This returns 29696, but file is 85 bytes */
    fseek(fp, 0, SEEK_SET);
    code_s = sizeof(char) * f_size;
    str_data = malloc(code_s);
    result = fread(str_data, 1, f_size, fp);
    return strdup(str_data);
}

static MunitResult
test_xml_to_json(const MunitParameter params[], void *fixture)
{
    bmd *b = parse_bmd_xml("bmd.xml");
    char *file_created = xml_to_json(b);
    /* Copy file data into string */
    char *json_data = get_str_data(file_created);
    char *test_data = get_str_data("payload_test.json");

    munit_assert_string_equal(json_data, test_data);

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
  return munit_suite_main(&suite, NULL, argc, NULL);
}