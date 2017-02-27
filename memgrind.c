#include "mymalloc.h"
#include "mymalloc.c"
#include <stdio.h>
#include <time.h>

void main()
{
 double testAtime = 0;
 double testBtime = 0;
 double testCtime = 0;
 double testDtime = 0;
 double testEtime = 0;
 double testFtime = 0;
 int index;

 clock_t startTime, endTime;
 double totalTime;


 // Detectable Errors

 // A*****************

 int x1;
 myfree(&x1);

 // B1*****************

 char *p1 = (char*)mymalloc(200 *sizeof(char));
 myfree(p1+10);

// B2******************

 int *x2;
 myfree(x2);

 // C1*****************
 char *p2 = (char*)mymalloc(100);
 myfree(p2);
 myfree(p2);

 //C2*****************
 char *p3 = (char*)mymalloc(100);
 myfree(p3);
 p3 = (char*)mymalloc(100);
 myfree(p3);
 
 //D1******************
 char *p4 = (char*)mymalloc(5001);
 
 //D2******************
 char *p5 = (char*)mymalloc(5000);
 char *q1 = (char*)mymalloc(1);

 // EXTRA TESTING******************************
 int randomNum;
 int randomNumBytes = 0;
 int numOfMallocs = 0;
 int numOfFrees = 0;
 int freedIndex = 0;
 
 int execute100 = 0;

 // MIGHT BE BETTER TO SEPARATE TEST A, TEST B...TEST F INTO function calls instead of hardcode
 for(execute100 = 0; execute100 < 100; execute100++)
 {	
  // Test A*************************************************8
 
  char *ptrArray1[1000]; // MAY HAVE TO DRAG THESE ARRAY DECL OUT OF LOOP
 
  totalTime = 0;
 
  startTime = clock();
 
  for(index = 0; index < 1000; index++)
  {
   ptrArray1[index] = (char*)mymalloc(sizeof(char));
  }

  for(index = 0; index < 1000; index++)
  {
   myfree(ptrArray1[index]);
  }
  
  endTime = clock();
  totalTime = ((double)(endTime - startTime))/CLOCKS_PER_SEC;

  testAtime += totalTime;
 
  // TEST B**********************************************************88
 
  totalTime = 0;

  startTime = clock();
  for(index = 0; index < 1000; index++)
  {  
   	char* ptr = (char*)mymalloc(sizeof(char));
    myfree(ptr);
  }
   endTime = clock();
   totalTime = ((double)(endTime - startTime))/CLOCKS_PER_SEC;
   testBtime += totalTime;
 

  // Test C********************************************************

  totalTime = 0;

 
  char *ptrArray2[1000];
 
  startTime = clock();
 
  while(numOfMallocs < 1000)
  {
   randomNum = (rand() % 2);

   if((randomNum == 0) && (numOfMallocs < 1000))
   {
    ptrArray2[numOfMallocs] = (char*)mymalloc(sizeof(char));
    numOfMallocs++;
   }

   if(randomNum == 1)
   {
   	if(numOfMallocs > numOfFrees)
   	{
  	 myfree(ptrArray2[freedIndex]);
     freedIndex++;
  	}
   }
  }
   endTime = clock();

   totalTime = ((double)(endTime - startTime))/CLOCKS_PER_SEC;
   testCtime += totalTime; 

   // TEST D*******************
  
   totalTime = 0;
   randomNum = 0;
   randomNumBytes = 0;
   numOfMallocs = 0;
   numOfFrees = 0;
   freedIndex = 0;
 
  char *ptrArray3[1000];
 
  startTime = clock();
 
  while(numOfMallocs < 1000)
  {
   randomNum = (rand() % 2);
   randomNumBytes = ((rand() % 64) + 1);

   if((randomNum == 0) && (numOfMallocs < 1000))
   {
    ptrArray3[numOfMallocs] = (char*)mymalloc(randomNumBytes * sizeof(char));
    numOfMallocs++;
   }

   if(randomNum == 1)
   {
   	if(numOfMallocs > numOfFrees)
  	{
  	 myfree(ptrArray3[freedIndex]);
     freedIndex++;
  	}
   }
  }
   endTime = clock();

   totalTime = ((double)(endTime - startTime))/CLOCKS_PER_SEC;
   testDtime += totalTime; 

  // Test E*******************************
  totalTime = 0;

  startTime = clock();

  // Fill Up memory
  for(index = 0; index < 999; index++)
  {  
   	char* ptr = (char*)mymalloc(sizeof(char));
  }
  
  // Rotate Mallocing & freeing right on the edge of memory overflow
  for(index = 0; index < 1000; index++)
  { 
    char* ptr = (char*)mymalloc(sizeof(char));
  	myfree(ptr); 
  }
   endTime = clock();
   totalTime = ((double)(endTime - startTime))/CLOCKS_PER_SEC;
   testEtime += totalTime;
 
 
 // Test F*******************************
  totalTime = 0;
  randomNumBytes = 0;
  
  startTime = clock();

  // Fill up the majority of memory
  for(index = 0; index < 900; index++)
  {  
   	char* ptr = (char*)mymalloc(sizeof(char));
  }
  
  // Rotate Mallocing & freeing right on the edge of memory overflow with a random number of bytes
  for(index = 0; index < 1000; index++)
  { 
    char* ptr = (char*)mymalloc(randomNumBytes * sizeof(char));
    myfree(ptr);
    randomNumBytes = ((rand() % 256) + 1); 
  }
   endTime = clock();
   totalTime = ((double)(endTime - startTime))/CLOCKS_PER_SEC;
   testFtime += totalTime;
 
  }


  testAtime = testAtime/100;
  testBtime = testBtime/100;
  testCtime = testCtime/100;
  testDtime = testDtime/100;
  testEtime = testEtime/100;
  testFtime = testFtime/100;

  printf("Average Time For test A: %d\n",testAtime);
  printf("Average Time For test B: %d\n",testBtime);
  printf("Average Time For test C: %d\n",testCtime);
  printf("Average Time For test D: %d\n",testDtime);
  printf("Average Time For test E: %d\n",testEtime);
  printf("Average Time For test F: %d\n",testFtime);  
 
}




   





