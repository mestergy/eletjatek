#include <stdio.h>
#include <stdbool.h>

#include "debugmalloc.h"
#include "logika.h"
#include "matrix_muveletek.h"

void create_eletter(Eletter *e, int x_max, int y_max) {
	e->x_max = x_max;
	e->y_max = y_max;
	e->eleje = (bool**) malloc(sizeof(bool*) * y_max);
		if (e->eleje == NULL) {
			printf("Nem sikerült memóriát foglalni!\n");
			return;
		}
	e->eleje[0] = (bool*) malloc(sizeof(bool) * y_max * x_max);
		if (e->eleje[0] == NULL) {
			printf("Nem sikerült memóriát foglalni!\n");
			return;
		}
	for(int i = 0; i < y_max; ++i) {
		e->eleje[i] = e->eleje[0] + i*x_max;
	}
	for(int j = 0; j < y_max; ++j) {
		for(int i = 0; i < x_max; ++i) {
			e->eleje[j][i] = false;
		}
	}
}

void create_random_eletter(Eletter *e, int x_max, int y_max) {
	e->x_max = x_max;
	e->y_max = y_max;
	e->eleje = (bool**) malloc(sizeof(bool*) * y_max);
	e->eleje[0] = (bool*) malloc(sizeof(bool) * y_max * x_max);
	for(int i = 0; i < y_max; ++i) {
		e->eleje[i] = e->eleje[0] + i*x_max;
	}
	for(int j = 0; j < y_max; ++j) {
		for(int i = 0; i < x_max; ++i) {
			e->eleje[j][i] = rand() % 2;
		}
	}
}

void free_eletter(Eletter *e) {
	free(e->eleje[0]);
	free(e->eleje);
}

void masol(Eletter *forras, Eletter *cel) {
	cel->x_max = forras->x_max;
	cel->y_max = forras->y_max;
	free_eletter(cel);
	create_eletter(cel, cel->x_max, cel->y_max);
	for(int j = 0; j < cel->y_max; ++j) {
		for(int i = 0; i < cel->x_max; ++i) {
			cel->eleje[j][i] = forras->eleje[j][i];
		}
	}
}
