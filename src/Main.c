#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "syllables.c"
#include "synonyms.c"
#include "rhyming.c"

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
  char coupletLineOne[INPUTSIZE];
  char coupletLineTwo[INPUTSIZE];

  void verifyHaiku(char *haikuLine, int syllablesNeeded);
  void findSynonyms(char *haikuLine);
  void aboutDetails();
  void verifyCouplet(char *lineOne, char *lineTwo);

  do
  {
    /*print out the main menu, taking in user input to select a function*/
    printf("\n-------Main Menu-------\n");
    printf("0: Haiku Verification\n");
    printf("1: Alternative Words\n");
    printf("2: Couplet Verification\n");
    printf("3: About Info\n");
    printf("e: Exit Program\n");
    printf("\nPlease enter an option from the main menu: ");
    scanf(" %s", menu_option);

    switch (menu_option[0])
    {
    case '0':
      printf("\n*Note:\n\tThe amount of words accepted is the same as syllables needed, as a word contains at least one syllable");
      printf("\n\nEnter the first line (5 syllables):");
      scanf(" %[^\n]", haikuLine);
      printf("\n---------------Line 1: Syllable Counts-----------------");
      verifyHaiku(haikuLine, 5);

      printf("\nEnter the second line (7 syllables):");
      scanf(" %[^\n]", haikuLine);
      printf("\n---------------Line 2: Syllable Counts-----------------\n");
      verifyHaiku(haikuLine, 7);

      printf("\nEnter the third line (5 syllables):");
      scanf(" %[^\n]", haikuLine);
      printf("\n--------------Line 3: Syllable Counts------------------");
      verifyHaiku(haikuLine, 5);
      break;
    case '1':
      printf("\nEnter a word to see its synonyms and their syllable count:");
      scanf(" %s", haikuLine);
      findSynonyms(haikuLine);
      break;
    case '2':
      printf("\nReminder: The last word of the line must rhyme.\nFor a proper result, do not include punctuation at the end of the line\n");
      printf("\nEnter your first line:");
      scanf(" %[^\n]", coupletLineOne);

      printf("\nEnter your second line:");
      scanf(" %[^\n]", coupletLineTwo);

      verifyCouplet(coupletLineOne, coupletLineTwo);
      break;
    case '3':
      aboutDetails();
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

void verifyHaiku(char *haikuLine, int syllablesNeeded)
{
  char str1[INPUTSIZE];
  strcpy(str1, haikuLine);
  char newString[9][30];
  int i, letter, word, wordCount;

  letter = 0;
  word = 0;
  for (i = 0; i <= (strlen(str1)) && word < syllablesNeeded; i++)
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
    printf("Invalid Line:\n\t%d syllables were needed, but %d were found\n", syllablesNeeded, finalTotal);
  else
  {
    /*tell the user if there was an invalid word in their input, and reset validLine for next line input*/
    printf("Invalid Line:\n\tAn invalid word was found in the line.\n\tPlease assure correct spelling and try again\n");
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
  printf("\n");
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

void verifyCouplet(char *lineOne, char *lineTwo)
{

  char *lineOneWord;
  char *lineTwoWord;

  if (strrchr(lineOne, ' ') != NULL)
  {
    lineOneWord = strrchr(lineOne, ' ');
  }
  else{
    lineOneWord = lineOne;
  }
  if (lineOneWord && *(lineOneWord + 1))
    lineOneWord += 1;

  if (strrchr(lineTwo, ' ') != NULL)
  {
    lineTwoWord = strrchr(lineTwo, ' ');
  }
  else{
    lineTwoWord = lineTwo;
  }
  if (lineTwoWord && *(lineTwoWord + 1))
    lineTwoWord += 1;
  
  secondWord = lineTwoWord;

  getRhymingWords(lineOneWord);
}
void aboutDetails()
{
  printf("\n\t---------------Option 0: Verify Haiku-----------------");
  printf("\nA Haiku is a three line poem, where the syllables in each line are 5-7-5 respectively\n");

  printf("\n\t---------------Option 1: Alternative Words-----------------");
  printf("\n    Enter a word to find a list of synonyms, while also showing their syllable count\n");
  printf("this is especially useful for finding words with similar meanings to replace words in the haiku.\n");

  printf("\n\t---------------Option 2: Couplets-----------------");
  printf("\nA couplet, in its simplest form, is a two line poem whose ending words rhyme\n");

  printf("\n\t---------------Warnings:-----------------");
  printf("\n    Some words from the external api, WordsAPI, return an empty body for syllable count.\n");
  printf("Since these are often short words like \"is\" or \"I\" the program assumes a word with an empty body is 1 syllable long.\n");
  printf("This assumption is not always correct, so it reccomended to follow your better judgements\n");
}