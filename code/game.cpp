#include <SDL.h>
#include <iostream>
#include "MainWindow.h"
#include "Game.h"
#include "Player.h"
#include "DrawTexture.h"
#include "Collide.h"

//SDL_Rect rect = { 300, 100, 100, 100 };
//SDL_Rect rect2 = { 100, 100, 50, 50 };
SDL_Rect srcRect = { 0, 0, 16, 16 };


static void RectF(SDL_FRect* drawRect, unsigned char r, unsigned char g, unsigned char b, unsigned char layer) {
	*drawRect = {
		drawRect->x - player.camera.x,
		drawRect->y - player.camera.y,
		drawRect->w,
		drawRect->h
	};
	if (drawRect->x + drawRect->w < 0 ||
		drawRect->y + drawRect->h < 0 )
	{
		std::cout << "RETURN\n";
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
//SimpleTexture steveTexture("assets/art/steve.png");

void Game::mainGameUpdate() {
	

    setDrawColor(215, 215, 215);
    SDL_RenderClear(renderer);


	
    //setDrawColor(255, 255, 255);
	//SDL_RenderFillRect(renderer, &rect);
	
	



	player.update();
    //col.collideFAndR(&player.hitbox, rect);
	SDL_FRect sigma = { 100, 100, 100, 100 };

	

	

	RectF(&sigma, 255, 0, 0, 0);
	col.collideTwoRects(&player.hitbox, sigma);
	

	player.rect.x = (player.hitbox.x - PL_OFFSETX) + player.camera.x;
	player.rect.y = (player.hitbox.y - PL_OFFSETY) + player.camera.y;


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

	//steveTexture.destRect = &rect;
	//steveTexture.draw();

	//steveTexture.destRect = &rect2;
	//steveTexture.draw();

	
	if (DEBUG_MODE_ACTIVE) 
	{
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 100);
		SDL_RenderFillRectF(renderer, &drawRect);
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 100);
		SDL_RenderFillRectF(renderer, &player.hitbox);
	}
    
    SDL_RenderPresent(renderer);
}


