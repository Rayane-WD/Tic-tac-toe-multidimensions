#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "grid.h"
#include "extra.h"


void initializeGrid(char tab[], int size){
  /* Permet d'initialiser la ou les grilles de morpion.
   	tab -> grille de jeu (vide)
	taille -> taille de la grille de jeu
  */


	for (int i=0; i < size; i++){
		tab[i] = '.';
	}
}



void displayGrid(char tab[], int edge_len, int dimension){
  /* Permet d'afficher la ou les grilles.

   tab -> grille de jeu
   edge_len -> nombre de lignes (et de colonnes) de la grille de jeu
   dimension -> dimension de la grille

  */
  char separator = '|'; //séparateur des tokens
  char scount[10];
  char count = 1; // variable suivant le compte des grilles


  if(dimension == 2){

    //On affiche le tableau de référence
    puts("\nGrille de référence  \n");
    for (int i = 1; i <= pow(edge_len, dimension); i++){

      if (i<10){sprintf(scount, " %d", i);}
      if (i>=10){sprintf(scount, "%d", i);}

      if (i%edge_len == 0){separator = '\n';}
        printf(" %s %c", scount, separator);
        separator = '|';
    }
    puts("\n");


    //On affiche le tableau de jeu
    puts("Grille de jeu  \n");
    //On parcourt le tableau
    for (int i = 1; i <= pow(edge_len, dimension); i++){

      char token = tab[i-1]; //On recupere le token
      if (i%edge_len == 0){separator = '\n';} //Tout les edge_len on saute une ligne
        printf(" %c %c", token, separator); //On affiche le token avec son séparateur
        separator = '|'; //Le séparateur reprends sa valeur d'origine
    }
    puts("\n");
  }

  //--------------------------------------------------------

  else if(dimension == 3){
    //On parcourt le tableau par colonne puis par ligne
    for( int i = 1; i <= pow(edge_len, dimension); i++ ){

		char token = tab[i-1]; //On recupere le token
		separator='|';

		//Tout les edge_len on saute une ligne
		if (i%(edge_len) == 0){
			separator = '\n'; //Saut de ligne
		}
		//Tout les edge_len^2 on saute deux lignes
		if (i%(edge_len*edge_len) == 1 && i!=1){
			puts("\n");
		}
		//Tout les edge_len^2 on affiche le numéro de plan
		if (i%(edge_len*edge_len) == edge_len ){
			sprintf(scount, "    %d", count); //Affichage du numéro du carré et attribuer valeur y à count
			count++;
		}

        printf("%c%s%c", token, scount,separator); //On affiche la ligne
        sprintf(scount, "%s", ""); //on ré attribue à count une valeur vide


    }

  }

  //--------------------------------------------------------

  else if(dimension == 4){
	  char letter = 65;
	//On parcourt chaque cube(=building) un par un
	//On parcourt le tableau par colonne puis par ligne
	 for( int i = 1; i <= pow(edge_len, dimension); i++ ){

		char token = tab[i-1]; //On recupere le token
		separator='|';

		//Tout les edge_len on saute une ligne
		if (i%(edge_len) == 0){
			separator = '\n'; //Saut de ligne
		}
		//Tout les edge_len^2 on affiche un séparateur
		if (i%(edge_len*edge_len) == 1 && i!=1){
			puts("  -");
		}
		//Tout les edge_len^3 on saute deux lignes
		if (i%(edge_len*edge_len*edge_len) == 1 && i!=1){
			puts("\n");
		}
		//Tout les edge_len^2 on affiche le numéro de plan et la lettre de cube
		if (i%(edge_len*edge_len*edge_len) == edge_len ){
			sprintf(scount, "    %c",letter); //Affichage du numéro du carré et attribuer valeur y à count
			letter++;
		}

		 printf("%c%s%c", token, scount,separator); //On affiche la ligne
		 sprintf(scount, "%s", ""); //on ré attribue à count une valeur vide
	 }
  }
  puts("\n");
}


