#pragma once
#include <SDL_rect.h>
#include <SDL_keycode.h>

#define PL_OFFSETX player.rect.w / 3.2f
#define PL_OFFSETY player.rect.h / 8
#define PL_SIGMA 0

class Player {
public:
	SDL_FRect rect = { 0, 0, 64, 64 };
	SDL_FPoint camera = { 0, 0 };
	SDL_FRect hitbox = { 0, 0, 1, 1 };
	SDL_Rect srcRect = { 0, 0, 16, 16 };
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	float speed = 0.1f;
	void update();
	void loadSettings();
};

extern Player player;
