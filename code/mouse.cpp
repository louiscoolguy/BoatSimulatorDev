#include <SDL.h>
#include <thread>
#include "MainWindow.h"
#include "Mouse.h"

//Do this because its better to have it in contructor get the desktop size every function call
void Mouse::setDesktop() {
	while (!m_desktop.w) SDL_GetDesktopDisplayMode(0, &m_desktop);
}

//This constructor should always go outside of a scope where its functions are called
Mouse::Mouse() {
	m_desktop = { 0, 0, 0 ,0 };
	std::thread t(&Mouse::setDesktop, this);
	t.detach();
}

//Gets the mouse position relative to the game window
//Doesnt matter if the game is 1920x1080 or 800x600, if it is at the same relative position, it will return the same value
SDL_FPoint Mouse::getMouseGameRelative(bool Fullscreen) const {
	int IntmouseX = 1, IntmouseY = 1;
	int windowWidth = 0, windowHeight = 0;

	SDL_GetWindowSize(win, &windowWidth, &windowHeight);
	SDL_GetMouseState(&IntmouseX, &IntmouseY);


	if (Fullscreen) {
		return {
			IntmouseX / (m_desktop.w / (float)WINDOW_WIDTH),
			IntmouseY / (m_desktop.h / (float)WINDOW_HEIGHT)
		};
	}

	return {
		IntmouseX / (windowWidth / (float)WINDOW_WIDTH),
		IntmouseY / (windowHeight / (float)WINDOW_HEIGHT)
	};
}

bool Mouse::isMouseInFRect(SDL_FRect rect, bool Fullscreen) const {
	SDL_FPoint mouse = getMouseGameRelative(Fullscreen);
	return mouse.x >= rect.x && mouse.x <= rect.x + rect.w && mouse.y >= rect.y && mouse.y <= rect.y + rect.h;
}

bool Mouse::isMouseInRect(SDL_Rect rect, bool Fullscreen) const {
	SDL_FPoint mouse = getMouseGameRelative(Fullscreen);
	return mouse.x >= rect.x && mouse.x <= rect.x + rect.w && mouse.y >= rect.y && mouse.y <= rect.y + rect.h;
}