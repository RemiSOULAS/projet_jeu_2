#include "../head/GameState.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
GameState state = {.map = NULL, .size = 0};
void GR8_create_empty_game_state (GameState* state, int size)
{
	state->map=(Color*) malloc(size*size*sizeof(Color));
	state->size=size;
}
void set_map_value (GameState* state, int x, int y, Color value)
{
	state -> map[y * state -> size + x]=value;
}
Color get_map_value (GameState* state, int x, int y){
	if (state -> map == NULL || x > state -> size || y > state -> size || x < 0 || y < 0)
	{
		printf("[ERROR] map not big enough or not initialized %p %i access (%i %i)", state -> map, state -> size, x, y);
		return ERROR;
	}
	return state -> map[y * state -> size + x];
}

void fill_map(GameState* map)
{	
	srand(time(NULL));
	int nb_color=7;
	for(int i=0;i<=(map->size*map->size);i++)
	{
		int indice = (rand() % nb_color)+3;
		int y=i/(map->size);
		int x=i%(map->size);

		set_map_value(map,x,y,indice);
	
	}
	set_map_value(map,0,map->size-1,1);
	set_map_value(map,map->size-1,0,2);

}

void affiche(GameState* state)
{
	for(int i=0;i<state->size;i++)
	{
		for(int j=0;j<state->size-1;j++)
		{
			printf("%i",get_map_value(state,j,i));
		}
		printf("%i\n",get_map_value(state,state->size-1,i));
	}
}
int main(int argc, char** argv)
{
	
	GR8_create_empty_game_state(&state, 4);
	fill_map(&state);
	//int test=get_map_value(&state,0,2);
	//printf("%i\n",test);
	affiche(&state);
}


