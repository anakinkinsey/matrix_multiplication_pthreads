CC=gcc
MCC =mpicc
CFLAGS=-Wall -Wstrict-prototypes -D_SVID_SOURCE -std=c99 -lm
LFLAGS=-lm -pthread -lpthread
PROGS = pth_mat_vect_rand_split make_matrix print_matrix

all: $(PROGS)

pth_mat_vect_rand_split: pth_mat_vect_rand_split.c functions.c timer.h
	$(CC) $(CFLAGS) -o pth_mat_vect_rand_split pth_mat_vect_rand_split.c timer.h functions.c $(LFLAGS)

make_matrix: make-matrix.c functions.c
	$(CC) $(CFLAGS) -o make_matrix make-matrix.c functions.c

print_matrix: print-matrix.c functions.c
	$(CC) $(CFLAGS) -o print_matrix print-matrix.c functions.c
	
clean:
	rm -f $(PROGS) *.o core*