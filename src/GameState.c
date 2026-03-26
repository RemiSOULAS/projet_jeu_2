#include "../head/GameState.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

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
	printf("\n");
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

	int c=0;
	for(int i = 0; i < state->size; i++)
    {
        for(int j = 0; j < state->size; j++)
        {
            if(get_map_value(state,j,i) == 1)
            {
                if(j+1 < state->size && get_map_value(state,j+1,i) != 1 && get_map_value(state,j+1,i) != 2 ){
					c++;}
					

                else if(j-1 >= 0 && get_map_value(state,j-1,i) != 1 && get_map_value(state,j-1,i) != 2 ){
					c++;}

                else if(i+1 < state->size && get_map_value(state,j,i+1) != 1 && get_map_value(state,j,i+1) != 2 ){
					c++;
				}

                else if(i-1 >= 0 && get_map_value(state,j,i-1) != 1 && get_map_value(state,j,i-1) != 2 ){
					c++;}
            }
        }
    }
	if (c == 0){
		return 2; 
	}

	c=0;

	for(int i = 0; i < state->size; i++)
    {
        for(int j = 0; j < state->size; j++)
        {
            if(get_map_value(state,j,i) == 2)
            {
                if(j+1 < state->size && get_map_value(state,j+1,i) != 1 && get_map_value(state,j+1,i) != 2 ){
					c++;}
					

                else if(j-1 >=0 && get_map_value(state,j-1,i) != 1 && get_map_value(state,j-1,i) != 2 ){
					c++;}

                else if(i+1 < state->size && get_map_value(state,j,i+1) != 1 && get_map_value(state,j,i+1) != 2 ){
					c++;
				}

                else if(i-1 >=0 && get_map_value(state,j,i-1) != 1 && get_map_value(state,j,i-1) != 2 ){
					c++;}
            }
        }
    }
	if (c == 0){
		return 1; 
	}

	return 0;
}



void jouer_IA(int size, int(*f)(GameState*, int))
{
	GameState state = {.map = NULL, .size = 0};
	GR8_create_empty_game_state(&state,size);
	fill_map(&state);

	printf("La partie commence !\n");

	affiche(&state);

	int coup;
	while(is_finish(&state)==0)
	{
		printf("coup du joueur 1 : ");
		scanf("%i", &coup);	
		maj_coup(&state,1,coup);
		affiche(&state);
		if(is_finish(&state)!=0){
			break;
		}

		printf("L'IA joue : \n");
		maj_coup(&state,2,f(&state, 2));
		affiche(&state);
		
	}

	if(is_finish(&state)==1){
		printf("le joueur 1 a gagné !\n");
	}
	else{
		printf("le joueur 2 a gagné !\n");
	}
	
}
int IA_aleatoire(GameState* state, int num_joueur){
	
	int nb_color=7;
	int indice = (rand() % nb_color)+3;
	return indice;
}

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

int IA_aleatoire_mieux(GameState* state, int num_joueur){
	while(1){
		int nb_color=7;
		int indice = (rand() % nb_color)+3;
		if (is_adj(state, num_joueur, indice)==1){
		return indice;}
	}
}

GameState* copie_GS(GameState* state){

	
	GameState* copie = (GameState*)malloc(sizeof(GameState));

	copie->size=state->size;
	
	int size=copie->size;
	copie->map=(Color*) malloc(size*size*sizeof(Color));
	memcpy(copie->map, state->map, size*size*sizeof(Color) );

	return copie;

}

int eval_score(GameState* state, int num_joueur){
	int c=0;
	for(int i = 0; i < state->size; i++)
    {
        for(int j = 0; j < state->size; j++)
        {
            if(get_map_value(state,j,i) == num_joueur)
            {
                c++;
            }
        }
    }
	

    return c;
}


int IA_glouton(GameState* state, int num_joueur)
{
	int couleur=3;
	int score =0;
	for(int i=3; i<=9; i++){
		GameState* copie = copie_GS(state);
		maj_coup(copie,num_joueur,i);
		if(eval_score(copie,num_joueur)>score){
			couleur=i;
			score=eval_score(copie,num_joueur);
		}
		free(copie->map);
		free(copie);
	}
		
	
	
	return couleur;
}