char getTokenByPlayer(int player){
  /*Permet d'obtenir la forme du token dun joueur
  player -> numéro du joueur actuel

  Retourne le token.
  */


  if (player == 1){return 'X';}
  if (player == 2){return 'O';}
  if (player == 3){return 'R';}
  if (player == 4){return 'M';}

  return '?';
}


bool isCaseFree(char tab[], int position){
  /* Permet de vérifier si une case est déjà occupée

    tab -> grille de jeu
    position -> case à tester

    Retourne true si elle l'est.
  */

  return tab[position] == '.'; //Une case occupée sera toujours un '.'

}

int askForPosition(char tab[], int edge_len, int dimension, int player){
  /*Permet de demander la position où l'on veut jouer

   tab -> grille de jeu
   edge_len -> nombre de lignes (et de colonnes) de la grille de jeu
   dimension -> dimension de la grille
   player -> numéro du joueur actuel

   Retourne la position (donnée par le joueur) convertie en position dans notre tableau.
  */

  char token_type = getTokenByPlayer(player); //On récupère la forme de token (X ou O)

  int human_pos_case; //Case de base d'un morpion
  char case_phrase[50];
  sprintf(case_phrase, "J%d ~ %c case n°:", player, token_type);

  int layer; //Couche d'un cube
  char layer_phrase[50];
  sprintf(layer_phrase, "J%d ~ %c, plan n°:", player, token_type);

  int building; //Cube d'un ensemble de cubes
  char building_phrase[50];
  sprintf(building_phrase, "J%d ~ %c lettre du cube:", player, token_type);

  int position;

  if (dimension == 2){
    human_pos_case = askForInt(case_phrase, 1, edge_len*edge_len); //Le joueur choisit sa case

    position = human_pos_case-1; //En 2D la position sera la même que celle de l'humain -1

  }

  else if (dimension == 3){

    layer = askForInt(layer_phrase, 1, edge_len); //Le joueur choisit sa couche

    //On récupère la partie du tableau qui nous interesse
    int start = (layer-1) * edge_len * edge_len; //On calcul le début
    int size = edge_len *  edge_len * sizeof(char) ;
    char *tab_copy = malloc(size);
    memcpy(tab_copy, &tab[start], size); //On effectue une copie

    displayGrid(tab_copy, edge_len, dimension-1); //On affiche la grille dans la dimension de dessous

    position = start + askForPosition(tab_copy, edge_len, dimension-1, player);

    free(tab_copy);//On libère la mémoire
  }

  else if (dimension == 4){

    building = askForChar(building_phrase, 65, edge_len+64); //Le joueur choisit son cube

     //On récupère la partie du tableau qui nous interesse
    int start_3d = (building-65) * edge_len * edge_len * edge_len;

    int size_3d = edge_len * edge_len * edge_len * sizeof(char);
    char *tab_copy_3d = malloc(size_3d);
    memcpy(tab_copy_3d, &tab[start_3d], size_3d); //On effectue une copie
    displayGrid(tab_copy_3d, edge_len, dimension-1); //On affiche la grille dans la dimension de dessous (3)

    position = start_3d + askForPosition(tab_copy_3d, edge_len, dimension-1, player);


    free(tab_copy_3d);//On libère la mémoire
  }


  //Si la case est déjà prise
  if ( !(isCaseFree(tab, position)) ){
    puts("Case déjà prise. Recommencez.");
    position = askForPosition(tab, edge_len, dimension, player); // On relance la fonction
  }

  puts("----------------------------------------------------------------");
  return position;
}







