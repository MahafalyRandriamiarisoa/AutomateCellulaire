#include <stdlib.h>
#include <stdio.h>
#include <sys/select.h>

#include "header/automate.h"
#include "header/termcap_initializer.h"

void initTerm(){
    int ret = tgetent(NULL,getenv("TERM")); // initialisation de termcap pour recuperer quelque infos sur le terminal
    char *clrTerm = tgetstr("cl",NULL);
    tputs(clrTerm, 1, putchar);
}

void check_input(){
    char read_buffer[64] = {0};
    
}

int main(int argc,char** argv){
    int keep_running = 1;
    
    fd_set t;
    

    init_termcap();
    
    const char* rule = "00011110";
    // const char* rule = "01011010";

    
    /* cell line0 = lineGen(NULL,"");
    lineDisplay(line0,0);
    cell line1 = lineGen(line0,"00011110");
    lineDisplay(line1,1);
 */
    clear_term();

    cell lineN = NULL;
    for(int i=0;i<NLI-1;i++){

        lineN = lineGen(lineN,rule);
        lineDisplay(lineN,i);
        //free(&lineN[i]);
    }
   
    // puts("");
    // printf("NCOL = %d\n",NCOL);
    // getNghd(&line0[5],line0);
    // cell soustab = subTab(0,6,line0,NCOL);
    // afficherTabCell(soustab,6);
    tputs(tc_cmd.ve,1,putchar);
    
    //clear_term();
    tputs(tc_cmd.reset,1,putchar);
    fflush(stdout);

    return EXIT_SUCCESS;

}
