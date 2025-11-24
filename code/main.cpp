#include <iostream>
#include <thread>
#include <chrono>
#include <SDL.h>
#include "MainWindow.h"
#include "Game.h"
#include "FPSInfo.h"
#include "WindowInformation.h"


SDL_DisplayMode desktopDisplay;
SDL_Window* win;
SDL_Renderer* renderer;
FPSStruct delta;
WindowInformation desktop;
bool DEBUG_MODE_ACTIVE;
int FPS_CAP = 60;

enum WindowType {
	WINDOWED,
    TWICE,
	FULLSCREEN,
};


static void CommandMain() {
    while (true) {
	    std::cout << "Enter command: ";
	    std::string command;
	    std::cin >> command;
        if (command == "exit") {
            SDL_DestroyWindow(win);
            SDL_Quit();
            exit(0);
        }

	    if (command == "fps") std::cout << "FPS: " << delta.currentFPS << std::endl;
		if (command == "delta") std::cout << "Delta: " << delta.deltaTime << std::endl;
	    if (command == "debug") DEBUG_MODE_ACTIVE = !DEBUG_MODE_ACTIVE;

	    if (command == "setfps") {
		    int fps;
		    std::cin >> fps;
		    if (fps < 1) {
			    std::cout << "FPS must be greater than 0" << std::endl;
                continue;
		    }
			FPS_CAP = fps;
	    }

		if (command == "display")
			std::cout << "Display width: " << desktopDisplay.w << " Display height: " << desktopDisplay.h << std::endl;

        if (command == "scale") {
			float x, y;
			std::cin >> x;
			std::cin >> y;
			SDL_RenderSetScale(renderer, x, y);
        }
    }
}


int main(int argc, char** argv){
    #pragma region Init SDL
    win = nullptr;
    renderer = nullptr;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) 
        return errbox("sdl library", "code 0 no sdl library that is working");

    win = SDL_CreateWindow(
        "Boating N Guns", 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        WINDOW_WIDTH, WINDOW_HEIGHT, 
        SDL_WINDOW_SHOWN
    );
    if (!win) 
        return errbox("window init", "failed to make sdl window");


    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) 
        return errbox("sdl renderer", "code 2 no sdl renderer found");

	//Set to nearest cause I need pixel art
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
    SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");
    delta.frameCount = 0;


    
    if (SDL_GetCurrentDisplayMode(0, &desktopDisplay) < 0) 
        return errbox("sdl display", "code 3 no display found or invalid display");
    #pragma endregion

    desktop.desktopWidth = desktopDisplay.w;
	desktop.desktopHeight = desktopDisplay.h;


	std::thread CommandThread(CommandMain);
	CommandThread.detach();


	//SDL_ShowCursor(SDL_DISABLE);

    bool gameIsRunning = true;
    float frameTime;

	// Set FPS
	Game::init();

    int winType = WindowType::WINDOWED;
	bool allowedF11 = true;
	DEBUG_MODE_ACTIVE = false;


    while (gameIsRunning) 
    {
        float frameDelay = 1000.0 / FPS_CAP;
		float startTime = SDL_GetTicks();

        SDL_Event event;
        while (SDL_PollEvent(&event)) 
        {
            if (event.type == SDL_QUIT) {
                gameIsRunning = false;
            }


			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_F11 && allowedF11) {
                switch (winType) {
                    case WindowType::WINDOWED:

						winType = WindowType::TWICE;
                        allowedF11 = false;

						SDL_RenderSetScale(renderer, 2, 2);
                        SDL_SetWindowFullscreen(win, 0);
						SDL_SetWindowSize(win, WINDOW_WIDTH * 2, WINDOW_HEIGHT * 2);
						SDL_SetWindowPosition(win, desktopDisplay.w / 2 - WINDOW_WIDTH, desktopDisplay.h / 2 - WINDOW_HEIGHT);
                        break;

                    case WindowType::TWICE:
                        winType = WindowType::FULLSCREEN;
                        allowedF11 = false;

						SDL_SetWindowFullscreen(win, SDL_WINDOW_FULLSCREEN_DESKTOP);
                        SDL_RenderSetScale(renderer, desktopDisplay.w /(float)WINDOW_WIDTH, desktopDisplay.w / (float)WINDOW_WIDTH);
						desktop.windowIsFullscreen = true;
                        break;
                    case WindowType::FULLSCREEN:
						winType = WindowType::WINDOWED;
						allowedF11 = false;

						SDL_RenderSetScale(renderer, 1, 1);
						SDL_SetWindowFullscreen(win, 0); 
						SDL_SetWindowSize(win, WINDOW_WIDTH, WINDOW_HEIGHT);
						SDL_SetWindowPosition(win, desktopDisplay.w / 2 - WINDOW_WIDTH / 2, desktopDisplay.h / 2 - WINDOW_HEIGHT / 2);
						desktop.windowIsFullscreen = false;
                        break;
                }
			}

            //When F11 is released we allow you to press it again
			if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_F11) {
				allowedF11 = true;
			}
        }


        Game::mainGameUpdate();



        delta.frameCount++;

		//Limit FPS
        frameTime = SDL_GetTicks() - startTime;

        if (frameTime < frameDelay) {
		    delta.deltaTime = frameDelay;
            delta.currentFPS = 1000 / frameDelay;
		} else {
			delta.deltaTime = frameTime;
			delta.currentFPS = 1000 / frameTime;
		}

        if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
    }


    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}