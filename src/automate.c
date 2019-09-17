#include "../header/automate.h"

void clear_term()
{
	tputs(tc_cmd.cl, 1, putchar);
	fflush(stdout);
}


cell lineGen(cell line,const char* rule){
    
     
    cell l = (cell) malloc(sizeof(struct cellule)*NCOL);
    if(line == NULL){
        // printf("generation de la première ligne de %d caractères\n",NCOL);
        for(int i = 0;i < NCOL; i++){
            if(i == NCOL/2){
                l[i].state = 1;
            }else{
                l[i].state = 0;
            }
        }
        return l;
    }
    return l;
}
void beautyLineDisplay(cell line,int n){ // n ici est le numero de ligne à afficher
    char *clrTerm = tgetstr("cl",NULL);
    //tputs(clrTerm, 1, putchar); 

    
    tputs( tparm(tc_cmd.ab,COLOR_RED), 1, putchar); // on met la couleur de fond en blanc
    

    tputs(tgoto(tc_cmd.cm,0,0),1,putchar);
    
    printf(" ");


    



}

void lineDisplay(cell line,int n){

    // char *reset_cmd = tgetstr("me", NULL);
    tputs(tc_cmd.reset, 1, putchar);
    for(int i = 0; i<NCOL; i++){
        //printf("%d",line[i].state);
    }
    //puts("");
    beautyLineDisplay(line,n);

}


