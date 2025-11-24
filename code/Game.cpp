#include <SDL.h>
#include <iostream>
#include <variant>
#include "MainWindow.h"
#include "Game.h"
#include "Player.h"
#include "DrawTexture.h"
#include "Collide.h"
#include "FPSInfo.h"

//SDL_Rect rect = { 300, 100, 100, 100 };
//SDL_Rect rect2 = { 100, 100, 50, 50 };
SDL_Rect srcRect = { 0, 0, 16, 16 };


static void RectF(SDL_FRect* drawRect, unsigned char r, unsigned char g, unsigned char b, unsigned char layer, SDL_FPoint cam) {
	*drawRect = {
		drawRect->x - cam.x,
		drawRect->y - cam.y,
		drawRect->w,
		drawRect->h
	};
	if (drawRect->x + drawRect->w < 0 ||
		drawRect->y + drawRect->h < 0 )
	{
		return;
	}
	SDL_SetRenderDrawColor(renderer, r, g, b, 255);
	SDL_RenderFillRectF(renderer, drawRect);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}


void Game::init() {
	player.loadSettings();
}


Collide col;
TextureF plTexture("assets/art/char1-walk.png");


void Game::mainGameUpdate() {
	

    setDrawColor(215, 215, 215);
    SDL_RenderClear(renderer);
	

	
	SDL_FRect h = { 150, 50, 200, 200 };
	SDL_FRect g = { 600, 50, 200, 100 };
	
	player.update();
	
	
	RectF(&h, 255, 0, 0, 0, player.camera);
	RectF(&g, 0, 255, 0, 0, player.camera);
	col.collideTwoRects(&player.hitbox, h);

	
	
	player.rect.x = (player.hitbox.x - player.rect.w / 3.2f) + player.camera.x;
	player.rect.y = (player.hitbox.y - player.rect.h / 8)    + player.camera.y;

	SDL_FRect drawRect = {
		player.rect.x - player.camera.x,
		player.rect.y - player.camera.y,
		player.rect.w,
		player.rect.h
	};
	
	plTexture.destRect = &drawRect;
	plTexture.sourceRect = &player.srcRect;
	plTexture.flip = player.flip;
	plTexture.draw();

	
	if (DEBUG_MODE_ACTIVE) 
	{
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 100);
		SDL_RenderFillRectF(renderer, &drawRect);
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 100);
		SDL_RenderFillRectF(renderer, &player.hitbox);
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 100);
		SDL_RenderFillRectF(renderer, &player.rect);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	}
    
    SDL_RenderPresent(renderer);
}