bool checkHorizontalVictory2D(char tab[], int edge_len, char token){
    /*Permet de voir si un player a aligné horizontalement ses tokens.

   tab -> grille de jeu
   edge_len -> nombre de lignes (et de colonnes) de la grille de jeu
   token -> signe du player

111000000       000111000       000000111
  1 1 1           0 0 0           0 0 0
  0 0 0           1 1 1           0 0 0
  0 0 0           0 0 0           1 1 1

    Retourne true si un joueur a gagné
  */

  //On parcourt les cases situées à gauche de la grille
  for (int i=0; i <= edge_len*(edge_len-1); i+=edge_len){
    //Si une case correspond au token rentré en paramètre
    if (tab[i] == token){
      //On vérifie si les edge_len-1 token suivants sont similaires
      for(int j = 1; j <= edge_len; j++){
        //Si c'est vérifié
        if (tab[i+j] == token){
          //Et que j = edge_len
          if(j==edge_len-1){return true;}
        }
        else{return false;} //Si le token suivant est différent
      }
    }
  }
  return false;
}

bool checkVerticalVictory2D(char tab[], int edge_len, char token){
  /*Permet de voir si un player a aligné verticalement ses tokens.

   tab -> grille de jeu
   edge_len -> nombre de lignes (et de colonnes) de la grille de jeu
   token -> signe du player

100100100         010010010       001001001
  1 0 0             0 1 0           0 0 1
  1 0 0             0 1 0           0 0 1
  1 0 0             0 1 0           0 0 1

    Retourne true si un joueur a gagné
  */
  //On parcourt les cases situées en haut de la grille
  for(int i = 0; i < edge_len; i++){
    //Si une case correspond au token rentré en paramètre
    if(tab[i] == token){
      //On vérifie si les token situés en dessous sont similaires
      for (int j = edge_len; j <= edge_len*(edge_len-1); j+=edge_len){
        //Si le token en dessous est bon
        if(tab[i+j]==token){
          //Et si c'est le dernier token
          if(j == edge_len*(edge_len-1)){return true;}
        }
        else{return false;}//Si le token en dessous n'était pas bon
      }
    }
  }
  return false;

}


bool checkDiagonalVictory2D(char tab[], int edge_len, char token){
  /*Permet de voir si un player a aligné en diagonale ses tokens.

   tab -> grille de jeu
   edge_len -> nombre de lignes (et de colonnes) de la grille de jeu
   token -> signe du player

100010001         001010001
  1 0 0             0 0 1
  0 1 0             0 1 0
  0 0 1             1 0 0

  Retourne true si un joueur a gagné
  */

  //On vérifie le premier élément de la grille
  if( tab[0] == token ){
    //On parcourt les cases en diagonales suivantes
    for(int i = edge_len+1; i <= (edge_len*edge_len)-1; i += edge_len+1){
      //Si la case est un token
      if(tab[i] == token){
        //Et que c'est la dernière case
        if(i == edge_len*edge_len-1){return true;}
      }
      else{return false;} //Si une diagonale n'a pas de token
    }
  }

  //On vérifie le dernier élément de la 1re ligne de la grille
  if( tab[edge_len-1] == token){
    //On parcourt les cases en diagonales suivantes
    for(int i = edge_len-1; i <= edge_len*(edge_len-1); i += edge_len-1){
      //Si la case est un token
      if(tab[i] == token){
        //Et que c'est la dernière case
        if(i == edge_len*(edge_len-1)){return true;}
      }
      else{return false;} //Si une diagonale n'a pas de token
    }
  }

  return false;
}




bool checkVictory2D(char tab[], int edge_len, int player){
  /*Permet de svoir si un player à gagné ou non.

   tab -> grille de jeu
   edge_len -> nombre de lignes (et de colonnes) de la grille de jeu
   player -> numéro du joueur actuel

    Retourne true si un joueur a gagné.
    --> nombre de façons de gagner = 2 * edge_len + 2
  */


char token = getTokenByPlayer(player); //On récupère le token que l'on veut vérifier

if (checkHorizontalVictory2D(tab, edge_len, token) || checkVerticalVictory2D(tab, edge_len, token) || checkDiagonalVictory2D(tab, edge_len, token) ){
  return true;
}

  return false;
}




