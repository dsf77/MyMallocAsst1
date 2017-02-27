#ifndef MYMALLOC_H
#define MYMALLOC_H

#include <stdio.h>
#include <stddef.h>

void initialize();
void * mymalloc(size_t giveMeThisSize);
void myfree(void * freeThisPointer);

#endif