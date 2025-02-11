#include <stdio.h>
#include <SDL2/SDL.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

Uint32 COLOR_WHITE = 0xffffffff;
Uint32 COLOR_GRAY = 0x2f2f2f2f;
Uint32 COLOR_BLACK = 0x00000000;
Uint32 COLOR_RED = 0xb81414;
int SURFACE_WIDTH = 900;
int SURFACE_HEIGHT = 600;
int CELL_WIDTH = 20;
int LINE_WIDTH = 2;

//::::::::::::::::::::::::::::::::::::::::
int draw_cell(SDL_Surface* surface, int cell_x, int cell_y, int cell_value)
{
	int pixel_x = cell_x * CELL_WIDTH;
	int pixel_y = cell_y * CELL_WIDTH;
	Uint32 color = cell_value == 0 ? COLOR_BLACK : COLOR_WHITE;

	SDL_Rect cell_rect = (SDL_Rect ){pixel_x, pixel_y, CELL_WIDTH,CELL_WIDTH};
	SDL_FillRect(surface, &cell_rect, color);
}

//::::::::::::::::::::::::::::::::::::::::
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

//::::::::::::::::::::::::::::::::::::::::::
void draw_game_matrix(SDL_Surface* surface, int rows, int columns, int* game_matrix)
{
	for(int i=0;i<rows;i++)
	{
		for(int j=0;j<columns;j++)
		{
			int cell_value = game_matrix[j + columns * i];
			draw_cell(surface, j, i, cell_value);
		}

	}
}

//::::::::::::::::::::::::::::::::::::::::::::::
void randomize_game_matrix(int rows, int columns, int *game_matrix)
{
	for(int i=0;i<rows;i++)
	{
		for(int j=0;j<columns;j++)
		{
			game_matrix[j + columns * i] = (rand() % 2);
			//*(game_matrix + i*columns + j) = rand() % 2;
		}
	}
}

//:::::::::::::::::::::::::::::::::::::::::::::::
void blank_game_matrix(int rows, int columns, int *game_matrix)
{
	for(int i=0;i<rows;i++)
	{
		for(int j=0;j<columns;j++)
		{
			game_matrix[j + columns * i] = 0;
			//*(game_matrix + i*columns + j) = rand() % 2;
		}
	}
}

//::::::::::::::::::::::::::::::::::::::::::::::
int count_neighbors(int i, int j, int row_count, int column_count, int game_matrix[])
{
	
	int neighbor_counter = 0;
	// lefthand neighbor
	if (j > 0)
		neighbor_counter += game_matrix[j-1 + column_count * i];
	// righthand neighbor
	if (j < (column_count))
		neighbor_counter += game_matrix[j+1 + column_count * i];
	// above neighbor
	if (i > 0)
		neighbor_counter += game_matrix[j + column_count * (i-1)];
	// above left neighbor
	if ( i> 0 && j > 0)
		neighbor_counter += game_matrix[j-1 + column_count * (i-1)];
	// above right neighbor
	if ( i > 0 && j < (column_count))
		neighbor_counter += game_matrix[j+1 + column_count * (i-1)];
	// below neighbor
	if (i < (row_count))
		neighbor_counter += game_matrix[j + column_count * (i+1)];
	// below left neighbor
	if ( i < (row_count) && j > 0)
		neighbor_counter += game_matrix[j-1 + column_count * (i+1)];
	// below right neighbor
	if ( i < (row_count) && j < (column_count))
		neighbor_counter += game_matrix[j+1 + column_count * (i+1)];
	 
	return neighbor_counter;	
}

