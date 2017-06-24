#include <SDL.h>
#include <stdio.h>
#include <string>

enum KeyPressSurfaces
{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};

bool init();
bool loadMedia();
void close();

//load individual image
SDL_Surface* loadSurface(std::string path);

SDL_Window*  gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gKeyPressedSurfaces[KEY_PRESS_SURFACE_TOTAL];
SDL_Surface* gCurrentSurface = NULL;

const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 400;

int main(int argc, char* argv[])
{

	if (!init())
	{
		printf("failed to init SDL Error: %s\n", SDL_GetError());
	}
	else if (!loadMedia())
	{
		printf("failed to load media SDL Error: %s\n", SDL_GetError());
	}
	else
	{
		bool quit = false;
		SDL_Event e;

		gCurrentSurface = gKeyPressedSurfaces[KEY_PRESS_SURFACE_DEFAULT];

		while (!quit)
		{
			while (SDL_PollEvent(&e) != 0)
			{
				switch (e.type)
				{
				case SDL_QUIT:
					quit = true;
					break;

				case SDL_KEYDOWN:
					switch (e.key.keysym.sym)
					{
					case SDLK_UP:
						gCurrentSurface = gKeyPressedSurfaces[KEY_PRESS_SURFACE_UP];
						break;

					case SDLK_DOWN:
						gCurrentSurface = gKeyPressedSurfaces[KEY_PRESS_SURFACE_DOWN];
						break;

					case SDLK_LEFT:
						gCurrentSurface = gKeyPressedSurfaces[KEY_PRESS_SURFACE_LEFT];
						break;

					case SDLK_RIGHT:
						gCurrentSurface = gKeyPressedSurfaces[KEY_PRESS_SURFACE_RIGHT];
						break;

					default:
						gCurrentSurface = gKeyPressedSurfaces[KEY_PRESS_SURFACE_DEFAULT];
						break;
					}
				}
			}
			SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);
			SDL_UpdateWindowSurface(gWindow);
		}
	}

	close();
	return 0;
}

SDL_Surface* loadSurface(std::string path)
{
	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
	}
	return loadedSurface;
}

bool init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("could not initialize. error: %s\n", SDL_GetError());
		return false;
	}
	else
	{
		gWindow = SDL_CreateWindow("ma game!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("could not create a window. error: %s\n", SDL_GetError());
			return false;
		}
		else
		{
			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}
	return true;
}

bool loadMedia()
{
	
	gKeyPressedSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("default.bmp");
	if (gKeyPressedSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL)
	{
		printf("failed to load default image!\n");
		return false;
	}

	gKeyPressedSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("up.bmp");
	if (gKeyPressedSurfaces[KEY_PRESS_SURFACE_UP] == NULL)
	{
		printf("failed to load up image!\n");
		return false;
	}

	gKeyPressedSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("down.bmp");
	if (gKeyPressedSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL)
	{
		printf("failed to load down image!\n");
		return false;
	}

	gKeyPressedSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("left.bmp");
	if (gKeyPressedSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL)
	{
		printf("failed to load left image!\n");
		return false;
	}
	gKeyPressedSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("right.bmp");
	if (gKeyPressedSurfaces[KEY_PRESS_SURFACE_RIGHT] == NULL)
	{
		printf("failed to load right image!\n");
		return false;
	}
	return true;
}

void close()
{
	for (int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i)
	{
		SDL_FreeSurface(gKeyPressedSurfaces[i]);
		gKeyPressedSurfaces[i] = NULL;
	}

	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	SDL_Quit();
}