int eval_front(GameState* state, int num_joueur){

	int c=0;
	for(int i = 0; i < state->size; i++)
    {
        for(int j = 0; j < state->size; j++)
        {
            if(get_map_value(state,j,i) == num_joueur)
            {
                if(j+1 < state->size && get_map_value(state,j+1,i) != 1 && get_map_value(state,j+1,i) != num_joueur ){
					c++;}
					

                if(j-1 >= 0 && get_map_value(state,j-1,i) != 1 && get_map_value(state,j-1,i) != num_joueur ){
					c++;}

                if(i+1 < state->size && get_map_value(state,j,i+1) != 1 && get_map_value(state,j,i+1) != num_joueur ){
					c++;
				}

                if(i-1 >= 0 && get_map_value(state,j,i-1) != 1 && get_map_value(state,j,i-1) != num_joueur ){
					c++;}
            }
        }
    }
	
    return c;

}

int IA_hegemonie(GameState* state, int num_joueur)
{
	int couleur=3;
	int frontiere =0;
	for(int i=3; i<=9; i++){
		GameState* copie = copie_GS(state);
		maj_coup(copie,num_joueur,i);
		if(eval_front(copie,num_joueur)>frontiere && is_adj(state, num_joueur, i)==1){
			couleur=i;
			frontiere=eval_front(copie,num_joueur);
		}
		free(copie->map);
		free(copie);
	}
		
	
	
	return couleur;
}

int IA_mixte(GameState* state, int num_joueur)
{
	int couleur=0;
	int frontiere =eval_front(state,num_joueur);
	for(int i=3; i<=9; i++){
		GameState* copie = copie_GS(state);
		maj_coup(copie,num_joueur,i);
		if(eval_front(copie,num_joueur)>frontiere){
			couleur=i;
			frontiere=eval_front(copie,num_joueur);
		}
		free(copie->map);
		free(copie);
	}
		
	if (couleur==0){
		int score =0;
	for(int i=3; i<=9; i++){
		GameState* copie = copie_GS(state);
		maj_coup(copie,num_joueur,i);
		if(eval_score(copie,num_joueur)>score){
			couleur=i;
			score=eval_score(copie,num_joueur);
		}
		free(copie->map);
		free(copie);
	}
	}
	
	return couleur;
}

void jouer_a_2(int size)
{
	GameState state = {.map = NULL, .size = 0};
	GR8_create_empty_game_state(&state,size);
	fill_map(&state);

	printf("La partie commence !\n");

	affiche(&state);

	int coup;
	while(is_finish(&state)==0)
	{
		printf("coup du joueur 1 : ");
		scanf("%i", &coup);	
		maj_coup(&state,1,coup);
		affiche(&state);
		if(is_finish(&state)!=0){
			break;
		}

		printf("coup du joueur 2 : ");
		scanf("%i", &coup);	
		maj_coup(&state,2,coup);
		affiche(&state);
		
	}

	if(is_finish(&state)==1){
		printf("le joueur 1 a gagné !\n");
	}
	else{
		printf("le joueur 2 a gagné !\n");
	}
	
}

int affrontement_IA(int size, int(*IA1)(GameState*, int),int(*IA2)(GameState*, int))
{
	GameState state = {.map = NULL, .size = 0};
	GR8_create_empty_game_state(&state,size);
	fill_map(&state);


	while(is_finish(&state)==0)
	{

		maj_coup(&state,1,IA1(&state, 1));
		if(is_finish(&state)!=0){
			break;
		}

		maj_coup(&state,2,IA2(&state, 2));
		
	}
	
	if(is_finish(&state)==1){
		return 1;
	}
	else{
		return 0;
	}
	
}

/*
int main(int argc, char** argv)
{
	
	GR8_create_empty_game_state(&state, 4);
	fill_map(&state);

	
	affiche(&state);
	set_map_value(&state,2,0,1);
	set_map_value(&state,2,1,1);
	set_map_value(&state,3,1,1);

	
	maj_coup(&state,1,5);
	
	affiche(&state);
	printf("%i\n",is_finish(&state));

}
*/
int main(int argc, char** argv)
{
	/*
	srand(time(NULL));
	int c=0;
	for(int i=1; i<=500; i++){
		c=c+affrontement_IA(8,IA_hegemonie,IA_hegemonie);
		
	}
	printf("%i\n",c);

	
	c=0;
	for(int i=1; i<=500; i++){
		c=c+affrontement_IA(15,IA_hegemonie,IA_hegemonie);
		
	}
	printf("%i\n",c);

	
	c=0;
	for(int i=1; i<=500; i++){
		c=c+affrontement_IA(30,IA_hegemonie,IA_hegemonie);
		
	}
	printf("%i\n",c);

	*/

	jouer_IA(10,IA_hegemonie);
	
	
	
}
