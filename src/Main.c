#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curl/curl.h> /* has to be installed with "sudo apt-get install libcurl4-openssl-dev" */


/*Important notes:
use of the api requires a subscription to the WordsAPI page. https://rapidapi.com/dpventures/api/wordsapi/endpoints
The api key listed below is the personal api key of Blake Dukes, charges are incurred after 2500 api calls in a given day. 
Please do not misuse the api in a way that would incurr charges to the account. Be extremely careful with looping etc.
*/

int main()
{

  void getRequest();

  /*define variables for user input*/
  char menu_option;

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
      getRequest();
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

void getRequest()
{
  CURL *hnd = curl_easy_init();

  curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "GET");
  curl_easy_setopt(hnd, CURLOPT_URL, "https://wordsapiv1.p.rapidapi.com/words/.22-caliber/pertainsTo");

  struct curl_slist *headers = NULL;
  headers = curl_slist_append(headers, "x-rapidapi-key: c6ccdbfbbbmshe7408fbb59b5b09p1c4661jsn1ef62d57e9b0");
  headers = curl_slist_append(headers, "x-rapidapi-host: wordsapiv1.p.rapidapi.com");
  curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);

  CURLcode ret = curl_easy_perform(hnd);
}