#ifndef AUTOMATE_H
#define AUTOMATE_H

#include <stdlib.h>
#include <stdio.h>

struct cellule{
    int state; //compris entre 0 et 1
    int nghd; // compris entre 0 et 7
};

int* lineGen(int*,const char*); // ici le deuxième argument sera obligatoirement de taille 8

#endif