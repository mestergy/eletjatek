#include <stdio.h>
#include "logika.h"
#include "matrix_muveletek.h"


static bool mellette_van_e(Eletter e, int x, int y, int vx, int vy) {
	if((x+vx < 0) || (x+vx >= e.x_max) || (y+vy < 0) || (y+vy >= e.y_max)) {
		return false;
	} else if ((x == x+vx) && (y == y+vy)) {
		return false;
	} else {
		return true;
	}
}

static int szomszedok(Eletter e, int x, int y) {
	int ossz = 0;
	for(int j = -1; j <= 1; j++) {
		for(int i = -1; i <= 1; i++)
			if(mellette_van_e(e, x, y, i, j))
				ossz += e.eleje[j+y][i+x];
	}
	return ossz;
}

void logika(Eletter most, Eletter kov) {
	for(int y = 0; y < most.y_max; y++) {
		for(int x = 0; x < most.x_max; x++) {
			if (szomszedok(most, x, y) == 3)
				kov.eleje[y][x] = true;
			else
				if ((szomszedok(most, x, y) == 2) && (most.eleje[y][x]))
					kov.eleje[y][x] = true;
			else
				kov.eleje[y][x] = false;
		}
	}
}

void leptet(Eletter *most) {
	Eletter kovetkezo;
	create_eletter(&kovetkezo, most->x_max, most->y_max);
	logika(*most, kovetkezo);
	masol(&kovetkezo, most);
	free_eletter(&kovetkezo);
}
