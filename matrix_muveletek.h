#ifndef MATRIX_MUVELETEK_H_INCLUDED
#define MATRIX_MUVELETEK_H_INCLUDED

#include <stdbool.h>

typedef struct Eletter {
	int x_max;
	int y_max;
	bool **eleje;
} Eletter;

void create_eletter(Eletter *e, int x_max, int y_max);
void create_random_eletter(Eletter *e, int x_max, int y_max);
void free_eletter(Eletter *e);
void masol(Eletter *forras, Eletter *cel);


#endif // MATRIX_MUVELETEK_H_INCLUDED
