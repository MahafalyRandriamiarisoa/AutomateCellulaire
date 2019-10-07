#include "../header/automate.h"


_Rule initRule(char*rule,cell(*getNextCell)(cell c,cell* linec,char*rule)){
    _Rule _rule = (_Rule) malloc(sizeof(struct Rule));
    _rule->rule = rule;
    _rule->getNextCell = getNextCell;
    return _rule;
}
void clear_term()
{
    stc tc_cmd = (stc) malloc(sizeof(struct s_termcap_cmd));
    init_termcap(tc_cmd);
	tputs(tc_cmd->cl,1, putchar);
	fflush(stdout);
    free(tc_cmd);
    tc_cmd = NULL;
}

int getIndice(cell c,cell* line,Autom a){
    int ind = -1;
    for(int i =0;i<a->WIDTH;i++){
        if (c == line[i]){
            return i;
        }
    }
    return -1;
    
}

void freeTabCell(cell*line,int length){
    for(int i=0; i<length; i++){
        // line[i]->state = -1;
        free(line[i]);
        line[i] = NULL;
    }
    free(line);
    line = NULL;
}



void initAutomate(Autom a,int  MAX_VALUE,int FIRST_VALUE,int WIDTH,int HEIGHT, int POSITION_FIRST_VALUE,_Rule _rule){

    a->linesSave = "";

    a->_rule = _rule;
    a->MAX_VALUE = MAX_VALUE;
    a->FIRST_VALUE = FIRST_VALUE;
    a->WIDTH = WIDTH;
    a->HEIGHT = HEIGHT;
    a->POSITION_FIRST_VALUE = POSITION_FIRST_VALUE;
}

Autom automateGen(int MAX_VALUE,int FIRST_VALUE,int WIDTH,int HEIGHT,int POSITION_FIRST_VALUE, _Rule _rule){
    Autom a = (Autom) malloc (sizeof(struct automate));
    
    initAutomate(a,MAX_VALUE,FIRST_VALUE,WIDTH,HEIGHT, POSITION_FIRST_VALUE,_rule);

    cell *lineN = NULL;
    char* str = (char*) calloc(((a->WIDTH +1)*a->HEIGHT)+1,sizeof(char)*(((a->WIDTH +1)*a->HEIGHT)+1));
    for(int i=0;i<a->HEIGHT;i++){

        lineN = lineGen(lineN,a);


        
        char* s = tabcellToString(lineN,a->WIDTH);
        strcat(str,s);

        free(s);
        s = NULL;

        strcat(str,"\n");
    }
        freeTabCell(lineN,a->WIDTH);
        strcat(str,"\0");
        a->linesSave = str;
        return a;
}

void freeAutomate(Autom ate){
    free(ate->linesSave);
        free(ate);
        ate = NULL;
}

void displayAutomate(void*automate){
    printf("%s",((Autom)automate)->linesSave);
}


