#pragma once
#include <SDL_rect.h>

class Mouse {
private:
	SDL_DisplayMode m_desktop;
	void setDesktop();
public:
	//	This constructor should always go outside of a scope where its functions are called
	Mouse();
	
	//Gets the mouse position relative to the game window
	//Doesnt matter if the game is 1920x1080 or 800x600, if it is at the same relative position, it will return the same value
	SDL_FPoint getMouseGameRelative(bool Fullscreen) const;
	bool isMouseInFRect(SDL_FRect rect, bool Fullscreen) const;
	bool isMouseInRect(SDL_Rect rect, bool Fullscreen) const;
};