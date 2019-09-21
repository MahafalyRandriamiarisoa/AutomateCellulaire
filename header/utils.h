#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

int mod(int,int); //a mod b == (a % b + b) % b, pour pouvoir gerer les indices d'un tableau circulaire car l'operande "%" ne donne que le reste du division euclidienne

int nb_char_int(int v); // fonction qui permet de savoir combien de caractère compose un entier

void itoa(int value, char* str, int base); // code utilisé pour convertir un entier dans n'importe quelle base, cette fonction n'est pas inclue dans la library standard mais son code est disponible ici :http://www.strudel.org.uk/itoa/ 


int bin_to_int(char*);