//:::::::::::::::::::::::::::::::::::::::::::::::::::
void simulation_step(int rows, int columns, int game_matrix[])
{	
	int next_game_matrix[rows*columns];

	for(int i=0;i<rows;i++)
	{
		for(int j=0;j<columns;j++)
		{
			int neighbor_count = count_neighbors(i,j,rows,columns,game_matrix);
			// perform logic based on neighbor count
			int current_cell_value = game_matrix[j + columns*i];
			
			// rule 1
			if (current_cell_value != 0 && neighbor_count <  2)
			{
				next_game_matrix[j + columns*i] = 0;
			}
			// rule 2
			else if (current_cell_value != 0 && (neighbor_count == 2 || neighbor_count == 3))
			{
				next_game_matrix[j + columns*i] = 1;
			}
			// rule 3
			else if (current_cell_value != 0 && neighbor_count > 3)
			{
				next_game_matrix[j + columns*i] = 0;
			}
			// rule 4
			else if (current_cell_value == 0 && neighbor_count == 3)
			{
				next_game_matrix[j + columns*i] = 1;
			}
			else
			{
				next_game_matrix[j + columns*i] = current_cell_value;
			}
		}
	}

	for (int i=0; i<rows*columns; i++)
	{
		game_matrix[i] = next_game_matrix[i];
	}
}

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::
void set_cell_in_game_matrix_on(Sint32 mouse_x, Sint32 mouse_y, int rows, int columns, int game_matrix[])
{
	int j = mouse_x / CELL_WIDTH;
	int i = mouse_y / CELL_WIDTH;
	game_matrix[j + columns*i] = 1;//!game_matrix[j + columns*i];

}

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::
void set_cell_in_game_matrix_off(Sint32 mouse_x, Sint32 mouse_y, int rows, int columns, int game_matrix[])
{
	int j = mouse_x / CELL_WIDTH;
	int i = mouse_y / CELL_WIDTH;
	game_matrix[j + columns*i] = 0;//!game_matrix[j + columns*i];

}

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::
void draw_waiting(SDL_Surface* surface)
{
	
	
	SDL_Rect pause_block1 = (SDL_Rect) {0,0,10,20};
	SDL_FillRect(surface, &pause_block1, COLOR_WHITE);
	
	SDL_Rect pause_block2 = (SDL_Rect) {15,0,10,20};
	SDL_FillRect(surface, &pause_block2, COLOR_WHITE);
	
}

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::
void draw_erase(SDL_Surface* surface)
{
	
	
	SDL_Rect erase_block = (SDL_Rect) {SURFACE_WIDTH-30, 0,20,20};
	SDL_FillRect(surface, &erase_block, COLOR_RED);
		
}



