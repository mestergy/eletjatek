#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "debugmalloc.h"
#include "matrix_muveletek.h"
#include "logika.h"
#include "sdl.h"
#include "fajlkezeles.h"
#include "menu.h"

#ifdef _WIN32
    #include <windows.h>
#endif

int main(int argc, char *argv[]) {

#ifdef _WIN32
    SetConsoleCP(1250);
    SetConsoleOutputCP(1250);
#endif

	srand(time(0));

	Eletter jelenlegi;
	kiolvas(&jelenlegi, "kezdolap.txt");

    Megjelenites megjel;
    megjelenites_init(&megjel);

	bool quit = false;
	bool fut = false;

    while (!quit) {
		int x = 0, y = 0;

        SDL_Event event;
        SDL_WaitEvent(&event);

        switch (event.type) {
            case SDL_USEREVENT:
                if(fut) {
                    leptet(&jelenlegi);
                }
                kirajzol_ablak(&megjel, jelenlegi);
                break;

			case SDL_MOUSEBUTTONDOWN:
                x = event.button.x;
                y = event.button.y;
                if (x > 600) {
                    fut = menu(x, y, fut, &jelenlegi, megjel.gombok);
                } else {
					cellamuvelet(x, y, &jelenlegi);
                }
                break;

            case SDL_QUIT:
                quit = true;
                break;
        }
    }

	free_eletter(&jelenlegi);

    return 0;
}

