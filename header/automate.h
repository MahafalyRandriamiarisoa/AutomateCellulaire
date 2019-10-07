#ifndef AUTOMATE_H
#define AUTOMATE_H

#include <stdlib.h>
#include <stdio.h>
#include <term.h> // library pour utiliser termcap
#include <curses.h> // on utilisera les define des couleurs
#include <string.h>
#include <time.h>

#include <stdarg.h>

// #include "RuleStrategy.h"
// #include "differentsRules.h"


//#include "../header/utils.h"
#include "termcap_initializer.h"




// #define NCOL tgetnum("co") // recuperer la longueur du terminal où est exécuté le programme et on met à disposition la longueur du terminal 
// #define NLI  (tgetnum("li")-1) // recuperer la longueur du terminal où est exécuté le programme et on met à disposition la longueur du terminal 
// #define NLI 10 // recuperer la longueur du terminal où est exécuté le programme et on met à disposition la longueur du terminal 
// #define NCOL 5

#define NCOL COL
#define NLI LI
#define NB_VOISINS 3

// int getCOL();
// int getLI();

int COL;
int LI;

struct cellule{

    int state; //compris entre 0 et 1
    // struct cellule* nghd; //tableau de trois cellules
    // struct cellule* right;
    // struct cellule* left;



};


// export int n_col = tege

typedef struct cellule* cell;

struct Rule{
    char* rule;
    cell (*getNextCell)(cell,cell*,char*);
};
typedef struct Rule* _Rule;
typedef cell (*RuleStrategy)(cell c,cell* line);

struct automate{
    
    cell* currentLine;
    char* rule;

    _Rule _rule;
    int MAX_Value;
    int FIRST_VALUE;
    int POSITION_FIRST_VALUE;
    char* linesSave;
    int WIDTH;
    int HEIGHT;

    void (*dsp)(void*);

    

};

typedef struct automate* Autom;
#include "utils.h"
#include "pgm_img.h"

void test(void*);

// passez en paramètre le pointeur d'un automate et une regle afin d'initialiser ce dernier

_Rule initRule(char*,cell(*)(cell,cell*,char*));
void initAutomate(Autom a, char* rule,int  MAX_Value,int FIRST_VALUE,int WIDTH,int HEIGHT, int POSITION_FIRST_VALUE,_Rule _rule);

void displayAutomate(void*);
void fancyAutomateDisplay(void*automate);

void automateDisplayInPGM(void*automate);
Autom automateGen( char* rule,int MAX_Value,int FIRST_VALUE,int WIDTH,int HEIGHT,int POSITION_FIRST_VALUE, _Rule _rule);
void freeAutomate(Autom ate);


cell* lineGen(cell*,Autom a); 
void lineDisplay(cell *line,int n);
cell* getNghd(cell c,cell *line,Autom a);
void afficherTabCell(cell* t,int length);
void freeTabCell(cell*line,int length);

cell applyRule(cell c,cell* line, char*rule);
char* ruleGen(int);
void generiqueDisplay(void*,void(*)(void*));

char* tabcellToString(cell* t,int);
char* intToBase(int n,int base,int lg);

cell* subTab(int indD,int lg,cell* array,int lgArray);
void clear_term();





#endif