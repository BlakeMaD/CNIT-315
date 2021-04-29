#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curl/curl.h> /* has to be installed with "sudo apt-get install libcurl4-openssl-dev" */
#include <stdbool.h>

int currentWordSyllableCount;
bool validWord = true;
bool validLine = true;
bool uncertain = false;

struct wordsAndSyllables
{
    char word[30];
    int syllableCount;
    struct wordsAndSyllables *nextWord;
};

struct wordsAndSyllables *listStart = NULL;

void InsertEnd(char word[30], int syllableCount)
{
    struct wordsAndSyllables *temp, *last = listStart;

    /*request space for one structure */
    temp = (struct wordsAndSyllables *)malloc(sizeof(struct wordsAndSyllables)); /* check that space was allocated */
    if (temp == (struct wordsAndSyllables *)NULL)
    {
        printf("\nAllocation failed\n");
        exit(1);
    }

    /*make listStart point to the new wordsAndSyllables if the list is empty*/
    if (listStart == NULL)
    {
        listStart = temp;
    }

    /*travel to the end of the list and make the last entry point to the new wordsAndSyllables*/
    else
    {
        while (last->nextWord != NULL)
        {
            last = last->nextWord;
        };

        last->nextWord = temp;
    }
    /*make new wordsAndSyllables point to null and copy user input into the wordsAndSyllables*/
    temp->nextWord = NULL;
    /*copy user input into new wordsAndSyllables*/
    strcpy(temp->word, word);
    temp->syllableCount = syllableCount;
}

void Traverse()
{
    struct wordsAndSyllables *current = listStart;

    while (current != NULL)
    {
        printf("\nWord: %-30s Syllables: %d", current->word, current->syllableCount);

        current = current->nextWord;
    }
    printf("\n");
}

void syllableResponse(char *response, size_t size, size_t nmemb, void *stream)
{
    int count;
    if (strstr(response, "count"))
    {
        char *target = NULL;
        char *start, *end;

        start = strstr(response, "count\":");

        start += strlen("count\":");
        end = strstr(start, ",");
        target = (char *)malloc(end - start + 1);
        memcpy(target, start, end - start);
        target[end - start] = '\0';

        count = atoi(target);
        free(target);
    }
    else if (strstr(response, "syllables\":{}"))
    {
        uncertain = true;
        count = 1;
    }
    else if (strstr(response,"success\":false"))
    {
        validWord = false;
        validLine = false;
    }
    currentWordSyllableCount = count;
}

void getSyllables(char *word)
{
    CURL *curl;
    int syllableCount;
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

        /*store syllable count and word in linked list if it's valid*/
        if(validWord) InsertEnd(word, currentWordSyllableCount);
        else printf("\n*WARNING!! ----> \"%s\" is an invalid word", word);

        if(uncertain) printf("\n*WARNING!! ----> \"%s\" is valid but syllables unknown, 1 syllable assumed", word);

        /*reset flags for syllable certainty and word validity*/
        validWord = true;
        uncertain = false;
    }
}

int syllableCount(int syllablesNeeded){
    struct wordsAndSyllables *current = listStart;
    int totalSyllables = 0;

    while (current != NULL)
    {
        totalSyllables += current->syllableCount;
        current = current->nextWord;
    }

    /*if we have the correct amount of syllables in the line, we determine the line is valid*/
    if (validLine) return totalSyllables;

    return -1;
}