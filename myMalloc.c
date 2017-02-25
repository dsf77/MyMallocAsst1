// NOTE: This will be a .h file & the test cases will be "main.c" arbitrarily calling this .h file



#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

// Size of memory
#define MEMORYBLOCKSIZE 5000 

#define Freed 1
#define notFreed 0

// Static array of chars to simulate memory
static char myblock[MEMORYBLOCKSIZE]; 

// Linked list structure to traverse through memory
struct MetaData 
{
	struct MetaData *prev, *next; 
	int freed; // Freed: 1, not Freed: 0
	int size; 
};

// Pass in sizeOf to malloc, The file using this method, and the line number referencing it
void * myMalloc(int sizeOf, char * fileNameofError, int lineNumErr)
{
 int blnFirstMalloc = 0;
 struct MetaData * headOfMemory;
 struct MetaData * metaPtr;

 if(sizeof == 0)
 {
  printf("Error: Tried to allocate 0 bytes:\n File_Name: %s\n Line_Number: %s\n",fileNameofError, lineNumErr);
 }

 if(blnFirstMalloc == 0)
 {
  headOfMemory = (struct MetaData*) myblock;                     // initialize head to point to front of "myBlock"
  headOfMemory->next = 0;                                        // initialize next to 0
  headOfMemory->prev = 0;                                        // initialize prev to 0
  headOfMemory->size = MEMORYBLOCKSIZE - sizeOf(struct MetaData);// Keep track of size to check for overflow
  headOfMemory->freed = notFreed;                                // Set that the memory is no longer free
  blnFirstMalloc = 1;                                            // Set that the memory space has been linked with MetaData
 }

 /*
  DO CENTRAL
  ALGORITHM HERE
  FOR MALLOC
 */
}

// Pass in ptr to be freed, The file calling this method, the line number referencing it, return 0 or 1 if it freed successfully or not
int myFree(void* freeThisPtr, char * fileNameofError, int lineNumErr)
{

}

 

 