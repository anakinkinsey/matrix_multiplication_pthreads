
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "functions.h"
#include "timer.h"
#include <getopt.h>
#define BLOCK_LOW(id,p,n)  ((id)*(n)/(p))
#define BLOCK_HIGH(id,p,n) (BLOCK_LOW((id)+1,p,n)-1)

/* Global variables */
int     thread_count;
int    m, n;
double* A;
double* x;
double* y;

/* Serial functions */
void Usage(char* prog_name);
void Gen_matrix(double A[], int m, int n);
void Read_matrix(char* prompt, double A[], int m, int n);
void Gen_vector(double x[], int n);
void Read_vector(char* prompt, double x[], int n);
void Print_matrix(char* title, double A[], int m, int n);
void Print_vector(char* title, double y[], double m);

/* Parallel function */
void *Pth_mat_vect(void* rank);

/*------------------------------------------------------------------*/
int main(int argc, char* argv[]) {
   long       thread;
   pthread_t* thread_handles;
	char* a_name;
	char* x_name ;
	char* y_name;
	int parameter;
   double start, end, end_math, start_math;
	//Start time
   GET_TIME(start);
   if (argc != 9) 
   {
   	Usage(argv[0]);
   }
   else {
  		while((parameter = getopt(argc, argv, "t:A:x:y:")) != -1) {
			switch(parameter) {
				case 't':
					thread_count = strtol(optarg, NULL, 10);
					break;
				case 'A':
					a_name = optarg;
					break;
				case 'x':
					x_name = optarg;
					break;
				case 'y':
					y_name = optarg;
					break;
				case '?':
					Usage(argv[0]);
					exit(1);
			}
		}
		 	
   	
  	}
   //thread_count = strtol(argv[1], NULL, 10);
   //m = strtol(argv[2], NULL, 10);
   //n = strtol(argv[3], NULL, 10);

#  ifdef DEBUG
   //printf("thread_count =  %d, m = %d, n = %d\n", thread_count, m, n);
#  endif

   thread_handles = malloc(thread_count*sizeof(pthread_t));
   int mA, nA, mX, nX;
  
	
	read_matrix(a_name, &mA, &nA, &A);
	read_matrix(x_name, &mX, &nX, &x);
	//printf("Multiplying a %ld x %d and a ", mA, nA);
	//printf("%d x %d\n", mX, nX);
	if(nA != mX)
	{
		printf("Inner dimensions of matrix and vector must match!\n		eg. Must be 'm x n' and 'n x 1'");
		exit(0);	
	}
	else 
	{
		m = mA;
		n = nA;	
	}
   //A = malloc(m*n*sizeof(double));
   //x = malloc(n*sizeof(double));
   y = malloc(m*sizeof(double));
   
   //Gen_matrix(A, m, n);
//#  ifdef DEBUG
   //Print_matrix("We generated", A, m, n);
    
//#  endif

   //Gen_vector(x, n);
//#  ifdef DEBUG
   //Print_vector("We generated", x, n); 
//#  endif
	//print_matrix(mA, nA, A);
	//print_matrix(mX, nX, x);
	
	GET_TIME(start_math);
   for (thread = 0; thread < thread_count; thread++)
      pthread_create(&thread_handles[thread], NULL,
         Pth_mat_vect, (void*) thread);

   for (thread = 0; thread < thread_count; thread++)
      pthread_join(thread_handles[thread], NULL);
   GET_TIME(end_math);
	//print_matrix(mA, nX, y);
	write_matrix(y_name, mA, nX, y);
//#  ifdef DEBUG
//   Print_vector("The product is", y, m); 
//#  endif
   //print_matrix(mA, nA, A);
   free(A);
   //print_matrix(mX, nX, x);
   free(x);
   //print_matrix(mA, nX, y);
   free(y);
	free(thread_handles);

   GET_TIME(end);

   printf("Total time: %f seconds\n", (end-start));
   printf("Math time: %f seconds\n",(end_math - start_math));
   printf("IO time: %f seconds\n", ((end - start) - (end_math-start_math)));
   return 0;
}  /* main */


/*------------------------------------------------------------------
 * Function:  Usage
 * Purpose:   print a message showing what the command line should
 *            be, and terminate
 * In arg :   prog_name
 */
void Usage (char* prog_name) {
   fprintf(stderr, "usage: %s -t <thread_count> -A <A.dat> -x <x.dat> -y <y.dat>\n", prog_name);
   exit(0);
}  /* Usage */


/*------------------------------------------------------------------
 * Function:       Pth_mat_vect
 * Purpose:        Multiply an mxn matrix by an nx1 column vector
 * In arg:         rank
 * Global in vars: A, x, m, n, thread_count
 * Global out var: y
 */
void *Pth_mat_vect(void* rank) {
   long my_rank = (long) rank;
   int i;
   int j;
   int my_first_row = BLOCK_LOW(my_rank, thread_count, m);
   int my_last_row = BLOCK_HIGH(my_rank, thread_count, m);
   register int sub = my_first_row*n;
   //double start, finish;
   double temp;
	

   //printf("Thread %ld > first_row = %d, last_row = %d\n", my_rank, my_first_row, my_last_row);

	
   //GET_TIME(start_math);
   for (i = my_first_row; i <= my_last_row; i++) {
      y[i] = 0.0;
      for (j = 0; j < n; j++) {
          temp = A[sub++];
          temp *= x[j];
          y[i] += temp;
      }
   }
   //GET_TIME(finish_math);
   //printf("Thread %ld > Elapsed time = %e seconds\n", 
    //  my_rank, finish - start);
	
   return NULL;
}  /* Pth_mat_vect */


/*------------------------------------------------------------------
 * Function:    Print_matrix
 * Purpose:     Print the matrix
 * In args:     title, A, m, n
 */
