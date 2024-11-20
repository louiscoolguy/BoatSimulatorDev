#pragma once
#include <SDL_surface.h>
#include <SDL_rect.h>



class TextureF {
	SDL_Surface* m_imgSurface;
public:
	SDL_Rect* sourceRect;
	SDL_FRect* destRect;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	double texAngle = 0;
	TextureF(const char* fileName);
	TextureF(const char* fileName, SDL_FRect dest);
	TextureF(const char* fileName, SDL_FRect dest, SDL_Rect src);
	void draw() const;
};


class SimpleTexture {
	SDL_Surface* m_imgSurface;
public:
	SDL_Rect* sourceRect;
	SDL_Rect* destRect;
	SimpleTexture(const char* fileName);
	SimpleTexture(const char* fileName, SDL_Rect dest);
	SimpleTexture(const char* fileName, SDL_Rect dest, SDL_Rect src);
	void draw() const;
};