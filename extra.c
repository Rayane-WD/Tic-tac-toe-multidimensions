#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include "grid.h"


int askForInt(char message[], int limit_min, int limit_max){
  /* S'assure que le int demand� est dans la limite demaand�e.

  message -> message afficher pour aiguiller l'utilisateur
  limit_min -> valeur min possible (inclue)
  limit_max -> valeur max possible (inclue)

  Retourne le int rentr� par l'utilisateur
  */
	int validation;
  int out;



  fflush( stdout );
  puts(message); //On affiche le message
  fflush( stdout );
  validation = scanf("%d", &out); // validation sera �gale � 1 si le scanf s'est bien d�roul�
  fflush( stdout );
  puts("\n");

  //Si les conditions d'input ne sont pas r�spect�es...
  if ( validation != 1 || !(limit_min <= out && out <= limit_max) ){
    return askForInt(message, limit_min, limit_max); //... on relance la fonction de demande d'input
  }
  return out;
}


char askForChar(char message[], int limit_min, int limit_max){
  /* S'assure que le char demand� est inf�rieur � une certaine valeur ASCII limite.

  message -> message afficher pour aiguiller l'utilisateur
  limit_min -> valeur min possible (inclue)
  limit_max -> valeur max possible (inclue)

  Retourne le char rentr� par l'utilisateur
  */

  char out;
  do{
  puts(message);
  fflush( stdout );
  scanf(" %c", &out);
  fflush( stdout );
  puts("\n");
  out = toupper(out);

  } while( !(out >= limit_min && out <= limit_max) );

  return out;
}
