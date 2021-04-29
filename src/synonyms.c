#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curl/curl.h> /* has to be installed with "sudo apt-get install libcurl4-openssl-dev" */
#include <stdbool.h>

void synonymResponse(char *response, size_t size, size_t nmemb, void *stream)
{
    char *start;
    if (strstr(response, "\":[\""))
    {
        int count = 0;

        start = strstr(response, "\":[");
        start += strlen("\":[");

        // Extract the first token
        start[strlen(start) - 1] = '\0';
        char *token = strtok(start, "\"");
        // loop through the string to extract all other tokens
        while (token != NULL)
        {
            if (count % 2 == 0)
                getSyllables(token); //printing each token
            token = strtok(NULL, "\"");
            count++;
        }
    }
    else if (strstr(response, "\":[]"))
    {
        printf("Synonyms could not be found\n");
    }
    else if (strstr(response,"success\":false"))
    {
        printf("\nYour word appears to be invalid");
    }
}

void getSynonyms(char *word)
{

    CURL *curl;
    int syllableCount;
    char apiURL[200] = "https://wordsapiv1.p.rapidapi.com/words/";
    strcat(apiURL, word);
    strcat(apiURL, "/synonyms");

    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
        curl_easy_setopt(curl, CURLOPT_URL, apiURL);
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "x-rapidapi-key: c6ccdbfbbbmshe7408fbb59b5b09p1c4661jsn1ef62d57e9b0");
        headers = curl_slist_append(headers, "x-rapidapi-host: wordsapiv1.p.rapidapi.com");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, synonymResponse);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
}