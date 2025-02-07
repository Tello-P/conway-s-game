#include <stdio.h>
#include <SDL2/SDL.h>

Uint32 COLOR_WHITE = 0xffffffff;
Uint32 COLOR_GRAY = 0x2f2f2f2f;
Uint32 COLOR_BLACK = 0x00000000;
int SURFACE_WIDTH = 900;
int SURFACE_HEIGHT = 600;
int CELL_WIDTH = 30;
int LINE_WIDTH = 2;

int draw_cell(SDL_Surface* surface, int cell_x, int cell_y, int cell_value)
{
	int pixel_x = cell_x * CELL_WIDTH;
	int pixel_y = cell_y * CELL_WIDTH;
	Uint32 color = cell_value == 0 ? COLOR_BLACK : COLOR_WHITE;

	SDL_Rect cell_rect = (SDL_Rect ){pixel_x, pixel_y, CELL_WIDTH,CELL_WIDTH};
	SDL_FillRect(surface, &cell_rect, color);
}

int draw_grid(SDL_Surface* surface, int columns, int rows)
{
	for(int i=0;i<rows;i++)
	{
		SDL_Rect line = (SDL_Rect) {0, i*CELL_WIDTH, SURFACE_WIDTH, LINE_WIDTH};
		SDL_FillRect(surface, &line, COLOR_GRAY);
	}

	for(int i=0;i<columns;i++)
	{
		SDL_Rect line = (SDL_Rect) {i*CELL_WIDTH, 0, LINE_WIDTH,SURFACE_HEIGHT};
		SDL_FillRect(surface, &line, COLOR_GRAY);
	}
}

void draw_game_matrix(SDL_Surface* surface, int rows, int columns, int* game_matrix)
{
	for(int i=0;i<rows;i++)
	{
		for(int j=0;j<columns;j++)
		{
			int cell_value = *(game_matrix + i*rows + j);
			draw_cell(surface, i, j, cell_value);
		}

	}
}



void initialize_game_matrix(int rows, int columns, int *game_matrix)
{
	for(int i=0;i<rows;i++)
	{
		for(int j=0;j<columns;j++)
		{
			*(game_matrix + i*rows + j) = rand() % 2;
		}
	}
}



int main()
{
	printf("Hola mundo\n");
	
	SDL_Init(SDL_INIT_VIDEO);
	
	char* window_title = "Conway's game of life";

	int columns = SURFACE_WIDTH / CELL_WIDTH;
	int rows = SURFACE_HEIGHT / CELL_WIDTH;
	
	SDL_Window* window = SDL_CreateWindow(window_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SURFACE_WIDTH, SURFACE_HEIGHT,0);
	
	SDL_Surface* surface = SDL_GetWindowSurface(window);

	int row_count = SURFACE_HEIGHT / CELL_WIDTH;
	int column_count = SURFACE_WIDTH / CELL_WIDTH;
	int game_matrix[row_count][column_count];
	initialize_game_matrix(row_count,column_count,game_matrix[0]);

	int cell_x = 10;
	int cell_y = 6;

	draw_game_matrix(surface, row_count, column_count, game_matrix[0]);
	draw_grid(surface, columns, rows);
	SDL_UpdateWindowSurface(window);
	SDL_Delay(5000);
	

}
