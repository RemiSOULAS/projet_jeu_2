#include "../head/GameState.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int is_adj(GameState* state,int nb_joueur, int couleur)
{

	

	int c=0;
	for(int i = 0; i < state->size; i++)
    {
        for(int j = 0; j < state->size; j++)
        {
            if(get_map_value(state,j,i) == nb_joueur)
            {
                if(j+1 < state->size && get_map_value(state,j+1,i) != 1 && get_map_value(state,j+1,i) == couleur ){
					c++;}
					

                else if(j-1 >= 0 && get_map_value(state,j-1,i) != 1 && get_map_value(state,j-1,i) == couleur ){
					c++;}

                else if(i+1 < state->size && get_map_value(state,j,i+1) != 1 && get_map_value(state,j,i+1) == couleur ){
					c++;
				}

                else if(i-1 >= 0 && get_map_value(state,j,i-1) != 1 && get_map_value(state,j,i-1) == couleur ){
					c++;}
            }
        }
    }
	if (c == 0){
		return 0; 
	}

    return 1;

}