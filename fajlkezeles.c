#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "debugmalloc.h"
#include "fajlkezeles.h"
#include "matrix_muveletek.h"

void kiolvas(Eletter *e, char nev[]) {
	int aktualis;
	int i, j;
	FILE *fp;
	fp = fopen(nev, "r");

	if (fp != NULL) {
		fscanf(fp, "%dx%d\n", &i, &j);
		if((i > 800) && (j > 600)) {
			printf("Nem megfelel� a f�jlban t�rolt �rt�k");
			return;
		}
		create_eletter(e, i, j);
		printf("M�retei:%dx%d\n", e->x_max, e->y_max);

		for(int y = 0; y < e->y_max; y++) {
			for(int x = 0; x < e->x_max; x++) {
				fscanf(fp, "%1d;", &aktualis);
				if((aktualis != 0) && (aktualis != 1)) {
					free_eletter(e);
					create_eletter(e, i, j);
					perror("Nem megfelel� a fajl, csak a m�retet tudtam �tvenni");
					return;
				}
				e->eleje[y][x] = (bool)aktualis;
			}
		}
		fclose(fp);
    }
    else
        perror("Nem siker�lt megnyitni a f�jlt");
}

void elment(Eletter e) {
	printf("Milyen n�vre mentsem? ");
	char nev[20];
	scanf("%s", nev);

	FILE *firott;
	firott = fopen(nev, "w");
	if (firott != NULL) {
		fprintf(firott, "%dx%d\n", e.x_max, e.y_max);
		for(int y = 0; y < e.y_max; y++) {
			for(int x = 0; x < e.x_max; x++) {
				fprintf(firott, "%d;", e.eleje[y][x]);
			}
			fprintf(firott, "\n");
		}
		fclose(firott);
	}
    else {
        perror("Nem siker�lt a ment�s");
    }
}
