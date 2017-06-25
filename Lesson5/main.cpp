#include <SDL.h>
#include <stdio.h>
#include <string>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 200;

bool init();
bool loadMedia();
void close();
SDL_Surface* loadSurface(std::string path);

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gStrechedSurface = NULL;

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
				
				SDL_Rect stretchRect;
				stretchRect.x = 0;
				stretchRect.y = 0;
				stretchRect.w = SCREEN_WIDTH;
				stretchRect.h = SCREEN_HEIGHT;
				SDL_BlitScaled(gStrechedSurface, NULL, gScreenSurface, &stretchRect);

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
			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}
	return true;
}

bool loadMedia()
{
	gStrechedSurface = loadSurface("stretch.bmp");
	if (gStrechedSurface == NULL)
	{
		printf("failed to load streching image\n");
		return false;
	}
	return true;
}

void close()
{
	SDL_FreeSurface(gStrechedSurface);
	gStrechedSurface = NULL;

	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	SDL_Quit();
}

SDL_Surface* loadSurface(std::string path)
{
	SDL_Surface* optimizedSurface = NULL;

	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
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

