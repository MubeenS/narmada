#include <stdio.h>
#include "../test/munit.h"
#include "bmd.h"

char *get_str_data(char *file)
{
  long f_size;
  char *str_data;
  size_t file_size, result;
  FILE *fp = fopen(file, "r");
  fseek(fp, 0, SEEK_END);
  /* Reads the size of the file */
  f_size = ftell(fp);
  fseek(fp, 0, SEEK_SET);
  file_size = sizeof(char) * f_size;
  str_data = malloc(file_size);
  /* fread returns number of items actually read. */
  result = fread(str_data, 1, f_size, fp);
  return strdup(str_data);
}

/* Test setup function */
static void *
xml_to_json_setup(const MunitParameter params[], void *user_data)
{
  char *file = "../bmd_files/bmd1.xml";
  bmd *b = parse_bmd_xml(file);
  char *file_created = xml_to_json(b);
  /* Copy file data into string */
  char *json_data = get_str_data(file_created);
  return strdup(file_created);
}

/* Test function */
static MunitResult
test_xml_to_json(const MunitParameter params[], void *fixture)
{ 
  char *file_created = (char *)fixture;
  char *json_data = get_str_data(file_created);

  char *test_data = get_str_data("payload_test.json");

  munit_assert_string_equal(json_data, test_data);
  int size = find_size("payload_test.json");
  return MUNIT_OK;
}

static void
xml_to_json_tear_down(void *fixture)
{ char *file_created = (char *) fixture;
   int del = remove(file_created);
   /* Checks if file is deleted */
   munit_assert(!del);
  free(file_created);
}

/* Test setup function creates bmd and returns it */
static void *
is_bmd_valid_setup(const MunitParameter params[], void *user_data)
{
  char *file = "../bmd_files/bmd1.xml";
  bmd *b = parse_bmd_xml(file);
  return b;
}

/* Test function */
static MunitResult
test_is_bmd_valid(const MunitParameter params[], void *fixture)
{
  bmd *test_bmd = (bmd *)fixture;
  /* is_bmd_valid returns 1 if valid */
  munit_assert(is_bmd_valid(test_bmd) == 1);
  return MUNIT_OK;
}

static void
is_bmd_valid_tear_down(void *fixture)
{
  free(fixture);
}

/* Test setup function creates bmd and returns it */
static void *
parse_bmd_xml_setup(const MunitParameter params[], void *user_data)
{
  char *file = "../bmd_files/bmd1.xml";
  bmd *b = parse_bmd_xml(file);
  return b;
}

bmd *get_bmd(void)
{
  bmd *bmd_file = (bmd *)malloc(sizeof(bmd));
  envelop *envl = (envelop *)malloc(sizeof(envelop));
  envl->Sender = "A";
  envl->Destination = "Y";
  envl->CreationDateTime = "2020-08-12T05:18:00+00001";
  envl->MessageID = "A9ECAEF2-107A-4452-9553-043B6D25386E";
  envl->MessageType = "CreditReport";
  envl->ReferenceID = "INV-PROFILE-8897121";
  envl->Signature = "63f5f61f7a79301f715433f8f3689390d1f5da4f855169023300491c00b8113c1";
  bmd_file->envelop_data = envl;
  bmd_file->payload = "001-01-12341";

  return bmd_file;
}
/* Test function */
static MunitResult
test_parse_bmd_xml(const MunitParameter params[], void *fixture)
{
  bmd *test_bmd = (bmd *)fixture;
  bmd *expected_bmd = get_bmd();
  /* is_bmd_valid returns 1 if valid */
  munit_assert_string_equal(test_bmd->envelop_data->Sender,
                            expected_bmd->envelop_data->Sender);
  munit_assert_string_equal(test_bmd->envelop_data->Destination,
                             expected_bmd->envelop_data->Destination);
  munit_assert_string_equal(test_bmd->envelop_data->MessageType,
                            expected_bmd->envelop_data->MessageType);
  munit_assert_string_equal(test_bmd->envelop_data->CreationDateTime,
                             expected_bmd->envelop_data->CreationDateTime);
  munit_assert_string_equal(test_bmd->envelop_data->MessageID,
                             expected_bmd->envelop_data->MessageID);
  munit_assert_string_equal(test_bmd->envelop_data->Signature,
                             expected_bmd->envelop_data->Signature);
  munit_assert_string_equal(test_bmd->envelop_data->ReferenceID,
                             expected_bmd->envelop_data->ReferenceID);
  munit_assert_string_equal(test_bmd->payload,expected_bmd->payload);
  
  return MUNIT_OK;
}

static void
parse_bmd_xml_tear_down(void *fixture)
{
  bmd *b = (bmd *)fixture;

  free(b->envelop_data);
  free(b->payload);
  free(b);

}

/* Put all unit tests here. */
MunitTest bmd_tests[] = {
    {
        "/parse_bmd_xml_test",   /* name */
        test_parse_bmd_xml,      /* test function */
        parse_bmd_xml_setup,     /* setup function for the test */
        parse_bmd_xml_tear_down, /* tear_down */
        MUNIT_TEST_OPTION_NONE,  /* options */
        NULL                     /* parameters */
    },

    {
        "/is_bmd_valid_test",   /* name */
        test_is_bmd_valid,      /* test function */
        is_bmd_valid_setup,     /* setup function for the test */
        is_bmd_valid_tear_down, /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL                    /* parameters */
    },

    {
        "/xml_to_json_test",    /* name */
        test_xml_to_json,       /* test function */
        xml_to_json_setup,      /* setup function for the test */
        xml_to_json_tear_down,  /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL                    /* parameters */
    },
    /* Mark the end of the array with an entry where the test
   * function is NULL */
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

/* Arrange the test cases into a test suite. */
static const MunitSuite suite = {
    "/bmd_tests",           /* name */
    bmd_tests,              /* tests */
    NULL,                   /* suites */
    1,                      /* iterations */
    MUNIT_SUITE_OPTION_NONE /* options */
};

/* Run the the test suite */
int main(int argc, const char *argv[])
{
  return munit_suite_main(&suite, NULL, argc, NULL);
}