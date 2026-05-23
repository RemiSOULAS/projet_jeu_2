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
void GR8_set_map_value (GameState* state, int x, int y, Color value)
{
	state -> map[y * state -> size + x]=value;
}
Color GR8_get_map_value (GameState* state, int x, int y){
	if (state -> map == NULL || x > state -> size || y > state -> size || x < 0 || y < 0)
	{
		printf("[ERROR] map not big enough or not initialized %p %i access (%i %i)", state -> map, state -> size, x, y);
		return ERROR;
	}
	return state -> map[y * state -> size + x];
}

void GR8_fill_map(GameState* map)
{	
	
	int nb_color=7;
	for(int i=0;i<=(map->size*map->size);i++)
	{
		int indice = (rand() % nb_color)+3;
		int y=i/(map->size);
		int x=i%(map->size);

		GR8_set_map_value(map,x,y,indice);
	
	}
	GR8_set_map_value(map,0,map->size-1,1);
	GR8_set_map_value(map,map->size-1,0,2);

}

void GR8_affiche(GameState* state)
{
	for(int i=0;i<state->size;i++)
	{
		for(int j=0;j<state->size-1;j++)
		{
			printf("%i %s",GR8_get_map_value(state,j,i)," ");
		}
		printf("%i\n",GR8_get_map_value(state,state->size-1,i));
	}
	printf("\n");
}

void GR8_maj_coup(GameState* state, int joueur, int couleur)
{
	int c=0;
    for(int i = 0; i < state->size; i++)
    {
        for(int j = 0; j < state->size; j++)
        {
            if(GR8_get_map_value(state,j,i) == couleur)
            {
                if(j+1 < state->size && GR8_get_map_value(state,j+1,i) == joueur){
                    GR8_set_map_value(state,j,i,joueur);
					c++;}
					

                else if(j-1 >= 0 && GR8_get_map_value(state,j-1,i) == joueur){
                    GR8_set_map_value(state,j,i,joueur);
					c++;}

                else if(i+1 < state->size && GR8_get_map_value(state,j,i+1) == joueur){
                    GR8_set_map_value(state,j,i,joueur);
					c++;
				}

                else if(i-1 >= 0 && GR8_get_map_value(state,j,i-1) == joueur){
                    GR8_set_map_value(state,j,i,joueur);
					c++;}
            }
        }
    }
	if(c>0){
		GR8_maj_coup(state,joueur,couleur);
	}
}

