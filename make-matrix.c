/*
	Cory Rothenberger & Anakin Kinsey
	CSCI 473
	October 27th
	Team Project
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "functions.h"
#include "getopt.h"
int main(int argc, char **argv)
{
	int opt;
	int rows;
	int columns;
	int lower;
	int upper;
	double *myArray;
	char *in;

	if(argc < 11)
    	{
        printf("The proper usage is './make-matrix -m ## -n ## -l ## -u ## -o outputFile\n");
        exit(0);
    	}
	else
	{

		while((opt = getopt(argc, argv, "m:n:o:l:u:")) != -1)
		{
			switch(opt)
			{	
				case'l':
					lower = atoi(optarg);
				break;
				case'u':
					upper = atoi(optarg);
				break;
				case'm':
					rows = atoi(optarg);
				break;
				case'n':
					columns = atoi(optarg);
				break;
				case'o':
					in = optarg;
				break;
				case '?':
					printf("Incorrect Input \nCorrect Usage: ");
					printf("./make-matrix -m ## -n ## -l ## -u ## -o output_file\n");
					printf("Where m = # of rows, n = # of columns\n");
					exit(0);
				break;
				
			}
		}

		make_matrix(rows,columns,lower,upper,&myArray);

		write_matrix(in, rows, columns, myArray);

		free(myArray);
	}
	return 0;
}
