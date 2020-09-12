#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define STRING_SIZE 100
struct string
{
  char *ptr;
  size_t len;
};

void init_string(struct string *s)
{ 
  printf("string initialisation\n");
  s->len = 0;
  s->ptr = malloc(s->len + 1);
  if (s->ptr == NULL)
  {
    fprintf(stderr, "malloc() failed\n");
    exit(EXIT_FAILURE);
  }
  s->ptr[0] = '\0';
}

size_t write_callback(void *ptr, size_t size, size_t nmemb, struct string *s)
{ 
  printf("Callback is called\n");
  size_t new_len = s->len + size * nmemb;
  s->ptr = realloc(s->ptr, new_len + 1);
  if (s->ptr == NULL)
  {
    fprintf(stderr, "realloc() failed\n");
    exit(EXIT_FAILURE);
  }
  memcpy(s->ptr + s->len, ptr, size * nmemb);
  s->ptr[new_len] = '\0';
  s->len = new_len;
  return size * nmemb;
}

char* call_destination_service(char *ifsc)
{
  CURL *curl;
  CURLcode res;

  curl = curl_easy_init();
  char URL[STRING_SIZE];
  sprintf(URL, "https://ifsc.razorpay.com/%s", ifsc);
  struct string s;
  init_string(&s);
  /* Checks if curl is initialised properly and 
   * performs required operations */

  if (curl)
  {
    printf("Contacting destination service ifsc.razorpay\n");
    curl_easy_setopt(curl, CURLOPT_URL, URL);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
    /* Verbose is to check what happens within curl */
    //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    res = curl_easy_perform(curl);

    if (res != CURLE_OK)
    {
      fprintf(stderr, "Connection failed.");
      exit(0);
    }

    /* always cleanup */
    curl_easy_cleanup(curl);
  }
  curl_global_cleanup();

  return s.ptr;
}

/*int main()
{
  char *s = call_destination_service("IDIB000N068");
  printf("%s", s);
  return 0;
}*/