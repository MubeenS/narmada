/**
 * @file test_adapter.c
 * @author Nikhil
 * @brief 
 * @version 0.1
 * @date 2020-09-17
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include<stdio.h>
#include "../test/munit.h"
#include "transform.h"
#include "transport.h"
#include "adapter.h"

static MunitResult
test_send_mail(const MunitParameter params[], void *fixture) {
    int rc=send_mail("testmailtm02@gmail.com","Returnfile.json");
    munit_assert(rc == 0);
    return MUNIT_OK;
}

static MunitResult
test_http_post(const MunitParameter params[], void *fixture) {
    char* rc=http_post("https://reqres.in/api/users", "name=Test&job=Testing");
    munit_assert_string_equal(rc,"Returnfile.json");
    return MUNIT_OK;
}



MunitTest adapter_tests[]={ 
    {
        "/test_send_mail",   /* name */
        test_send_mail,      /* test function */
        NULL,     /* setup function for the test */
        NULL, /* tear_down */
        MUNIT_TEST_OPTION_NONE,  /* options */
        NULL                     /* parameters */
    },{
        "/test_http_post",   /* name */
        test_http_post,      /* test function */
        NULL,     /* setup function for the test */
        NULL, /* tear_down */
        MUNIT_TEST_OPTION_NONE,  /* options */
        NULL                     /* parameters */
    },
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}    
};

static const MunitSuite suite = {
    "/adapter_tests",           /* name */
    adapter_tests,              /* tests */
    NULL,                   /* suites */
    1,                      /* iterations */
    MUNIT_SUITE_OPTION_NONE /* options */
};

/* Run the the test suite */
int main(int argc, const char *argv[])
{
  return munit_suite_main(&suite, NULL, argc, NULL);
}