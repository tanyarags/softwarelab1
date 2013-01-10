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

void openFile(string name, int thread_number);
void createFile(string name, int thread_number);
void writeToFile(int data, int file_number);



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
	openFile(file_name, tid);

	while (fscanf(file[tid], "%d\n", &n[i]) == 1)
	    {
		cout<<n[i];
		i++;
	    }

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

	createFile(file_name, tid);
	rewind(file[tid]);
	for (int i = 0; i < NUMBER_NUMBER; i++) {
			writeToFile(n[i], tid);
		}



	pthread_exit(NULL);
}



void *WriteFileThread(void *threadid) {
	int tid;
	tid = (int) threadid;
	cout << "Started thread" << tid << endl;
	string file_name;
	stringstream out;
	out << tid;
	file_name = out.str();
	file_name = file_name + "_file";
	file[thread_number] = fopen(file_name.c_str(), "r");
	rewind(file[tid]);
	for (int i = 0; i < NUMBER_NUMBER; i++) {
		int number = rand() % 100;
		writeToFile(number, tid);
	}
	pthread_exit(NULL);
}


int main (int argc, char *argv[])
{
   pthread_t threads[NUM_THREADS];
   int rc;
   int sort;
   long t;
   for(t=0; t<NUM_THREADS; t++){
      //printf("In main: creating thread %ld\n", t);
      rc = pthread_create(&threads[t], NULL, WriteFileThread, (void *)t);
      if (rc){
         //printf("ERROR; return code from pthread_create() is %d\n", rc);
         exit(-1);
      }
   }
   for(t=0; t<NUM_THREADS; t++){
	   pthread_join(threads[t], NULL);
   }


   cout<< "Here";
   for(t=0; t<NUM_THREADS; t++){
         //printf("In main: creating thread %ld\n", t);
         sort = pthread_create(&threads[t], NULL, SortInFile, (void *)t);
         if (sort){
            //printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
         }
      }
      for(t=0; t<NUM_THREADS; t++){
   	   pthread_join(threads[t], NULL);
      }


   /* Last thing that main() should do */
   pthread_exit(NULL);
}





void createFile(string name, int thread_number) {
	file[thread_number] = fopen(name.c_str(), "w");
}

void openFile(string name, int thread_number) {
	file[thread_number] = fopen(name.c_str(), "r");
}

void writeToFile(int data, int file_number) {
	fprintf(file[file_number], "%d%s", data, "\n");
}










