
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void read_matrix(char* file_name, int* m, int* n, double** matrix)
{
    FILE* file;
    file = fopen(file_name, "rb");

    if(file == NULL)
    {
        printf("File does not exist");
        exit(0);
    }
    fread(m, sizeof(int), 1, file);
    fread(n, sizeof(int), 1, file);
    *matrix = (double*)malloc(sizeof(double)*((*n)*(*m)));
    fread(*matrix, sizeof(double), ((*n)*(*m)), file);

	fclose(file);
}

void print_matrix(int m, int n, double* matrix)
{
	int i;
	for(i = 0; i <m*n; i++)
	{
		printf("%0.2f ", matrix[i]);
		if((i+1)%n == 0)
		{
			printf("\n");		
		}
	}
}


void make_matrix(int m, int n, double l, double u, double** matrix)
{
    printf("%ld", sizeof(int));
    *matrix = (double*)malloc(sizeof(double)*(n*m));
    int i;
    srand(time(0));
    for(i = 0; i < (m*n); i++)
    {
    		double num = RAND_MAX/(u-l);
        (*matrix)[i] = l + (rand()/num);
    }

    

}

void write_matrix(char* file_name, int m, int n, double* matrix)
{
    FILE* file = fopen(file_name, "w");
    fwrite(&m, sizeof(int), 1, file);
    fwrite(&n, sizeof(int), 1, file);
    fwrite(matrix, sizeof(double), (n*m), file);
	fclose(file);

}
