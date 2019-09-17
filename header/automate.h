#ifndef AUTOMATE_H
#define AUTOMATE_H

#include <stdlib.h>
#include <stdio.h>
#include <term.h> // library pour utiliser termcap
#include <curses.h> // on utilisera les define des couleurs

#include "termcap_initializer.h"

#define NCOL tgetnum("co") // recuperer la longueur du terminal où est exécuté le programme et on met à disposition la longueur du terminal 


struct cellule{
    int state; //compris entre 0 et 1
    int nghd; // compris entre 0 et 7
};

typedef struct cellule* cell;

cell lineGen(cell,const char*); // ici le deuxième argument sera obligatoirement de taille 8
void lineDisplay(cell line,int n);
void clear_term();



#endif