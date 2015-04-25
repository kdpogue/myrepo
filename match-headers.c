/******************************************************************************
 * match-headers.c
 * Written By: Kevin Pogue
 * Created: 4/13/15
 * Counts and prints the http headers found in the file passed as the first 
 * (and only) argument.
 * 
 * Ordering the strings in Headers[] with the most common headers first would
 * significantly increase performance as processing is terminated once a match
 * is found.  I am not familiar enough with http to make this decision, the 
 * headers listed were found via a quick google search.
 * 
 * Performance could also be increased if it is certain that the ':' will be
 * present in every line of the input file by checking for the ':' and not the
 * null in the match() function, as well as not checking for the ':' and
 * inserting the null in main  
******************************************************************************/

#include <stdio.h>

/******************************************************************************
  Function Prototypes
******************************************************************************/
void match(char *input, char *matchstrs[], int Counts[]);

/******************************************************************************
  Global Constants
******************************************************************************/
// Increment NUMHEADERS for each additional header to be counted
#define NUMHEADERS 15
#define BUFFSIZE 256
#define TRUE 1
#define FALSE 0

/******************************************************************************
  main
******************************************************************************/
int main (int  argc, char *argv[]) {
  // Add additional headers to be counted here and increment NUMHEADERS
  char *Headers[]=
    {
      "Cache-Control", "Content-Type", "Content-Disposiion",
      "User-Agent", "Accept", "Etag", 
      "Accept-Language", "Accept-Encoding", "If-Modified-Since",
      "Cookie", "Referer", "Connection",
      "Last-Modified", "Authorization", "Content-Length"
    };
  int MatchCounts[NUMHEADERS]; // Stores the count for each header
  char FileBuff[BUFFSIZE]; // Input from the file
  char *CurrentChar;
  FILE * File;
  int i;
  
  if (argc != 2) {
    printf("usage: %s filename", argv[0]);
  }
  else {
    File = fopen( argv[1], "r");
    
    if (File == 0) {
      printf("Error, could not open file %s", argv[1]);
    } else {
      // Initialize MatchCounts
      for (i = 0; i < NUMHEADERS; i++) MatchCounts[i] = 0;
      while (fgets(FileBuff, BUFFSIZE, File)) { // Read each line of the file
	CurrentChar = FileBuff;
	while(*CurrentChar != ':' && *CurrentChar) CurrentChar++;
	if (*CurrentChar) { // We didn't get a null, found the ':'
	  *CurrentChar = 0;
	  match(FileBuff, Headers, MatchCounts);
	}
      }
    }
    close(File);
    for (i = 0; i < NUMHEADERS; i++) {
      printf("%s count: %i\n", Headers[i], MatchCounts[i]);
    }
  } 
}

/******************************************************************************
  Function Definitions
******************************************************************************/
/*
 * Pre: input: A pointer to null terminated string to be matched
 *	strgs[]: A pointer to an array of strings to match input against
 *	counts[]: A pointer to an array of ints which stores the match count 
 * Post: The array pointed to by counts[] is incremented appropriately if
 *	 a match is found	
 */

void match(char *input, char *strgs[], int counts[]) {
  unsigned int i;
  unsigned int j = 0;
  char stop_processing = FALSE;
  char input_found = FALSE;

  for (i = 0; i < NUMHEADERS && !input_found; i++) {
    while (!stop_processing) {
      if (input[j] == 0 && strgs[i][j] == 0) {
	//Reached end of string, found a match
	counts[i]++;
	stop_processing = TRUE;
	input_found = TRUE;
      } else if (input[j] == strgs[i][j]) {
	j++; // Good so far, check next char
      } else {
	stop_processing = TRUE;
      }
    }
    stop_processing = FALSE;
    j = 0;
  }
}
