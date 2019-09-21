#include "../header/automate.h"

void clear_term()
{
	tputs(tc_cmd.cl, 1, putchar);
	fflush(stdout);
}

int getIndice(cell c,cell line){

    int ind = -1;
    for(int i =0;i<NCOL;i++){
        if (c == &line[i]){
            return i;
        }
    }
    return -1;
    
}

//permet de réaliser un sous tableau circulaire
// todo: peut être le changer avec des paramètres generiques
cell subTab(int indD,int lg,cell array,int lgArray){

    cell t2 = (cell) malloc (sizeof(struct cellule)*lg);
    //printf("\nindFinlgArray = %d\n",lgArray);
    int indFin = ((indD+lg)>lgArray)?((indD+lg)%lgArray)-1:indD+lg;
    int indMax = lgArray - 1;
    int j = 0;
    for(int i=indD;j<lg;i++){

        if(i>indMax){
            i = 0;
        }
        
        t2[j] = array[i];
        j++;
    }

    return t2;
}


char* tabcellToString(cell t){

    char* str = (char*) calloc(NB_VOISINS,sizeof(char)*NB_VOISINS);
    for(int i=0; i<NB_VOISINS; i++){

        char ti[nb_char_int(t[i].state)];
        sprintf(ti,"%d",t[i].state);
        strcat(str,ti);
        

    }
    // printf("strlen = %ld\n",strlen(str));
    return str;
}

cell getNghd(cell c,cell line){

    // cell nghd = (cell) malloc(sizeof(struct cellule)*3);
    int ind_c = getIndice(c,line);
    int idDepart = mod(ind_c - (((NB_VOISINS)-1)/2),NCOL);
    cell nghd = subTab(idDepart,NB_VOISINS,line,NCOL);

        return nghd;
    
}


cell applyRule(cell c,cell line,const char*rule){

    cell new = (cell) malloc (sizeof(struct cellule));
    cell nghd = getNghd(c,line);
    //  char* cnghd = tabcellToString(c);
     //printf("nghd attrbt = %s\n",cnghd);
     //cell nghd = (c->nghd);
    char* b = tabcellToString(nghd);
    
    int p = bin_to_int(b);
    free(b);
    char new_statechar = rule[((int)(strlen(rule)-1))-p];
    /* puts("");
    afficherTabCell(nghd,3);
    int test = 0;
    printf("rule = %s rule[p=%d] = %c\n",rule,p,new_statechar); */
    int newstate = atoi(&new_statechar);
    new->state = newstate;
    
    for(int i=0; i<NB_VOISINS; i++){
        //free(&nghd[i]);
    }

    return new;
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
    }else{

        for(int i=0; i < NCOL; i++){

            l[i] = *(applyRule(&line[i],line,rule));
        }
        for (int i = 0; i<NCOL;i++){

           //free(&line[i]);
        //    line[i] = &NULL;

        }

       // free(line);
    }

    for(int i=0;i<NCOL;i++){
        
        //l[i].nghd = getNghd(&l[i],l);

    }

    return l;
}

void beautyLineDisplay(cell line,int n){ // n ici est le numero de ligne à afficher
    
    //tputs( tparm(tc_cmd.ab,COLOR_RED), 1, putchar); // on met la couleur de fond en blanc
    
    for(int i = 0; i<NCOL; i++){

        int colorab = (line[i].state == 0)? COLOR_BLACK : COLOR_WHITE;
        tputs( tparm(tc_cmd.ab,colorab), 1, putchar);
        int coloraf = (line[i].state == 0)? COLOR_BLACK : COLOR_WHITE;
        tputs( tparm(tc_cmd.af,coloraf), 1, putchar);
        tputs(tgoto(tc_cmd.cm,i,n),1,putchar);
        // printf("%d",line[i].state); // dev mode
        printf(" ");
    }
    
    
    


}

void lineDisplay(cell line,int y){

    // char *reset_cmd = tgetstr("me", NULL);
    //tputs(tc_cmd.reset, 1, putchar);
    for(int i = 0; i<NCOL; i++){
        //printf("%d",line[i].state);
    }
    puts("");
    beautyLineDisplay(line,y);

}

void afficherTabCell(cell t,int length){
    for(int i = 0; i<length; i++){
        printf("%d",t[i].state);
    }
    puts("");
}


