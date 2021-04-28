#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curl/curl.h>

void syllableResponse(char *response, size_t size, size_t nmemb, void *stream)
{
  if (strstr(response, "count"))
  {
    char *p1, *p2;
    p1 = strstr(response, "count\":");
    if (p1)
    {
      p2 = strstr(p1, ",");
      if (p2)
        printf("%.*s", p2 - p1 - 7, p1 + 7);
    }
  }
  else if (strstr(response, "syllables\":{}"))
  {
    printf("%s", response);
  }
}

void getSyllables(char *word)
{
  CURL *curl;
  char apiURL[200] = "https://wordsapiv1.p.rapidapi.com/words/";
  strcat(apiURL, word);
  strcat(apiURL, "/syllables");

  curl = curl_easy_init();
  if (curl)
  {
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
    curl_easy_setopt(curl, CURLOPT_URL, apiURL);
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "x-rapidapi-key: c6ccdbfbbbmshe7408fbb59b5b09p1c4661jsn1ef62d57e9b0");
    headers = curl_slist_append(headers, "x-rapidapi-host: wordsapiv1.p.rapidapi.com");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, syllableResponse);
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
  }
}