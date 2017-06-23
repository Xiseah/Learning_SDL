#include <SDL.h>
#include <stdio.h>

bool init();
bool loadMedia();
void close();

SDL_Window*  gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gHelloWorld = NULL;

const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 400;

int main(int argc, char* argv[])
{
	
	if (!init()) 
	{ 
		printf("failed to init\n"); 
	}
	else if (!loadMedia()) 
	{ 
		printf("failed to load media\n"); 
	}
	else
	{
		SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);
		SDL_UpdateWindowSurface(gWindow);
		SDL_Delay(3000);
	}

	close();
	return 0;
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
			printf("could not create a window. error: %s\n", SDL_GetError);
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
	gHelloWorld = SDL_LoadBMP("hello_world.bmp");
	if (gHelloWorld == NULL)
	{
		printf("could not load image. error: %s\n", SDL_GetError());
		return false;
	}
	return true;
}

void close()
{
	SDL_FreeSurface(gHelloWorld);
	gHelloWorld = NULL;

	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	SDL_Quit();
}