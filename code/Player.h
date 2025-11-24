#pragma once
#include <SDL_rect.h>
#include <SDL_keycode.h>


class Player {
public:
	SDL_FRect rect = { 0, 0, 64, 64 };
	SDL_FPoint camera = { 0, 0 };
	SDL_FRect hitbox = { 0, 0, 1, 1 };
	SDL_Rect srcRect = { 0, 0, 16, 16 };
	SDL_FPoint camOffset = { 0, 0 };
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	float speed = 0.1f;
	void update();
	void loadSettings();
};

extern Player player;
