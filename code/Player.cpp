#include <SDL.h>
#include <SDL_mixer.h>
#include <cmath>
#include <iostream>
#include <random>
#include <fstream>
#include "MainWindow.h"
#include "Player.h"
#include "FPSInfo.h"
#include "WindowInformation.h"
#include "Mouse.h"
#include "WorldGeneration.h"
#include "Collide.h"


Player player;
int Bindings[] = 
{ 
	SDL_SCANCODE_W, 
	SDL_SCANCODE_S,
	SDL_SCANCODE_A,
	SDL_SCANCODE_D,
	SDL_SCANCODE_F,
	SDL_SCANCODE_F1,
	SDL_SCANCODE_E 
};

enum KeyBinds {
	forwardKey = 0,
	backwardKey,
	leftKey,
	rightKey,
	flashlightKey,
	debugKey,
	interactKey
};

enum Direction {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};


#define KeyDown( key ) keys [ Bindings [ KeyBinds :: key ] ]
#define LittleDown( key ) keys [ Bindings [ KeyBinds :: key ] ] && ! keysLastFrame [ Bindings [ KeyBinds :: key ] ]

#define PressedOnce( key, name ) static bool name = false;\
if (keys [ Bindings [ KeyBinds :: key ] ] && ! keysLastFrame [ Bindings [ KeyBinds :: key ] ])\
	name = !name; if (name)







Mouse mouseClass;

void Player::update() {
	const Uint8* keys = SDL_GetKeyboardState(NULL);

	// This is a hacky way to get the keys from the last frame
	// I dont free there only one instance of it
	static Uint8* keysLastFrame = new Uint8[SDL_NUM_SCANCODES];
	
	SDL_FPoint mouse = mouseClass.getMouseGameRelative(desktop.windowIsFullscreen);

	if (mouseClass.isMouseInFRect(player.hitbox, desktop.windowIsFullscreen) && LittleDown(interactKey)) {
		Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
		Mix_Music* music = Mix_LoadMUS("assets/sfx/ding.ogg");
		Mix_Chunk* sound = Mix_LoadWAV("assets/sfx/ding.ogg");
		if (!music || !sound) {
			std::cerr << "Failed loading sound\n";
			return;
		}
		Mix_PlayMusic(music, 1);
	}

	
	

	const float centerHitboxX = player.hitbox.x + player.hitbox.w / 2;
	const float centerHitboxY = player.hitbox.y + player.hitbox.h / 2;

	
	if (LittleDown(debugKey))
		DEBUG_MODE_ACTIVE = !DEBUG_MODE_ACTIVE;

	std::random_device rd;         // seed
	std::mt19937 gen(rd());        // generator
	std::uniform_int_distribution<> dist(1, 100); // range

	int num = dist(gen);
	
	if (DEBUG_MODE_ACTIVE) {
		perlinData_t perlinValues = getFirstWorld(num);
		
		
		const int boxSize = 1;

		for (int i = 0; i < perlinValues.size(); i++) {
			auto& [perlinX, perlinY, perlinColor] = perlinValues[i];
			int rgb[3] = { perlinColor , perlinColor, perlinColor};

			//WORST CODE OF ALL TIME I AM STILL TESTING
			if (perlinColor <= WATER) {
				//Water
				rgb[0] = 0;
				rgb[1] = 0;
				rgb[2] = 255;
			}else if (perlinColor >= SNOW_MOUNTAIN_TOP) {
				//Snow Mountain Top
				rgb[0] = 255;
				rgb[1] = 255;
				rgb[2] = 255;
			}else if (perlinColor >= ALMOST_MOUNTAIN && perlinColor < SNOW_MOUNTAIN_TOP) {
				//Almost Mountain
				rgb[0] = 255;
				rgb[1] = 0;
				rgb[2] = 0;
			}else if (perlinColor >= GRASS && perlinColor < ALMOST_MOUNTAIN) {
				//Grass
				rgb[0] = 0;
				rgb[1] = 255;
				rgb[2] = 0;
			}else if (perlinColor >= SAND && perlinColor < GRASS) {
				//Sand
				rgb[0] = 255;
				rgb[1] = 255;
				rgb[2] = 0;
			} else {
				//Water fade out
				rgb[0] = 0;
				rgb[1] = 255;
				rgb[2] = 255;
			}

			SDL_SetRenderDrawColor(renderer, rgb[0], rgb[1], rgb[2], 255);
			SDL_Rect perlinRect = { perlinX * boxSize, perlinY * boxSize, boxSize, boxSize };
			SDL_RenderFillRect(renderer, &perlinRect);
			setDrawColor(255, 255, 255);
		}
	}


	const unsigned char fpsFrame = 12;
	const int animTime = (delta.currentFPS / fpsFrame == 0) ? 1 : delta.currentFPS / fpsFrame;
	if (delta.frameCount % animTime == 0) {
		player.srcRect.x = (player.srcRect.x >= 80) ? 0 : player.srcRect.x + 16;
	}

	if (KeyDown(forwardKey) && !KeyDown(backwardKey)) {
		player.rect.y -= player.speed * delta.deltaTime;
	}

	if (KeyDown(backwardKey) && !KeyDown(forwardKey)) {
		player.rect.y += player.speed * delta.deltaTime;
	}

	if (KeyDown(leftKey) && !KeyDown(rightKey)) {
		player.rect.x -= player.speed * delta.deltaTime;
		player.flip = SDL_FLIP_HORIZONTAL;
	}

	if (KeyDown(rightKey) && !KeyDown(leftKey)) {
		player.rect.x += player.speed * delta.deltaTime;
		player.flip = SDL_FLIP_NONE;
	}
	

	/*if (
		(player.rect.x - player.camera.x) > WINDOW_WIDTH ||
		(player.rect.x - player.camera.x + player.rect.w) < 0 ||
		(player.rect.y - player.camera.y) > WINDOW_HEIGHT ||
		(player.rect.y - player.camera.y + player.rect.h) < 0
	) {
	}*/
	
	player.camera.x = (player.rect.x - 194) + player.camOffset.x;
	player.camera.y = (player.rect.y - 100) + player.camOffset.y;

	player.hitbox = {
		player.rect.x + player.rect.w / 3.2f - player.camera.x,
		player.rect.y + player.rect.h / 8 - player.camera.y,
		player.rect.w / 2.66f,
		player.rect.h / 1.14f
	};

	

	PressedOnce(flashlightKey, flashlight) {


		//Get angle according to the mouse and player hitbox relative
		float angle = std::atan2(mouse.y - centerHitboxY, mouse.x - centerHitboxX);
		float newAngle = angle * 180 / M_PI;
		
		Direction dir = (newAngle > -45) ? Direction::RIGHT : Direction::LEFT;
		//Mouse raycast position
		SDL_FPoint endRaycast = {
			centerHitboxX + 200 * std::cos(angle - 0.25),
			centerHitboxY + 200 * std::sin(angle - 0.25)
		};

		SDL_FPoint endRaycast2 = {
			centerHitboxX + 200 * std::cos(angle + 0.25),
			centerHitboxY + 200 * std::sin(angle + 0.25)
		};


		SDL_Vertex Triangle[3] =
		{
			{
				{centerHitboxX, centerHitboxY },
				{0, 0, 0, 0xFF},
				{0.0f, 0.0f}
			},
			{
				{endRaycast.x, endRaycast.y },
				{0, 0, 0, 0xFF},
				{0.0f, 0.0f}
			},
			{
				{endRaycast2.x, endRaycast2.y },
				{0, 0, 0, 0xFF},
				{0.0f, 0.0f}
			}
		};

		SDL_RenderGeometry(renderer, NULL, Triangle, 3, NULL, 0);

		setDrawColor(255, 255, 255);
	}
	
    const Uint8* lastKeys = SDL_GetKeyboardState(NULL);
	memcpy(keysLastFrame, lastKeys, SDL_NUM_SCANCODES);

	
}



