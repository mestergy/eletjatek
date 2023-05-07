#ifndef SDL_H_INCLUDED
#define SDL_H_INCLUDED

#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

typedef struct Gomb {
	char nev[16];
	int x1;
	int y1;
	int x2;
	int y2;
	int id;
} Gomb;

typedef struct Megjelenites {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_TimerID id;
    Gomb gombok[9];
} Megjelenites;

void kirajzol_ablak(Megjelenites *megjel, Eletter jelenlegi);
void gomb_kirajzol(SDL_Renderer *r, Gomb g);

void megjelenites_init(Megjelenites *megjel);
void sdl_init(char const *felirat, int szeles, int magas, SDL_Window **pwindow, SDL_Renderer **prenderer);

void kirajzol(SDL_Renderer *r, Eletter e);

Uint32 idozit(Uint32 ms, void *param);


#endif // SDL_H_INCLUDED