int GR8_is_finish(GameState* state){

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
			if(GR8_get_map_value(state,i,j)==1){
				c1++;
			}
			if(GR8_get_map_value(state,i,j)==2){
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
            if(GR8_get_map_value(state,j,i) == 1)
            {
                if(j+1 < state->size && GR8_get_map_value(state,j+1,i) != 1 && GR8_get_map_value(state,j+1,i) != 2 ){
					c++;}
					

                else if(j-1 >= 0 && GR8_get_map_value(state,j-1,i) != 1 && GR8_get_map_value(state,j-1,i) != 2 ){
					c++;}

                else if(i+1 < state->size && GR8_get_map_value(state,j,i+1) != 1 && GR8_get_map_value(state,j,i+1) != 2 ){
					c++;
				}

                else if(i-1 >= 0 && GR8_get_map_value(state,j,i-1) != 1 && GR8_get_map_value(state,j,i-1) != 2 ){
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
            if(GR8_get_map_value(state,j,i) == 2)
            {
                if(j+1 < state->size && GR8_get_map_value(state,j+1,i) != 1 && GR8_get_map_value(state,j+1,i) != 2 ){
					c++;}
					

                else if(j-1 >=0 && GR8_get_map_value(state,j-1,i) != 1 && GR8_get_map_value(state,j-1,i) != 2 ){
					c++;}

                else if(i+1 < state->size && GR8_get_map_value(state,j,i+1) != 1 && GR8_get_map_value(state,j,i+1) != 2 ){
					c++;
				}

                else if(i-1 >=0 && GR8_get_map_value(state,j,i-1) != 1 && GR8_get_map_value(state,j,i-1) != 2 ){
					c++;}
            }
        }
    }
	if (c == 0){
		return 1; 
	}

	return 0;
}



void GR8_Jouer_IA(int size, int(*f)(GameState*, int))
{
	GameState state = {.map = NULL, .size = 0};
	GR8_create_empty_game_state(&state,size);
	GR8_fill_map(&state);

	printf("La partie commence !\n");

	GR8_affiche(&state);

	int coup;
	while(GR8_is_finish(&state)==0)
	{
		printf("coup du joueur 1 : ");
		scanf("%i", &coup);	
		GR8_maj_coup(&state,1,coup);
		GR8_affiche(&state);
		if(GR8_is_finish(&state)!=0){
			break;
		}

		printf("L'IA joue : \n");
		GR8_maj_coup(&state,2,f(&state, 2));
		GR8_affiche(&state);
		
	}

	if(GR8_is_finish(&state)==1){
		printf("le joueur 1 a gagné !\n");
	}
	else{
		printf("le joueur 2 a gagné !\n");
	}
	
}
int GR8_IA_aleatoire(GameState* state, int num_joueur){
	
	int nb_color=7;
	int indice = (rand() % nb_color)+3;
	return indice;
}

int GR8_is_adj(GameState* state,int nb_joueur, int couleur)
{

	

	int c=0;
	for(int i = 0; i < state->size; i++)
    {
        for(int j = 0; j < state->size; j++)
        {
            if(GR8_get_map_value(state,j,i) == nb_joueur)
            {
                if(j+1 < state->size && GR8_get_map_value(state,j+1,i) != 1 && GR8_get_map_value(state,j+1,i) == couleur ){
					c++;}
					

                else if(j-1 >= 0 && GR8_get_map_value(state,j-1,i) != 1 && GR8_get_map_value(state,j-1,i) == couleur ){
					c++;}

                else if(i+1 < state->size && GR8_get_map_value(state,j,i+1) != 1 && GR8_get_map_value(state,j,i+1) == couleur ){
					c++;
				}

                else if(i-1 >= 0 && GR8_get_map_value(state,j,i-1) != 1 && GR8_get_map_value(state,j,i-1) == couleur ){
					c++;}
            }
        }
    }
	if (c == 0){
		return 0; 
	}

    return 1;

}

int GR8_IA_aleatoire_mieux(GameState* state, int num_joueur){
	while(1){
		int nb_color=7;
		int indice = (rand() % nb_color)+3;
		if (GR8_is_adj(state, num_joueur, indice)==1){
		return indice;}
	}
}

GameState* GR8_copie_GS(GameState* state){

	
	GameState* copie = (GameState*)malloc(sizeof(GameState));

	copie->size=state->size;
	
	int size=copie->size;
	copie->map=(Color*) malloc(size*size*sizeof(Color));
	memcpy(copie->map, state->map, size*size*sizeof(Color) );

	return copie;

}

int GR8_eval_score(GameState* state, int num_joueur){
	int c=0;
	for(int i = 0; i < state->size; i++)
    {
        for(int j = 0; j < state->size; j++)
        {
            if(GR8_get_map_value(state,j,i) == num_joueur)
            {
                c++;
            }
        }
    }
	

    return c;
}


int GR8_IA_glouton(GameState* state, int num_joueur)
{
	int couleur=3;
	int score =0;
	for(int i=3; i<=9; i++){
		GameState* copie = GR8_copie_GS(state);
		GR8_maj_coup(copie,num_joueur,i);
		if(GR8_eval_score(copie,num_joueur)>score){
			couleur=i;
			score=GR8_eval_score(copie,num_joueur);
		}
		free(copie->map);
		free(copie);
	}
		
	
	
	return couleur;
}

int GR8_eval_front(GameState* state, int num_joueur){

	int c=0;
	for(int i = 0; i < state->size; i++)
    {
        for(int j = 0; j < state->size; j++)
        {
            if(GR8_get_map_value(state,j,i) == num_joueur)
            {
                if(j+1 < state->size &&  GR8_get_map_value(state,j+1,i) != num_joueur ){
					c++;}
					

                if(j-1 >= 0  && GR8_get_map_value(state,j-1,i) != num_joueur ){
					c++;}

                if(i+1 < state->size  && GR8_get_map_value(state,j,i+1) != num_joueur ){
					c++;
				}

                if(i-1 >= 0  && GR8_get_map_value(state,j,i-1) != num_joueur ){
					c++;}
            }
        }
    }
	
    return c;

}

int GR8_IA_hegemonie(GameState* state, int num_joueur)
{
	int couleur=3;
	int frontiere =0;
	for(int i=3; i<=9; i++){
		GameState* copie = GR8_copie_GS(state);
		GR8_maj_coup(copie,num_joueur,i);
		if(GR8_eval_front(copie,num_joueur)>frontiere && GR8_is_adj(state, num_joueur, i)==1){
			couleur=i;
			frontiere=GR8_eval_front(copie,num_joueur);
		}
		free(copie->map);
		free(copie);
	}
		
	
	
	return couleur;
}

int GR8_IA_mixte(GameState* state, int num_joueur)
{
	int couleur=0;
	int frontiere =GR8_eval_front(state,num_joueur);
	for(int i=3; i<=9; i++){
		GameState* copie = GR8_copie_GS(state);
		GR8_maj_coup(copie,num_joueur,i);
		if(GR8_eval_front(copie,num_joueur)>frontiere){
			couleur=i;
			frontiere=GR8_eval_front(copie,num_joueur);
		}
		free(copie->map);
		free(copie);
	}
		
	if (couleur==0){
		int score =0;
	for(int i=3; i<=9; i++){
		GameState* copie = GR8_copie_GS(state);
		GR8_maj_coup(copie,num_joueur,i);
		if(GR8_eval_score(copie,num_joueur)>score){
			couleur=i;
			score=GR8_eval_score(copie,num_joueur);
		}
		free(copie->map);
		free(copie);
	}
	}
	
	return couleur;
}

void GR8_jouer_a_2(int size)
{
	GameState state = {.map = NULL, .size = 0};
	GR8_create_empty_game_state(&state,size);
	GR8_fill_map(&state);

	printf("La partie commence !\n");

	GR8_affiche(&state);

	int coup;
	while(GR8_is_finish(&state)==0)
	{
		printf("coup du joueur 1 : ");
		scanf("%i", &coup);	
		GR8_maj_coup(&state,1,coup);
		GR8_affiche(&state);
		if(GR8_is_finish(&state)!=0){
			break;
		}

		printf("coup du joueur 2 : ");
		scanf("%i", &coup);	
		GR8_maj_coup(&state,2,coup);
		GR8_affiche(&state);
		
	}

	if(GR8_is_finish(&state)==1){
		printf("le joueur 1 a gagné !\n");
	}
	else{
		printf("le joueur 2 a gagné !\n");
	}
	
}

int GR8_affrontement_IA(int size, int(*IA1)(GameState*, int),int(*IA2)(GameState*, int))
{
	GameState state = {.map = NULL, .size = 0};
	GR8_create_empty_game_state(&state,size);
	GR8_fill_map(&state);


	while(GR8_is_finish(&state)==0)
	{

		GR8_maj_coup(&state,1,IA1(&state, 1));
		if(GR8_is_finish(&state)!=0){
			break;
		}

		GR8_maj_coup(&state,2,IA2(&state, 2));
		
	}
	
	if(GR8_is_finish(&state)==1){
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
	GR8_fill_map(&state);

	
	GR8_affiche(&state);
	GR8_set_map_value(&state,2,0,1);
	GR8_set_map_value(&state,2,1,1);
	GR8_set_map_value(&state,3,1,1);

	
	GR8_maj_coup(&state,1,5);
	
	GR8_affiche(&state);
	printf("%i\n",GR8_is_finish(&state));

}
*/
int main(int argc, char** argv)
{
	
	srand(time(NULL));
	int c=0;
	for(int i=1; i<=500; i++){
		c=c+GR8_affrontement_IA(8,GR8_IA_mixte,GR8_IA_mixte);
		
	}
	printf("%i\n",c);

	 c=0;
	for(int i=1; i<=500; i++){
		c=c+GR8_affrontement_IA(15,GR8_IA_mixte,GR8_IA_mixte);
		
	}

	printf("%i\n",c);

	 c=0;
	for(int i=1; i<=500; i++){
		c=c+GR8_affrontement_IA(30,GR8_IA_mixte,GR8_IA_mixte);
		
	}
	printf("%i\n",c);
	/*
	c=c+250;
	for(int i=1; i<=250; i++){
		c=c-GR8_affrontement_IA(8,GR8_IA_mixte,GR8_IA_glouton);
		
	}
	printf("%i\n",c);

	
	c=0;
	
	for(int i=1; i<=250; i++){
		c=c+GR8_affrontement_IA(15,GR8_IA_glouton,GR8_IA_mixte);
		
	}
	
	c=c+250;
	for(int i=1; i<=250; i++){
		c=c-GR8_affrontement_IA(15,GR8_IA_mixte,GR8_IA_glouton);
		
	}
		
	printf("%i\n",c);

	
	c=0;
	for(int i=1; i<=250; i++){
		c=c+GR8_affrontement_IA(30,GR8_IA_glouton,GR8_IA_mixte);
		
	}
	c=c+250;
	for(int i=1; i<=250; i++){
		c=c-GR8_affrontement_IA(30,GR8_IA_mixte,GR8_IA_glouton);
		
	}
	printf("%i\n",c);
*/
	

}
