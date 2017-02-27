#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mymalloc1.h"

// Size of memory
#define MEMORYBLOCKSIZE 5000

#define Freed 1
#define notFreed 0

// Static array of chars to simulate memory
static char memoryBlock[MEMORYBLOCKSIZE];

// Linked list structure to traverse through memory
typedef struct node
{
  struct node * next;
  int freedBoolean; // Freed: 1, not Freed: 0
  size_t size;
} node;

// Assign memory for linked list node(s)
node * linkedList = (void *) memoryBlock;

//  Initialize node parameters in linked list to appropriate size, free status, and next pointer to null 
void initializeLinkedList()
{
  linkedList -> size = MEMORYBLOCKSIZE - sizeof(node);
  linkedList -> freedBoolean = 1;
  linkedList -> next = NULL;
}

// Pass in giveMeThisSize to malloc and return malloced
void * mymalloc(size_t giveMeThisSize)
{
  node *prev, *curr;
  void * malloced;
  // Initialize linked list if not done so already
  if(!(linkedList -> size))
  {
    initializeLinkedList;
  }
  // Get start of linked list
  curr = linkedList;
  // Iterate through linked list if memory permits
  while((curr -> size) < giveMeThisSize)
  {
    prev = curr;
    curr = curr -> next;
  }
  // Check for when there is adequate memory and return malloced
  if((curr -> size) >= (giveMeThisSize + sizeof(node)))
  {
    node * temporaryNode = (void*)((char*)curr + giveMeThisSize + sizeof(node));
    temporaryNode -> size = ((curr -> size) - giveMeThisSize)-sizeof(node);
    temporaryNode -> freedBoolean = 1;
    temporaryNode -> next = curr -> next;
    // Set size, free status, and pointer to next node in current node
    curr -> size = giveMeThisSize;
    curr -> freedBoolean = 0;
    curr -> next = temporaryNode;
    // Get pointer to next available node
    malloced = (void*)(++curr);
  } else                // Check for insufficient amount of memory 
  {
    malloced = NULL;
    printf("Error: No memory left to allocate:\n File_Name: %s\n Line_Number: %d\n", __FILE__, __LINE__);
  }
  return malloced;
}

// Pass in ptr to be freed, pass error message when inappropriately freeing memory
void myfree(void* freeThisPointer)
{
  if(((void*)memoryBlock <= freeThisPointer) && ((void*)(memoryBlock+MEMORYBLOCKSIZE) >= freeThisPointer))
  {
    node * curr = freeThisPointer;
    --curr;
    if(curr -> freedBoolean == 1) {
      printf("Error: Repetitive free:\n File_Name: %s\n Line_Number: %d\n", __FILE__, __LINE__);
      return;
    }
    curr -> freedBoolean = 1;

    node *prev, *curr;
    curr = linkedList;
    while(curr && curr -> next)
    {
      if(curr -> freedBoolean) && (curr -> next -> freedBoolean)
      {
        curr -> size += (curr -> next -> size) + sizeof(node);
        curr -> next = curr -> next -> next;
      }
      prev = curr;
      curr = curr -> next;
    }
  } else 
  {
    printf("Error: Invalid pointer:\n File_Name: %s\n Line_Number: %d\n", __FILE__, __LINE__);
  }
}