//permet de réaliser un sous tableau circulaire
// todo: peut être le changer avec des paramètres generiques
cell* subTab(int indD,int lg,cell* array,int lgArray){

    cell* t2 = (cell*) malloc (sizeof(cell)*lg);
    int indMax = lgArray - 1;
    // int indFin = ((indD+lg)>lgArray)?((indD+lg)%lgArray)-1:indD+lg;
    int indFin = ((indD+lg)>indMax)?((indD+lg)%lgArray):indD+lg;
    //printf("\nindFinlgArray = %d\n",lgArray);
    if(indFin > indMax){
        // printf("AAAAAAAAAHPUTAIN\n");
    }
    if(indFin == -1){
        printf("OOOOOOOOOOOHPUTAIN\n");
    }
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


char* tabcellToString(cell* t,int length){

    char* str = (char*) calloc(length,sizeof(char)*length);
    for(int i=0; i<length; i++){

        char ti[nb_char_int(t[i]->state)];
        sprintf(ti,"%d",t[i]->state);
        strcat(str,ti);
        
    }
    strcat(str,"\0");
    // printf("strlen = %ld\n",strlen(str));
    return str;
}

cell* getNghd(cell c,cell* line,Autom a){

    // cell nghd = (cell) malloc(sizeof(struct cellule)*3);
    int ind_c = getIndice(c,line,a);
    int idDepart = mod(ind_c - (((NB_VOISINS)-1)/2),a->WIDTH);
    cell* nghd = subTab(idDepart,NB_VOISINS,line,a->WIDTH);
        return nghd;
    
}

int sumNghd(cell* nghd){
    int total = 0;
    for(int i=0; i<NB_VOISINS; i++){
        total += nghd[i]->state;
    }
    return total;

}


cell applyRule(cell c,cell* nghd, char*rule){

    cell new = (cell) malloc (sizeof(struct cellule));
    // cell* nghd = getNghd(c,line);
    char new_statechar = ' ';
    char* b = "";
    int p =0;
    

    int lenRule = (int) strlen(rule);
    switch (lenRule){
        case 8:
        //  char* cnghd = tabcellToString(c);
        //printf("nghd attrbt = %s\n",cnghd);
        //cell nghd = (c.nghd);

            b = tabcellToString(nghd,NB_VOISINS);
            
            p = bin_to_int(b);
            free(b);
            new_statechar = rule[((int)(strlen(rule)-1))-p];
        /* puts("");
        afficherTabCell(nghd,3);
        int test = 0;
        printf("rule = %s rule[p=%d] = %c\n",rule,p,new_statechar); */
        break;

        case 10:
            new_statechar = rule[sumNghd(nghd)];

        break;

        default: break;

    }
    free(nghd);
    int newstate = atoi(&new_statechar);
    new->state = newstate;
    // freeTabCell(nghd,NB_VOISINS);
    // free(nghd);

    return new;
}

void test(void*x){
    cell(*fct) = x;
    
    printf("NIMPORTEQUOI\n");
}

cell getNextCell(cell c,cell(*applyRule)(cell c,cell*line,char*rule));

cell *lineGen(cell *line,Autom a){
    // int beginValue = (strlen(rule)==10)? 3:1;
    int beginValue = a->FIRST_VALUE;
    cell *l = (cell*) malloc(sizeof(cell)*a->WIDTH);

    if(line == NULL){
        // printf("generation de la première ligne de %d caractères\n",NCOL);
        for(int i = 0;i < a->WIDTH; i++){
            cell c = (cell) malloc (sizeof(struct cellule));
            if(i == a->POSITION_FIRST_VALUE){
                c->state = beginValue;
            }else{

               c->state = 0;
               
                
            }
            l[i] = c;

            
        }

    }else{

        for(int i=0; i < a->WIDTH; i++){
            cell * nghd = getNghd(line[i],line,a);
            // l[i] = (applyRule(line[i],nghd,rule));
            l[i] = a->_rule->getNextCell(line[i],nghd,a->_rule->rule);
            // freeTabCell(nghd,NB_VOISINS);
        }
       
        freeTabCell(line,a->WIDTH);

    }

    
    return l;
}

char* ruleGen(int size){
    
    
    char* str = (char*)calloc(size,sizeof(char)*size);
    int x = 0;
    for(int i=0;i<size;i++){
        x = rand() %4;
        while((x == 0) && (i == 3)){
            
        x = rand() %4;
        }
        sprintf(&str[i],"%d",x);
    }
    return str;
}

/* void beautyLineDisplay(cell *line,int n){ // n ici est le numero de ligne à afficher
    
    //tputs( tparm(tc_cmd.ab,COLOR_RED), 1, putchar); // on met la couleur de fond en blanc
    
    for(int i = 0; i<NCOL; i++){

        int colorab = (line[i]->state == 0)? COLOR_BLACK : COLOR_WHITE;

        tputs( tparm(tc_cmd.ab,colorab), 1, putchar);

        int coloraf = (line[i]->state == 0)? COLOR_BLACK : COLOR_WHITE;

        tputs( tparm(tc_cmd.af,coloraf), 1, putchar);
        tputs(tgoto(tc_cmd.cm,i,n),1,putchar);
        // printf("%d",line[i]->state); // dev mode
        printf(" ");
    }
} */

void fancyAutomateDisplay(void*automate){
    
    clear_term();
    stc tc_cmd = (stc) malloc(sizeof(struct s_termcap_cmd));
    init_termcap(tc_cmd);
    tputs(tc_cmd->vi,1,putchar);
    Autom a = (Autom) automate;
    int colorab = 0;
    int x = 0,y=0;
    // for(int i= 0 ;i < ((NCOL+1)*(NLI-1)); i++){
    for(int i= 0 ;i <(int)strlen(a->linesSave); i++){

        char c = a->linesSave[i];
        int c1 = atoi(&c);

        if( c == '\n'){ x=0;  y++; }
        else {
            switch (c1){

                case 0 : colorab = COLOR_BLACK;
                    break;
                case 1 : colorab = COLOR_YELLOW ;
                    break;
                case 2 : colorab = COLOR_MAGENTA;
                    break;
                case 3 : colorab = COLOR_RED; 
                    break;  
                default : colorab = COLOR_CYAN;
            }
        // int colorab = (c == '0')? COLOR_BLACK : COLOR_WHITE;
            // int coloraf = (c == '0')? COLOR_WHITE : COLOR_BLACK; // for debug mod
            // int coloraf = COLOR_WHITE;
            int coloraf = COLOR_GREEN;
            tputs( tparm(tc_cmd->af,coloraf), 1, putchar);
            tputs( tparm(tc_cmd->ab,colorab), 1, putchar);
            tputs( tgoto(tc_cmd->cm,x,y),1,putchar);
            fflush(stdout);
            // printf("%c",c); // dev mode
            // printf("%d",x%10); // dev mode
            printf(" ");
            x++;
        }

    }
    /* for(int i = 0;i < (int)strlen(a->rule);i++){
        int coloraf = COLOR_GREEN;
        tputs( tparm(tc_cmd->af,coloraf), 1, putchar);
         tputs( tgoto(tc_cmd->cm,i,0),1,putchar);
         printf("%c",a->rule[i]);
    } */
    napms(0);
    // clear_term();
    fflush(stdout);
    tputs(tc_cmd->reset,1,putchar);
    
    
    // tputs(tc_cmd.reset,1,putchar);
    // tputs(tc_cmd->ve,1,putchar);
    tputs(tc_cmd->ve,1,putchar);
    free(tc_cmd);
    tc_cmd = NULL;
}

/* void lineDisplay(cell *line,int y){

    // char *reset_cmd = tgetstr("me", NULL);
    //tputs(tc_cmd->reset, 1, putchar);
    for(int i = 0; i<NCOL; i++){
        //printf("%d",line[i]->state);
    }
    puts("");
    beautyLineDisplay(line,y);

} */

void afficherTabCell(cell* t,int length){
    for(int i = 0; i<length; i++){
        printf("%d",t[i]->state);
    }
    // puts("");
}
// #include "../header/pgm_img.h"

void automateDisplayInPGM(void*automate){
    Autom a = (Autom) automate;
    int** tab2d = tabstrToTab2dInt(a->linesSave,a->HEIGHT,a->WIDTH);
    pgm p = creer_image_pgm(a->WIDTH,a->HEIGHT,a->MAX_VALUE,tab2d);
    ecrire_image_pgm("IMAGE.pgm", p );
    detruire_image_pgm(&p);
    free(p);
}

void generiqueDisplay(void*toDisplay,void(*dspl)(void*)){

    dspl(toDisplay);

}



// int getCOL(){
//     return COL;
// }
// int getLI(){
//     return LI;
// }


