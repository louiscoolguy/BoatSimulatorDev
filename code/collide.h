#pragma once
#include <SDL_rect.h>
#include <vector>

class Collide {
public:
	void collideTwoRects(SDL_FRect* rectToMove, SDL_FRect rectToCollide);
	void collideMultipleRects(SDL_FRect* rectToMove, const std::vector<SDL_FRect>& rects);
	void collideFAndR(SDL_FRect* rectToMove, SDL_Rect rectToCollide);
};