bool checkVictory3D(char tab[], int edge_len, int player){
  /*Permet de checker la victoire dans un cube

   tab -> grille de jeu
   edge_len -> nombre de lignes (et de colonnes) de la grille de jeu
   player -> numéro du joueur actuel

   Retourne true si une victoire est trouvée.
  */

  //Couches horizontales
  for (int i=0; i < pow(edge_len, 3); i+=edge_len*edge_len){

    char *tab_copy = malloc(edge_len*edge_len); //Cette varibale contiendra une couche

    memcpy(tab_copy, &tab[i], edge_len*edge_len); //On copie la couche dans la variable

    //On check la victoire sur cette couche
    if (checkVictory2D(tab_copy, edge_len, player)){
      free(tab_copy); //On libère la mémoire
      return true;
    }

    free(tab_copy); //On libère la mémoire
  }


  //Tranches verticales de gauche à droite
  for(int i=0; i < edge_len; i++){

    char *tab_copy = malloc(edge_len*edge_len); //Cette varibale contiendra une tranche de gateau
    int pos=0;
    for(int j = 0; j < pow(edge_len, 3); j+=edge_len){
       tab_copy[pos] = tab[i+j];
       pos++;
    }

    //On check la victoire sur cette tranche
    if (checkVictory2D(tab_copy, edge_len, player)){
      free(tab_copy); //On libère la mémoire
      return true;
    }

    free(tab_copy); //On libère la mémoire
  }

  //Tranches verticales de devant à derrière
  for(int i=0; i < edge_len*edge_len; i+=edge_len){

    char *tab_copy = malloc(edge_len*edge_len); //Cette varibale contiendra une tranche frontale
    int pos = 0;

    for(int j = 0; j < pow(edge_len, 3); j+=edge_len*edge_len){
      for (int k=0; k < edge_len; k++){
        tab_copy[pos] = tab[i+j+k];
        pos++;
      }
    }

    //On check la victoire sur cette tranche
    if (checkVictory2D(tab_copy, edge_len, player)){
      free(tab_copy); //On libère la mémoire
      return true;
    }
    free(tab_copy); //On libère la mémoire
  }



//Les diagonales tri-dimensionelles en partant de l'arrière
{// if(true)
  char *tab_copy = malloc(edge_len*edge_len*edge_len); //Cette varibale contiendra une grille 2D de diagonales

  //On parcourt la ligne n de la n-ième couche
  for (int i = 0; i < edge_len; i ++){

    char *line_copy = malloc(edge_len); //Cette variable contiendra une ligne
    int start = i*edge_len*(edge_len+1); //On récupère le début de la ligne suivante

    memcpy(line_copy, &tab[start], edge_len); //On récupère la ligne
    strcat(tab_copy, line_copy); //On concatène chaque ligne dans une copy
    free(line_copy); //On libère la mémoire

  }
  //On teste la grille comme si elle était en 2D
  if (checkVictory2D(tab_copy, edge_len, player)){
    free(tab_copy);
    return true;
  }
  free(tab_copy);
}

//Les diagonales tri-dimensionelles en partant de l'avant
{// if(true)
  char *tab_copy = malloc(edge_len*edge_len*edge_len); //Cette varibale contiendra une grille 2D de diagonales

  //On parcourt la ligne n de la n-ième couche
  for (int i = 1; i <= edge_len ; i++){

    char *line_copy = malloc(edge_len); //Cette variable contiendra une ligne
    int start = i*edge_len*(edge_len-1);
    memcpy(line_copy, &tab[start], edge_len); //On récupère la ligne
    strcat(tab_copy, line_copy); //On concatène chaque ligne dans une copy
    free(line_copy); //On libère la mémoire

  }
  //On teste la grille comme si elle était en 2D
  if (checkVictory2D(tab_copy, edge_len, player)){
    free(tab_copy);
    return true;
  }
  free(tab_copy);
}

  return false;
}

