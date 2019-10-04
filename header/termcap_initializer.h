// ce code n'est pas le mien :https://github.com/Glordim/Termcap_Tetris/blob/master/src/termcap_initializer.h

#ifndef TERMCAP_INITIALIZER_H
#define TERMCAP_INITIALIZER_H

#include <term.h>
#include <curses.h>
#include <ncurses.h>


struct s_termcap_cmd
{
	char *cl; // clear, efface tout
	char *cm; // déplace le curseur à la ligne l, colonne c
	char *vi; // rend le curseur invisible
	char *ve; // le cuseur reevient normal
	char *ab; // changer la couleur de fond
    char *af; // changer la couleur de la police
	char *reset; //renitialiser les paramètre

	char *ku; //input de la touche fleche du haut
	char *kd; //input de la touche fleche du bas
	char *kl; //input de la touche fleche gauche
	char *kr; //input de la touche fleche droite
};

typedef struct s_termcap_cmd* stc;

int init_termcap(stc);
// extern stc tc_cmd;
// extern struct s_termcap_cmd tc_cmd;

void freestc(stc);


#endif