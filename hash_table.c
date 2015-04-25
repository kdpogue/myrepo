/******************************************************************************
	Generated during "techincal phone interview" for entry level position
	Asked to implement insert() and lookup() in C from function prototypes
	
	Told to use a global variable for the hash table

	Added this comment at the top, otherwise this is what I came up with 
	in the interview
******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
typedef struct hash_string {
    char * key;
    char * val;
    struct hash_string * next;
} hash_string;

unsigned int hash(char * s);

hash_string * hashtable[100];

void insert(char * key, char * val)
{
    unsigned int hashval = hash(key) % 100;
    hash_string * temp = (hash_string *) malloc(sizeof(hash_string));
    temp->key = key;
    temp->val = val;
    temp->next = 0;
    if (hashtable[hashval] != 0) { // Collision
        temp->next = hashtable[hashval];
        hashtable[hashval] = temp;        
    } else { // Empty Slot, insert into table
        hashtable[hashval] = temp;
    }
}

char * lookup(char * key)
{
    hash_string * temp = (hash_string *) malloc(sizeof(hash_string));
    unsigned int hashval = hash(key) % 100;
    temp = hashtable[hashval];
    if (temp != 0) { // Match
       while (strcmp(temp->key, key) != 0 && temp->next != 0 ) { 
           temp = temp->next;
       } 
       if (strcmp(temp->key, key) == 0) { //Found a match
           return temp->val;
       } else { // Not in table
           return 0;
       }
    } else { // Not in table
        return 0;
    }
}

unsigned int hash(char * s){
  return (*s & 0xff);
}

int main (int argc, char * argv[]) {
  insert("1", "abcd");
  insert("2", "defg" );
  printf("lookup 2: %s\n", lookup("2"));
  printf("lookup 1: %s\n", lookup("1"));
  insert("1", "hijk");
  insert("2", "lmnop");

  printf("lookup 2: %s\n", lookup("2"));
  printf("lookup 1: %s\n", lookup("1"));
}