bool checkVictory4D(char tab[], int edge_len, int player){
  /*Permet de checker la victoire dans en prenant en compte plusieurs cubes.

   tab -> grille de jeu
   edge_len -> nombre de lignes (et de colonnes) de la grille de jeu
   player -> numéro du joueur actuel

   Retourne true si une victoire est trouvée.
  */

  //On segmente chaque cube
  for(int i=0; i <= pow(edge_len, 4); i += pow(edge_len, 3)){

    char *tab_copy = malloc(pow(edge_len, 4));
    memcpy(tab_copy, &tab[i], pow(edge_len, 3)); //On effectue une copie du cube

    if (checkVictory3D(tab_copy, edge_len, player)){ //On teste si il y a une victoire
      free(tab_copy); //On libère la mémoire
      return true;
    }
    free(tab_copy);
  }


  //On fait un cube à partir de la grille n de chaque cube
  for (int i = 0; i < edge_len*edge_len*edge_len; i+=edge_len*edge_len){

    char *tab_copy = malloc(pow(edge_len, 4)); //Copie d'un cube

    //On prends chaque grille n d'une lettre
    for(int j = 0; j < edge_len; j++){

      char *grid_copy = malloc(pow(edge_len,3)); //Copie d'une grille
      int start = i + j * pow(edge_len, 3);
      memcpy(grid_copy, &tab[start], pow(edge_len, 2)); //On effectue une copie du cube

      strcat(tab_copy, grid_copy); //On concatène chaque grille dans une copie d'un cube
      free(grid_copy); //On libère la mémoire

    }
    if (checkVictory3D(tab_copy, edge_len, player)){ //On teste si il y a une victoire
      free(tab_copy); //On libère la mémoire
      return true;
    }
    free(tab_copy);

  }

  {
  //On fait un cube avec des grilles correspondants à leur place dans leur dimension
    char *tab_copy = malloc(pow(edge_len, 4)); //Copie d'un cube
    for (int i = 0; i < edge_len ; i ++ ){

      char *grid_copy = malloc(pow(edge_len,3)); //Copie d'une grille
      int start = i* (pow(edge_len,3) + edge_len*edge_len); //On calcule un start

      memcpy(grid_copy, &tab[start], pow(edge_len, 2));
      strcat(tab_copy, grid_copy); //On concatène chaque grille dans une copie d'un cube

      free(grid_copy); //On libère la mémoire
    }
    if (checkVictory3D(tab_copy, edge_len, player)){ //On teste si il y a une victoire
      free(tab_copy); //On libère la mémoire
      return true;
    }
    free(tab_copy);
  }


  {
  //On fait un cube avec des grilles correspondants à leur place dans leur dimension en partant du bas
    char *tab_copy = malloc(pow(edge_len, 4)); //Copie d'un cube
    for (int i = 1; i <= edge_len ; i ++ ){
      char *grid_copy = malloc(pow(edge_len,3)); //Copie d'une grille
      int start = i* (pow(edge_len,3) - edge_len*edge_len); //On calcule un start

      memcpy(grid_copy, &tab[start], pow(edge_len, 2));
      strcat(tab_copy, grid_copy); //On concatène chaque grille dans une copie d'un cube

      free(grid_copy); //On libère la mémoire
    }
    if (checkVictory3D(tab_copy, edge_len, player)){ //On teste si il y a une victoire
      free(tab_copy); //On libère la mémoire
      return true;
    }
    free(tab_copy);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  }





  return false;
}

bool checkVictory(char tab[], int edge_len, int player, int dimension){
   /*Permet de diviser un cube en grille 2d

   tab -> grille de jeu
   edge_len -> nombre de lignes (et de colonnes) de la grille de jeu
   player -> numéro du joueur actuel


  */

  if (dimension==2){
    return checkVictory2D(tab, edge_len, player);
  }
  else if (dimension==3){
    return checkVictory3D(tab, edge_len, player);
  }
  else if (dimension==4){
    return checkVictory4D(tab, edge_len, player);
  }

  return false;
}
