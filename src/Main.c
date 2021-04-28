#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curl/curl.h> /* has to be installed with "sudo apt-get install libcurl4-openssl-dev" */
#define INPUTSIZE 120

/*Important notes:
use of the api requires a subscription to the WordsAPI page. https://rapidapi.com/dpventures/api/wordsapi/endpoints
The api key listed below is the personal api key of Blake Dukes, charges are incurred after 2500 api calls in a given day. 
Please do not misuse the api in a way that would incurr charges to the account. Be extremely careful with looping etc.
*/

int main()
{
  /*define variables for user input*/
  char menu_option;
  char haikuLine[INPUTSIZE];

  void getSyllables(char *word);
  void verifyLine(char *haikuLine);
  do
  {
    /*print out the main menu, taking in user input to select a function*/
    printf("Main Menu\n");
    printf("0: Haiku Verification\n");
    printf("1: Couplet Verification\n");
    printf("e: Exit Program\n");
    printf(" Please enter an option from the main menu: ");
    scanf(" %c", &menu_option);

    switch (menu_option)
    {
    case '0':
      printf("Enter the first line (5 syllables):\n");
      scanf(" %[^\n]", haikuLine);
      verifyLine(haikuLine);
      break;
    case '1':
      break;
    case 'e':
      /*stop program execution*/
      break;
    default:
      /*handle invalid menu choices*/
      printf("invalid input");
      break;
    }

  } while (menu_option != 'e');

  curl_global_cleanup();

  return 0;
}

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

void verifyLine(char *haikuLine)
{
  char str1[INPUTSIZE];
  strcpy(str1, haikuLine);
  char newString[30][30];
  int i, letter, word;

  letter = 0;
  word = 0;
  for (i = 0; i <= (strlen(str1)); i++)
  {
    // if space or NULL found, assign NULL into newString[word]
    if (str1[i] == ' ' || str1[i] == '\0')
    {
      newString[word][letter] = '\0';
      word++;     //for next word
      letter = 0; //for next word, init index to 0
    }
    else
    {
      newString[word][letter] = str1[i];
      letter++;
    }
  }

  for (i = 0; i < word; i++)
    getSyllables(newString[i]);
}