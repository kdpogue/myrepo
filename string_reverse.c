#include <stdlib.h>
#include <stdio.h>

/*
  Pre:	A null terminated string is pointed to by argument "string"
  Post: The string is reversed in place
*/
void string_reverse1(char *string)
{
  char *current_char = string;
  char temp;
  int half_length;
  int offset = 0;
  
  while (*current_char)  current_char++; // Move to end of string
  half_length = (current_char - string)/2;
  while (offset < half_length) { 
    // Switch first and last chars until you get to the middle
    temp = *(--current_char);
    *current_char = string[offset];
    string[offset++] = temp;
  }
}

/*
  Pre:	A null terminated string is pointed to by argument "string"
  Post: A pointer to the reversed string is returned.  The memory allocated
  	for the reversed string must be returned by the calling function with
	a call to free() on the returned pointer to prevent memory leaks.
*/
char * string_reverse2(const char *string) 
{
  char *temp = (char *) string;
  char *reversed_string;
  int length;
  int offset = 0;

  while(*temp) temp++; // Move to end of string
  length = temp - string;
  reversed_string = (char *) malloc(length * sizeof(char) + 1);
  reversed_string[length] = 0; // Null terminate string
  while (offset < length) { // Copy string in reverse order
    reversed_string[offset++] = *(--temp); 
  }
  return (reversed_string);
}

/*
  main provides a few representative test cases of string_reverse1()
  and string_reverse2()
*/
void main (void) {
  char test_string1[16] = "";
  char test_string2[16] = "a";
  char test_string3[16] = "abcd";
  char test_string4[16] = "abcde";
  char * temp1;
  char * temp2;
  char * temp3;
  char * temp4;
  printf("test_string1 before being reversed: %s\n", test_string1);
  printf("test_string2 before being reversed: %s\n", test_string2);
  printf("test_string3 before being reversed: %s\n", test_string3);
  printf("test_string4 before being reversed: %s\n", test_string4);
  string_reverse1(test_string1);
  string_reverse1(test_string2);
  string_reverse1(test_string3);
  string_reverse1(test_string4);
  printf("test_string1 after being reversed: %s\n", test_string1);
  printf("test_string2 after being reversed: %s\n", test_string2);
  printf("test_string3 after being reversed: %s\n", test_string3);
  printf("test_string4 after being reversed: %s\n", test_string4);
  temp1 = string_reverse2(test_string1);
  temp2 = string_reverse2(test_string2);
  temp3 = string_reverse2(test_string3);
  temp4 = string_reverse2(test_string4);
  printf("test_string1 reversed again: %s\n", temp1);
  printf("test_string2 reversed again: %s\n", temp2);
  printf("test_string3 reversed again: %s\n", temp3);
  printf("test_string4 reversed again: %s\n", temp4);
  free(temp1);
  free(temp2);
  free(temp3);
  free(temp4);
}
