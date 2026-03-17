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
			printf("%i %s",get_map_value(state,j,i)," ");
		}
		printf("%i\n",get_map_value(state,state->size-1,i));
	}
}

void maj_coup(GameState* state, int joueur, int couleur)
{
	int c=0;
    for(int i = 0; i < state->size; i++)
    {
        for(int j = 0; j < state->size; j++)
        {
            if(get_map_value(state,j,i) == couleur)
            {
                if(j+1 < state->size && get_map_value(state,j+1,i) == joueur){
                    set_map_value(state,j,i,joueur);
					c++;}
					

                else if(j-1 >= 0 && get_map_value(state,j-1,i) == joueur){
                    set_map_value(state,j,i,joueur);
					c++;}

                else if(i+1 < state->size && get_map_value(state,j,i+1) == joueur){
                    set_map_value(state,j,i,joueur);
					c++;
				}

                else if(i-1 >= 0 && get_map_value(state,j,i-1) == joueur){
                    set_map_value(state,j,i,joueur);
					c++;}
            }
        }
    }
	if(c>0){
		maj_coup(state,joueur,couleur);
	}
}

int is_finish(GameState* state){

	int c1 = 0;
	int c2 = 0;
	int moitie;
	if(state->size%2==0){
		moitie = state->size*state->size/2;
	}
	else {
		moitie = state->size*state->size/2+1;
	}

	for(int i=0;i<state->size;i++)
	{
		for(int j=0;j<state->size;j++)
		{
			if(get_map_value(state,i,j)==1){
				c1++;
			}
			if(get_map_value(state,i,j)==1){
				c2++;
			}
		}
		
	}
	if(c1>= moitie){
		return 1;
	}

	if(c2>=moitie){
		return 2;
	}

	return 0;
}

int main(int argc, char** argv)
{
	
	GR8_create_empty_game_state(&state, 4);
	fill_map(&state);

	
	affiche(&state);
	set_map_value(&state,0,1,5);
	set_map_value(&state,1,2,5);
	set_map_value(&state,0,0,5);
	set_map_value(&state,1,1,5);
	set_map_value(&state,1,3,5);
	set_map_value(&state,0,2,5);
	maj_coup(&state,1,5);
	
	affiche(&state);
	printf("%i\n",is_finish(&state));
}


