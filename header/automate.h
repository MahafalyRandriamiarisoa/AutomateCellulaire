#ifndef AUTOMATE_H
#define AUTOMATE_H

#include <stdlib.h>
#include <stdio.h>
#include <term.h> // library pour utiliser termcap
#include <curses.h> // on utilisera les define des couleurs
#include <string.h>
#include <time.h>

#include <stdarg.h>

#include "utils.h"
// #include "RuleStrategy.h"
// #include "differentsRules.h"


//#include "../header/utils.h"
#include "termcap_initializer.h"


#define NCOL tgetnum("co") // recuperer la longueur du terminal où est exécuté le programme et on met à disposition la longueur du terminal 
#define NLI  (tgetnum("li")-1) // recuperer la longueur du terminal où est exécuté le programme et on met à disposition la longueur du terminal 
// #define NLI 0 // recuperer la longueur du terminal où est exécuté le programme et on met à disposition la longueur du terminal 
// #define NCOL 0 
#define NB_VOISINS 3


struct cellule{

    int state; //compris entre 0 et 1
    // struct cellule* nghd; //tableau de trois cellules
    // struct cellule* right;
    // struct cellule* left;



    };

// export int n_col = tege

typedef struct cellule* cell;

typedef cell (*RuleStrategy)(cell c,cell* line);

struct automate{
    
    cell* currentLine;
    char* rule;
    char* linesSave;
    void (*dsp)(void*);

    RuleStrategy rs;

};

typedef struct automate* Autom;

void test(void*);

// passez en paramètre le pointeur d'un automate et une regle afin d'initialiser ce dernier
void initAutomate(Autom, char*);

void displayAutomate(void*);
void fancyAutomateDisplay(void*automate);
Autom automateGen( char*);



cell* lineGen(cell*, char*); // ici le deuxième argument sera obligatoirement de taille 8
void lineDisplay(cell *line,int n);
cell* getNghd(cell c,cell *line);
void afficherTabCell(cell* t,int length);
void freeTabCell(cell*line,int length);


char* ruleGen(int);
void generiqueDisplay(void*,void(*)(void*));

char* tabcellToString(cell* t,int);
char* intToBase(int n,int base,int lg);

cell* subTab(int indD,int lg,cell* array,int lgArray);
void clear_term();





#endif