//#·#·#·#·#·#·#·#·#·#·#·#·#·#·#·#·#·#·#·#·#·#·#·#·#·#
int main(int argc, char* argv[])
{	
	if (argc > 1) 
	{
        	if(strcmp(argv[1],"--help") == 0)
		{
			printf("HELP MENU.............................\n");
			printf("\n	First argument is cell width\n");
			printf("	The higher, the less cells are\n");
			printf("Example of usage:\n");
			printf("	./gol 10\n	./gol 19\n");
			printf("	Argument --keys for usage\n\n");

			return 1;
		}
		else if(strcmp(argv[1],"--keys") == 0)
		{	
			printf("KEY MENU.......................................\n");
			printf("	SPACE............Start/Stop time\n");
			printf("	BACKSPACE........Remove all cells\n");
			printf("	SHIFT............Start/Stop erase mode\n");
			printf("	ENTER............Random cell generation\n\n");
			return 1;
		}
		else
		{
			CELL_WIDTH = atoi(argv[1]);
			if (CELL_WIDTH < 5 || CELL_WIDTH > 100)
			{
				printf("Error in cell width value, please use a number greater than 5 and lower than 100");
			return 1;
			}
  		}
	}
	else
	{
        CELL_WIDTH = 15; // default
    	}
	


	
	SDL_Init(SDL_INIT_VIDEO);
	
	char* window_title = "Conway's game of life";
	// Seeding de random number generator
	srand(time(NULL));
	int columns = SURFACE_WIDTH / CELL_WIDTH;
	int rows = SURFACE_HEIGHT / CELL_WIDTH;
	
	SDL_Window* window = SDL_CreateWindow(window_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SURFACE_WIDTH, SURFACE_HEIGHT,0);
	
	SDL_Surface* surface = SDL_GetWindowSurface(window);

	int row_count = SURFACE_HEIGHT / CELL_WIDTH;
	int column_count = SURFACE_WIDTH / CELL_WIDTH;
	int game_matrix[row_count * column_count];

	int cell_x = 10;
	int cell_y = 6;

	
	randomize_game_matrix(row_count,column_count,game_matrix);
	draw_game_matrix(surface, row_count, column_count, game_matrix);
	draw_grid(surface, columns, rows);
	SDL_UpdateWindowSurface(window);

	int game_loop = 1;
	int simulation_paused = 1;
	int insert_mode = 1;
	int erase_mode = 0;
	// running, waiting, erasing
	
	SDL_Event event;
	while(game_loop)
	{
		while(SDL_PollEvent(&event))
		{
		
			
			if (simulation_paused == 1)
			{
				draw_waiting(surface);
				SDL_UpdateWindowSurface(window);
			}

			if(event.type == SDL_QUIT)
			{
				game_loop = 0;
			}
			
			else if(event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_SPACE)
				{
					simulation_paused = !simulation_paused;
					if (simulation_paused == 1)
					{
						draw_waiting(surface);
						SDL_UpdateWindowSurface(window);
					}
					if (erase_mode == 1)
					{
						draw_erase(surface);	
						SDL_UpdateWindowSurface(window);
					}
				}
				if (event.key.keysym.sym == SDLK_RETURN)
				{
					randomize_game_matrix(row_count, column_count, game_matrix);
					draw_game_matrix(surface, row_count, column_count, game_matrix);
					draw_grid(surface, columns, rows);
					if (simulation_paused == 1)
					{
						draw_waiting(surface);
					}
					if (erase_mode == 1)
					{
						draw_erase(surface);
					}
					SDL_UpdateWindowSurface(window);
				}
				if (event.key.keysym.sym == SDLK_BACKSPACE)
				{
					blank_game_matrix(row_count, column_count, game_matrix);
					draw_game_matrix(surface, row_count, column_count, game_matrix);
					draw_grid(surface, columns, rows);
					if (simulation_paused == 1)
					{
						draw_waiting(surface);
					}
					if (erase_mode == 1)
					{
						draw_erase(surface);
					}
					SDL_UpdateWindowSurface(window);

				}	
				if (event.key.keysym.sym == SDLK_LSHIFT)
				{
					insert_mode = !insert_mode;
					erase_mode = !erase_mode;
					if (simulation_paused == 1)
					{
						draw_waiting(surface);
						SDL_UpdateWindowSurface(window);
					}
					if (erase_mode == 1)
					{
						draw_erase(surface);
						SDL_UpdateWindowSurface(window);
					}
					SDL_UpdateWindowSurface(window);
				}

			}

			if (insert_mode == 1 && erase_mode == 0)
			{	
				SDL_UpdateWindowSurface(window);
				draw_game_matrix(surface, row_count, column_count, game_matrix);
				draw_grid(surface, columns, rows);


				if (event.type == SDL_MOUSEMOTION)
				{
					if (event.motion.state != 0)
					{
						Sint32 mouse_x = event.motion.x;
						Sint32 mouse_y = event.motion.y;
						set_cell_in_game_matrix_on(mouse_x, mouse_y, row_count, column_count, game_matrix);	
						draw_game_matrix(surface, row_count, column_count, game_matrix);
						draw_grid(surface, columns, rows);
					
						if (simulation_paused == 1)
						{
							draw_waiting(surface);
						}
						
						SDL_UpdateWindowSurface(window);
					}
				}
				else if (event.type == SDL_MOUSEBUTTONDOWN)
				{
				
					Sint32 mouse_x = event.button.x;
					Sint32 mouse_y = event.button.y;
					set_cell_in_game_matrix_on(mouse_x, mouse_y, row_count, column_count, game_matrix);	
					draw_game_matrix(surface, row_count, column_count, game_matrix);
					draw_grid(surface, columns, rows);
				
					if (simulation_paused == 1)
					{
						draw_waiting(surface);
					}
					SDL_UpdateWindowSurface(window);
				}

			}
			else if (insert_mode == 0 && erase_mode == 1)
			{
				if (event.type == SDL_MOUSEMOTION)
				{
					if (event.motion.state != 0)
					{
						Sint32 mouse_x = event.motion.x;
						Sint32 mouse_y = event.motion.y;
						set_cell_in_game_matrix_off(mouse_x, mouse_y, row_count, column_count, game_matrix);	
						draw_game_matrix(surface, row_count, column_count, game_matrix);
						draw_grid(surface, columns, rows);
					
						if (simulation_paused == 1)
						{
							draw_waiting(surface);
						}
						if (erase_mode == 1)
						{
							draw_erase(surface);
						}
						SDL_UpdateWindowSurface(window);
					}
				}
				else if (event.type == SDL_MOUSEBUTTONDOWN)
				{
				
					Sint32 mouse_x = event.button.x;
					Sint32 mouse_y = event.button.y;
					set_cell_in_game_matrix_off(mouse_x, mouse_y, row_count, column_count, game_matrix);	
					draw_game_matrix(surface, row_count, column_count, game_matrix);
					draw_grid(surface, columns, rows);
					
					if (simulation_paused == 1)
					{
						draw_waiting(surface);
					}
					if (erase_mode == 1)
					{
						draw_erase(surface);
					}
					SDL_UpdateWindowSurface(window);
				}	
			}
			
		}
		if (!simulation_paused)
		{
			simulation_step(row_count, column_count, game_matrix);		
			draw_game_matrix(surface, row_count, column_count, game_matrix);
			draw_grid(surface, columns, rows);
			SDL_UpdateWindowSurface(window);
			SDL_Delay(100);

		}
		else
		{
			SDL_Delay(100);
		}


		
	}
	

}
