#include "../head/GameState.h"
#include <stdlib.h>
#include <stdio.h>
GameState state = {.map = NULL, .size = 0};
void create_empty_game_state (GameState* state, int size){}
void set_map_value (GameState* state, int x, int y, Color value){}
Color get_map_value (GameState* state, int x, int y){
	if (state -> map == NULL || x > state -> size || y > state -> size || x < 0 || y < 0)
	{
		printf("[ERROR] map not big enough or not initialized %p %i access (%i %i)", state -> map, state -> size, x, y);
		return ERROR;
	}
	return state -> map[y * state -> size + x];
}
void fill_map(GameState* map){}
int main(int argc, char** argv){
}

