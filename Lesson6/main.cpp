#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 400;

bool init();
bool loadMedia();
void close();
SDL_Surface* loadSurface(std::string path);

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gPNGSurface = NULL;

int main(int argc, char* argv[])
{
	if (!init())
	{
		printf("failed to init\n");
	}
	else
	{
		if (!loadMedia())
		{
			printf("failed to load media\n");
		}
		else
		{
			bool quit = false;

			SDL_Event ev;

			while (!quit)
			{
				// event handling
				while (SDL_PollEvent(&ev) != 0)
				{
					if (ev.type == SDL_QUIT)
					{
						quit = true;
					}
				}
				
				SDL_BlitSurface(gPNGSurface, NULL, gScreenSurface, NULL);

				SDL_UpdateWindowSurface(gWindow);
			}

		}
	}
	close();
	return 0;
}


bool init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not init. SDL error: %s\n", SDL_GetError());
		return false;
	}
	else
	{
		gWindow = SDL_CreateWindow("mai geim", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("window could not be created. SDL error: %s\n", SDL_GetError());
			return false;
		}
		else
		{
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags))
			{
				printf("sdl_image could not init. sdl_image error: %s\n", IMG_GetError());
				return false;
			}
			else
			{
				gScreenSurface = SDL_GetWindowSurface(gWindow);
			}
		}
	}
	return true;
}

bool loadMedia()
{
	gPNGSurface = loadSurface("loaded.png");
	if (gPNGSurface == NULL)
	{
		printf("failed to load streching image\n");
		return false;
	}
	return true;
}

void close()
{
	SDL_FreeSurface(gPNGSurface);
	gPNGSurface = NULL;

	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	IMG_Quit();
	SDL_Quit();
}

SDL_Surface* loadSurface(std::string path)
{
	SDL_Surface* optimizedSurface = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("unable to load image %s. SDL error: %s\n", path.c_str(), SDL_GetError());
	}
	else
	{
		optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, NULL);
		if (optimizedSurface == NULL)
		{
			printf("unable to optimize image %s. SDL error: %s\n", path.c_str(), SDL_GetError());
		}

		SDL_FreeSurface(loadedSurface);
	}
	return optimizedSurface;
}