#pragma region FileSaves
#define BinaryWrite( class, data ) class . write(reinterpret_cast<const char*>(& data ), sizeof( data ))
#define BinaryCopy( class, mod ) class . read(reinterpret_cast<char*>( & mod ), sizeof( mod ))
#define ArraySize( array ) sizeof( array ) / sizeof( array [0] )


static void NewSettings() {
	using namespace std;
	fstream fout;

	fout.open("options", ios::out | ios::binary);
	if (!fout.is_open()) {
		errbox("Failed Write", "Failed opening file to write: 'options'. There is nothing we can do.");
		exit(0);
	}

	BinaryWrite(fout, Bindings);
	fout.close();
}




void Player::loadSettings() {
	using namespace std;
	fstream fileRead;

	fileRead.open("options", ios::in | ios::binary);
	if (!fileRead.is_open()) {
		infobox("Failed Read", "Failed opening file 'options'. Using default settings.");
		NewSettings();
		return;
	}


	const unsigned char bindCount = ArraySize(Bindings);
	int bindsFromFile[bindCount]{};
	BinaryCopy(fileRead, bindsFromFile);


	for (int i = 0; i < ArraySize(bindsFromFile); i++) {
		if (bindsFromFile[i] == NULL) {
			infobox("Failed Read", "Corrupt file 'options'. Using default settings");
			NewSettings();
			return;
		}
	}

	for (int i = 0; i < bindCount; i++) {
		Bindings[i] = bindsFromFile[i];
	}

	fileRead.close();
}
#pragma endregion