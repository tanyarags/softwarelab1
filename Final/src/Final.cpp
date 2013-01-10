//============================================================================
// Name        : Final.cpp
// Author      : tanya raghuvanshi
// Version     :
// Copyright   : Your copyright notice
// Description : Pthread in C++, Ansi-style
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

void *WriteFileThread(void *threadid) {
	int tid;
	tid = (int) threadid;
	cout << "Started thread" << tid << endl;
	string file_name;
	stringstream out;
	out << tid;
	file_name = out.str();
	file_name = file_name + "_file";
	createFile(file_name, tid);
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
