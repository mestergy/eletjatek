#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "debugmalloc.h"
#include "fajlkezeles.h"
#include "logika.h"
#include "matrix_muveletek.h"
#include "sdl.h"

void cellamuvelet(int xkp, int ykp, Eletter *e) {
    int meret_x = 800 / e->x_max;
	int meret_y = 600 / e->y_max;
	int meret = meret_x < meret_y ? meret_x : meret_y;
	int x = floor(xkp / meret);
	int y = floor(ykp / meret);
	if(x < e->x_max && y < e->y_max) {
        e->eleje[y][x] = !e->eleje[y][x];
	}
}

static int melyiket(int x, int y, Eletter e, Gomb gombok[]) {
	for(int ind = 0; ind < 8; ind++) {
		if(gombok[ind].x1 < x && gombok[ind].x2 > x && gombok[ind].y1 < y && gombok[ind].y2 > y)
			return gombok[ind].id;
	}
	return -1;
}

bool menu(int x, int y, bool fut_e, Eletter *e, Gomb gombok[]) {
	int id;
	if(x > 800) {
        id = melyiket(x, y, *e, gombok);
	} else {
        id = 99;
	}
	switch(id) {
		case 0 :
			return true;
		case 1 :
			return false;
		case 2 :
			if(fut_e)
				return true;
			leptet(e);
			return false;
		case 3 :
			free_eletter(e);
			create_random_eletter(e, e->x_max, e->y_max);
			return false;
		case 4 :
			free_eletter(e);
			create_eletter(e, e->x_max, e->y_max);
			return false;
		case 5 :
			printf("Mekkora legyen az új életter? /szélesség, magasság/\n");
			int szeles, magas;
			scanf("%d %d", &szeles, &magas);
			while (!(szeles <= 800 && szeles > 0 && magas <= 600 && magas > 0)) {
				printf("0 < szélesseg <= 800 és 0 < magasság <= 600\n");
				scanf("%d %d", &szeles, &magas);
			}
			free_eletter(e);
			create_eletter(e, szeles, magas);
			return false;
		case 6 :
			if(!fut_e) {
				printf("Melyik fájlt olvassam be? ");
				char fajlnev[20];
				scanf("%s", fajlnev);
				kiolvas(e, fajlnev);
				return false;
			}
			return false;
		case 7 :
			if(!fut_e)
				elment(*e);
			return false;
        case 99:
            if(!fut_e) {
                cellamuvelet(x, y, e);
                return false;
            }
            return true;
        default:
            return false;
	}
}
