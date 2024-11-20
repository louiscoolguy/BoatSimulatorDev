#include "Collide.h"
#include <iostream>
#include <SDL_rect.h>



void Collide::collideTwoRects(SDL_FRect* rectToMove, SDL_FRect rectToCollide)
{
    SDL_FRect result;
    //If there is no collision return
	if (!SDL_IntersectFRect(rectToMove, &rectToCollide, &result)) return;
	
    
    //If you collide from the top or bottom
    if (result.w >= result.h) {
        //If you collide from the top
        if (result.y == rectToCollide.y) {
            rectToMove->y -= result.h;
            return;
        }
        //If you collide from the bottom
        rectToMove->y += result.h;
        return;
    }

    //If you collide from the left side
    if (result.x == rectToCollide.x) {
        rectToMove->x -= result.w;
        return;
    }
	
	//If you collide from the right side
	rectToMove->x += result.w;
}

void Collide::collideFAndR(SDL_FRect* rectToMoveF, SDL_Rect rectToCollide)
{
    const SDL_FRect rectToCollideF = { static_cast<float>(rectToCollide.x),
        static_cast<float>(rectToCollide.y),
        static_cast<float>(rectToCollide.w),
        static_cast<float > (rectToCollide.h)
    };

	collideTwoRects(rectToMoveF, rectToCollideF);
}

void Collide::collideMultipleRects(SDL_FRect* rectToMove, const std::vector<SDL_FRect>& rects) {
    for (SDL_FRect rect : rects) {
        collideTwoRects(rectToMove, rect);
    }
}