#ifndef AUTOMATE_H
#define AUTOMATE_H

#include <stdlib.h>
#include <stdio.h>
#include <term.h> // library pour utiliser termcap
#include <curses.h> // on utilisera les define des couleurs
#include <string.h>

#include "utils.h"

//#include "../header/utils.h"
#include "termcap_initializer.h"


#define NCOL tgetnum("co") // recuperer la longueur du terminal où est exécuté le programme et on met à disposition la longueur du terminal 
#define NLI tgetnum("li") // recuperer la longueur du terminal où est exécuté le programme et on met à disposition la longueur du terminal 
// #define NLI 2 // recuperer la longueur du terminal où est exécuté le programme et on met à disposition la longueur du terminal 
// #define NCOL 5 
#define NB_VOISINS 3

struct cellule{

    int state; //compris entre 0 et 1
    struct cellule* nghd; //tableau de trois cellules
    void(*_afficher)(struct cellule*line);
    struct cellule* right;
    struct cellule* left;



    };

typedef struct cellule* cell;

cell lineGen(cell,const char*); // ici le deuxième argument sera obligatoirement de taille 8
void lineDisplay(cell line,int n);
cell getNghd(cell c,cell line);
void afficherTabCell(cell t,int length);

char* tabcellToString(cell t);
char* intToBase(int n,int base,int lg);

cell subTab(int indD,int lg,cell array,int lgArray);
void clear_term();





#endif