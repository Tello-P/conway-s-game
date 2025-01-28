#include <stdio.h>
#include <SDL2/SDL.h>

int main()
{
	printf("Hola mundo\n");
	
	SDL_Init(SDL_INIT_VIDEO);
	
	char* window_title = "Conway's game of life";
	int width = 900;
	int height = 600;
	
	SDL_CreateWindow(window_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height,0);
	SDL_Delay(5000);


	


}
