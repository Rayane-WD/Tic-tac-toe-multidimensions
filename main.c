#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include "grid.h"
#include "extra.h"


int main(void) {

  int dimension;
  int edge_len;
  int nb_player;
  bool victory = false;


  puts("\n      Jeu du Mxrpixn, by Rxyxne & Mxteo\n\n");

  //On demande la dimension
  dimension = askForInt("Dimension (2, 3 ou 4): ", 2, 4);
  //dimension = 2;

  //On demande la taille de la grille
  edge_len = askForInt("Taille des côtés: ", 3, 1000);
  //edge_len = 5;

  //On demande le nombre de player
  nb_player = askForInt("Nombre de Joueur (2 à 4) : ", 2, 4);

  // On calcule le nombre de grilles à afficher
  int nb_2Dgrid = pow(edge_len, dimension-2); // "-2" car c'est la dimension de représentation de nos grilles

  //On créer la grille de jeu
  int size = edge_len * edge_len * nb_2Dgrid;
  char tab[size];
  initializeGrid(tab, size);

  int actual_player = 0;
  int tour = 0;
  int p_tour = 1;

  //Le jeu commence
  puts("      Le jeu commence...\n");

  do{
    //On affiche la grille
    displayGrid(tab, edge_len, dimension);

    //On demande au joueur actuel dans quelle grille il veut jouer
    p_tour = tour/nb_player+1;
    printf("###### n°%d ######\n", p_tour); //On affiche le numéro de tour

    actual_player = ( tour%nb_player ) +1;
    int position = askForPosition(tab, edge_len, dimension, actual_player);
    tab[position] = getTokenByPlayer(actual_player); //On place le token


    victory = checkVictory(tab, edge_len, actual_player, dimension);


    //Le tour s'incrémente
    tour++;
  }
  while( !victory && tour < pow(edge_len, dimension));

  displayGrid(tab, edge_len, dimension);
  // En fonction de la sortie du while on affiche la phrase finale
  if (victory){
    printf("\n > > > > > Victoire ! Le gagnant est J%d.", actual_player);
  }
  else{
    puts("\n > > > > > Égalité ! Les grilles sont remplies.");
  }


  return EXIT_SUCCESS;
}
