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
int Isearch, Ifound;
FILE *file[FILE_NUMBER];



void *SortInFile(void *threadid) {
	int n[200];
    int i=0;
	int tid;
	tid = (int) threadid;
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

	file[tid] = fopen(file_name.c_str(), "w");
	for(int i=0;i<200;i++)
	fprintf(file[tid], "%d%s", n[i], "\n");
	fclose(file[tid]);


	pthread_exit(NULL);
} //SortinFile ends here


void *SearchInFile(void *threadid) {
	int n[200];
    int i=0;
	int tid;
	tid = (int) threadid;
	string file_name;
	stringstream out;
	out << tid;
	file_name = out.str();
	file_name = file_name + "_file";
	file[tid] = fopen(file_name.c_str(), "r");


	while (fscanf(file[tid], "%d\n", &n[i]) == 1)
	{
	if(n[i]==Isearch)
     	{
	 	Ifound=1;
	  	break;
	    }
		i++;
	  }
      cout<<"Your Number was First Found in "<<tid<< "File\n";
		fclose(file[tid]);


	pthread_exit(NULL);
} //SortinFile ends here


int main (int argc, char *argv[])
{
   pthread_t threads[NUM_THREADS];
   int sort,search;
   long t;
   int Ichoice;
   cout<<"Please Enter Your Choice:\n";
   cout<<"1. SORT\n2. SEARCH\n";
   cin>>Ichoice;

   if(Ichoice==1)
   {
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
      cout<<"Sorting Done";
      }

   else if(Ichoice==2)
   {
    cout<< "Please Enter The Number You Want to Search\n";
    cin>>Isearch;
     Ifound=0;
    for(t=0; t<NUM_THREADS; t++)
          {
          search = pthread_create(&threads[t], NULL, SearchInFile, (void *)t);
           if(Ifound==1)
           break;
           if(search)
           exit(-1);
          }

    if(Ifound == 0)
    cout<<"Sorry, Could Not Find Your Number\n";


   }

   else
    cout<<"Wrong Choice Entered: Exiting";
   /* Last thing that main() should do */
   pthread_exit(NULL);

}















