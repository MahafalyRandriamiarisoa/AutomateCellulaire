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
    clear_term();

    
    cell line0 = lineGen(NULL,"");

    lineDisplay(line0,0);
    tputs(tc_cmd.vi,1,putchar);
    fflush(stdout);
    while(keep_running){


    }
    clear_term();
    tputs(tc_cmd.reset,1,putchar);

    return EXIT_SUCCESS;

}
