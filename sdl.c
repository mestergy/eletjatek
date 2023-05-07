#include <string.h>
#include <math.h>

#include "logika.h"
#include "matrix_muveletek.h"
#include "sdl.h"

/* ablak letrehozasa */
void sdl_init(char const *felirat, int szeles, int magas, SDL_Window **pwindow, SDL_Renderer **prenderer) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
        exit(1);
    }
    SDL_Window *window = SDL_CreateWindow(felirat, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, szeles, magas, 0);
    if (window == NULL) {
        SDL_Log("Nem hozhato letre az ablak: %s", SDL_GetError());
        exit(1);
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL) {
        SDL_Log("Nem hozhato letre a megjelenito: %s", SDL_GetError());
        exit(1);
    }
    SDL_RenderClear(renderer);

    *pwindow = window;
    *prenderer = renderer;
}

void kirajzol_eletter(SDL_Renderer *r, Eletter e) {
	int meret_x = 800 / e.x_max;
	int meret_y = 600 / e.y_max;
	int meret = meret_x < meret_y ? meret_x : meret_y;
	for(int y = 0; y < e.y_max; y++) {
		for(int x = 0; x < e.x_max; x++) {
			Uint32 szin = 0x800080FF;
			if(e.eleje[y][x] == 0)
				szin = 0x000000FF;
			boxColor(r, x*meret, y*meret, (x+1)*meret, (y+1)*meret, szin);
		}
	}
}

void kirajzol_ablak(Megjelenites *megjel, Eletter jelenlegi) {
    boxRGBA(megjel->renderer, 0, 0, 1000, 600, 0, 0, 0, 255);
    for(int i = 0; i < 8; i++) {
        gomb_kirajzol(megjel->renderer, megjel->gombok[i]);
    }
    kirajzol_eletter(megjel->renderer, jelenlegi);
    SDL_RenderPresent(megjel->renderer);
}

Uint32 idozit(Uint32 ms, void *param) {
    SDL_Event ev;
    ev.type = SDL_USEREVENT;
    SDL_PushEvent(&ev);
    return ms;   /* ujabb varakozas */
}

void gomb_kirajzol(SDL_Renderer *r, Gomb g) {
	int keret = 5;
	int szo_hossz = strlen(g.nev);
	boxRGBA(r, g.x1, g.y1, g.x2, g.y2, 128, 0, 128, 255);
	boxRGBA(r, g.x1+keret, g.y1+keret, g.x2-keret, g.y2-keret, 255, 255, 255, 255);
	stringRGBA(r, g.x1 + (g.x2-g.x1)/2 - (szo_hossz / 2)*9 , g.y1 + (g.y2-g.y1) / 2, g.nev, 0, 0, 0, 255);
}

void gombok_init(Gomb gombok[], int meret) {
	int kitalalt_x1 = 840, teglalap_merete = 35, koz = 25, alap = 60, hossz = 120;

	strcpy(gombok[0].nev, "Indit");
	strcpy(gombok[1].nev, "Megallit");
	strcpy(gombok[2].nev, "Leptet");
	strcpy(gombok[3].nev, "Random");
	strcpy(gombok[4].nev, "Alaphelyzet");
	strcpy(gombok[5].nev, "Atmeretez");
	strcpy(gombok[6].nev, "Beolvas");
	strcpy(gombok[7].nev, "Mentes");

	for(int i = 0; i < meret; i++) {
		gombok[i].x1 = kitalalt_x1;
		gombok[i].y1 = (teglalap_merete + koz)*i + alap;
		gombok[i].x2 = kitalalt_x1 + hossz;
		gombok[i].y2 = (i+1)*teglalap_merete + alap + i*koz;
		gombok[i].id = i;
	}
}

void megjelenites_init(Megjelenites *megjel) {
    gombok_init(megjel->gombok, 8);
    sdl_init("Életjáték", 1000, 600, &megjel->window, &megjel->renderer);
    megjel->id = SDL_AddTimer(200, idozit, NULL);
}

void megjelenites_close(Megjelenites *megjel){
    SDL_RemoveTimer(megjel->id);
    SDL_Quit();
}
