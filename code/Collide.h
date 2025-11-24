#pragma once
#include <SDL_rect.h>
#include <vector>

class Collide {
public:
	static bool collideTwoRects(SDL_FRect* rectToMove, const SDL_FRect& rectToCollide);
	static void collideMultipleRects(SDL_FRect* rectToMove, const std::vector<SDL_FRect>& rects);
	static void collideFAndR(SDL_FRect* rectToMove, SDL_Rect rectToCollide);
};