#include <SDL_image.h>
#include <SDL.h>
#include "mainwindow.h"
#include "drawtexture.h"

#define TextureInit() \
m_imgSurface = IMG_Load(fileName);\
if (m_imgSurface == NULL)\
    errbox("Error loading image.", fileName);

TextureF::TextureF(const char* fileName) {
    sourceRect = NULL;
    destRect = NULL;
	TextureInit()
}


TextureF::TextureF(const char* fileName, SDL_FRect dest) {
    sourceRect = NULL;
    destRect = &dest;
    TextureInit()
}

TextureF::TextureF(const char* fileName, SDL_FRect dest, SDL_Rect src) {
    sourceRect = &src;
    destRect = &dest;
    TextureInit()
}


void TextureF::draw() const {
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, m_imgSurface);
	SDL_RenderCopyExF(renderer, tex, sourceRect, destRect, texAngle, NULL, flip);
    SDL_DestroyTexture(tex);
}


SimpleTexture::SimpleTexture(const char* fileName) {
	sourceRect = NULL;
	destRect = NULL;
	TextureInit()
}

SimpleTexture::SimpleTexture(const char* fileName, SDL_Rect dest) {
	sourceRect = NULL;
	destRect = &dest;
	TextureInit()
}

SimpleTexture::SimpleTexture(const char* fileName, SDL_Rect dest, SDL_Rect src) {
	sourceRect = &src;
	destRect = &dest;
	TextureInit()
}

void SimpleTexture::draw() const {
	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, m_imgSurface);
	SDL_RenderCopy(renderer, tex, sourceRect, destRect);
	SDL_DestroyTexture(tex);
}