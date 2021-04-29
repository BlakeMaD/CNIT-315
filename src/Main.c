#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "syllables.c" 
#include "synonyms.c"

#define INPUTSIZE 120

/*Important notes:
use of the api requires a subscription to the WordsAPI page. https://rapidapi.com/dpventures/api/wordsapi/endpoints
The api key listed below is the personal api key of Blake Dukes, charges are incurred after 2500 api calls in a given day. 
Please do not misuse the api in a way that would incurr charges to the account. Be extremely careful with looping etc.
*/

int main()
{
  /*define variables for user input*/
  char menu_option[INPUTSIZE];
  char haikuLine[INPUTSIZE];

  void verifyLine(char *haikuLine, int syllablesNeeded);
  void findSynonyms(char *haikuLine);

  do
  {
    /*print out the main menu, taking in user input to select a function*/
    printf("\n-------Main Menu-------\n");
    printf("0: Haiku Verification\n");
    printf("1: Alternative Words\n");
    printf("2: Couplet Verification\n");
    printf("e: Exit Program\n");
    printf("\nPlease enter an option from the main menu: ");
    scanf(" %s", menu_option);

    switch (menu_option[0])
    {
    case '0':
      printf("\nEnter the first line (5 syllables):");
      scanf(" %[^\n]", haikuLine);
      printf("\n---------------Line 1: Syllable Counts-----------------");
      verifyLine(haikuLine, 5);

      printf("\nEnter the second line (7 syllables):");
      scanf(" %[^\n]", haikuLine);
      printf("\n---------------Line 2: Syllable Counts-----------------\n");
      verifyLine(haikuLine, 7);

      printf("\nEnter the third line (5 syllables):");
      scanf(" %[^\n]", haikuLine);
      printf("\n--------------Line 3: Syllable Counts------------------");
      verifyLine(haikuLine, 5);
      break;
    case '1':
      printf("\nEnter a word to see its synonyms and their syllable count:");
      scanf(" %s", haikuLine);
      findSynonyms(haikuLine);
      break;
    case '2':
      break;
    case 'e':
      /*stop program execution*/
      break;
    default:
      /*handle invalid menu choices*/
      printf("invalid input");
      break;
    }

  } while (menu_option[0] != 'e');

  curl_global_cleanup();

  return 0;
}

void verifyLine(char *haikuLine, int syllablesNeeded)
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

  /*display the words in the line and their syllables*/
  Traverse();

  /*gather counts and determine if final line is valid*/
  printf("\n----------------------Results--------------------------\n");
  int finalTotal = syllableCount(syllablesNeeded);
  if (finalTotal == syllablesNeeded && validLine)
    printf("Success! Valid line\n");
  else if (finalTotal != syllablesNeeded && validLine)
    printf("Invalid Line\n%d syllables were needed, but %d were found\n", syllablesNeeded, finalTotal);
  else
  {
    /*tell the user if there was an invalid word in their input, and reset validLine for next line input*/
    printf("Invalid Line. An invalid word was found in the line\nPlease assure correct spelling and try again\n");
    validLine = true;
  }

  /*remove current list of words from struct*/
  struct wordsAndSyllables *temp;

  while (listStart != NULL)
  {
    temp = listStart;
    listStart = listStart->nextWord;
    free(temp);
  }
}

void findSynonyms(char *haikuLine)
{
  getSynonyms(haikuLine);

  Traverse();

  /*remove current list of words from struct*/
  struct wordsAndSyllables *temp;

  while (listStart != NULL)
  {
    temp = listStart;
    listStart = listStart->nextWord;
    free(temp);
  }
}