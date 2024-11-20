#pragma once
#include <SDL_render.h>

#define WINDOW_WIDTH 480
#define WINDOW_HEIGHT 270

extern SDL_Window* win;
extern SDL_Renderer* renderer;

extern bool DEBUG_MODE_ACTIVE;

#define errbox( t, msg ) SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, t, msg, NULL)
#define infobox( t, msg ) SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, t, msg, NULL)
#define setDrawColor( r,g,b ) SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE)