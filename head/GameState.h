#ifndef GAME_STATE_H
#define GAME_STATE_H

typedef enum Color{
	ERROR = -1,
	EMPTY,
	PLAYER_1,
	PLAYER_2,
	RED,
	GREEN,
	BLUE,
	YELLOW,
	MAGENTA,
	CYAN,
	WHITE
}Color; 

typedef struct GameState{
	Color* map;
	int size;
} GameState;


void GR8_create_empty_game_state (GameState* state, int size);
void GR8_set_map_value (GameState* state, int x, int y, Color value);
Color GR8_get_map_value (GameState* state, int x, int y);
void GR8_fill_map(GameState* state);
int main(int argc, char** argv);
#endif