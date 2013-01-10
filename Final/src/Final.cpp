//============================================================================
// Name        : Final.cpp
// Author      : tanya raghuvanshi
// Version     :
// Copyright   : Your copyright notice
// Description : Pthreadmain in C++, Ansi-style
//============================================================================


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstdio>
#include <string.h>
#include <string>
#include <sstream>
using namespace std;

#define NUM_THREADS     15
#define FILE_NUMBER		15
#define NUMBER_NUMBER	200

int thread_stop = 0;

FILE *file[FILE_NUMBER];



void *SortInFile(void *threadid) {
	int n[200];
    int i=0;
	int tid;
	tid = (int) threadid;
	cout << "Sort thread" << tid << endl;
	string file_name;
	stringstream out;
	out << tid;
	file_name = out.str();
	file_name = file_name + "_file";
	file[tid] = fopen(file_name.c_str(), "r");


	while (fscanf(file[tid], "%d\n", &n[i]) == 1)
     i++;
	fclose(file[tid]);

	//cout<<"File closed";
	  int temp;

	//sorting here with simple bubble sort
	for(int k=0;k<200;k++)
	for(int j=0;j<(200-k);j++)
	if(n[j]>n[j+1])
	{
	temp=n[j];
	n[j]=n[j+1];
	n[j+1]=temp;
	}
	for(int i=0;i<200;i++)
		{
		cout<<n[i]<<"\n";
		}

	file[tid] = fopen(file_name.c_str(), "w");
	for(int i=0;i<200;i++)
	fprintf(file[tid], "%d%s", n[i], "\n");
	fclose(file[tid]);


	pthread_exit(NULL);
}





int main (int argc, char *argv[])
{
   pthread_t threads[NUM_THREADS];
   int sort;
   long t;
   cout<< "Here";

   // here the sorting starts
   for(t=0; t<NUM_THREADS; t++)
         {
         sort = pthread_create(&threads[t], NULL, SortInFile, (void *)t);
           if (sort)
           exit(-1);
          }

           for(t=0; t<NUM_THREADS; t++){
   	       pthread_join(threads[t], NULL);
         } // here the sorting ends


   /* Last thing that main() should do */
   pthread_exit(NULL);
}















