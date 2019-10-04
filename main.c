#include <stdlib.h>
#include <stdio.h>
#include <sys/select.h>
#include <time.h>
#include <regex.h>

#include "header/automate.h"
#include "header/termcap_initializer.h"

/* void initTerm(){
    int ret = tgetent(NULL,getenv("TERM")); // initialisation de termcap pour recuperer quelque infos sur le terminal
    char *clrTerm = tgetstr("cl",NULL);
    tputs(clrTerm, 1, putchar);
} */

void check_input(){
    char read_buffer[64] = {0};
}

int main(int argc,char** argv){

    init_termcap(NULL);
    
    char*rule=NULL;

    if(argc>2){

    }else{
        if(argc==2){
            char* str = argv[1];
            if (strcmp(str,"sc")==0)
            {
                saveScreener();
            }
            else{
                regex_t preg;
                int err;
                char* reg = "[0-3]{10}|[01]{8}";

                err =  regcomp(&preg,reg,0);
                if(err  != 0){
                    printf("regex faile\n");
                    return err;
                }else{

                    int match = regexec(&preg,str,0,NULL,0);

                    regfree(&preg);

                    if(match!=0){
                        printf("argument invalide\n");
                        return EXIT_FAILURE;
                    }else{
                        rule = argv[1];
                    }
                }

            }
        }else{
            rule = "00011110";
        }
    }


    
    /* int keep_running = 1;
    
    fd_set t; */
/* int x=0;
    while(1) x = tgetent(NULL,getenv("TERM")); */
    


    /* char* rule = "00011110";
    char* rule2 = "0100000000";
    char* rule3 = "0013100132"; */
    // char* rule = "00011110";
    // const char* rule = "01011010";

    
    /* cell line0 = lineGen(NULL,"");
    lineDisplay(line0,0);
    cell line1 = lineGen(line0,"00011110");
    lineDisplay(line1,1);
 */
    // clear_term();
        rule = "00011110";
        Autom a = automateGen(rule);
        rule = NULL;
        generiqueDisplay(a,fancyAutomateDisplay);
        // generiqueDisplay(a,displayAutomate);
        free(a->linesSave);
        free(a);
        a = NULL;
    
    // free(tc_cmd.ab);
    // exit(EXIT_SUCCESS);
    // free(a->currentLine);

    



   /*  cell *lineN = NULL;
    for(int i=0;i<NLI-1;i++){

        lineN = lineGen(lineN,rule);
        // lineDisplay(lineN,i);
        
    }
    for (int i = 0; i<NCOL;i++){
        //    printf("sizeof cellule = %ld \n",sizeof(line[i]));
            free(lineN[i]);

        }
    free(lineN); */
    // freeTabCell(lineN,NCOL);
   
    // puts("");
    // printf("NCOL = %d\n",NCOL);
    // getNghd(&line0[5],line0);
    // cell soustab = subTab(0,6,line0,NCOL);
    // afficherTabCell(soustab,6);

    // // // // // tputs(tc_cmd.ve,1,putchar);
            
    
    //clear_term();

    // tputs(tc_cmd.reset,1,putchar);

    // fflush(stdout);
    // freestc(&tc_cmd);
    //free(&tc_cmd);
    /* srand(time(NULL));
    for (int i = 0;i<5;i++){
    // int x =(int)(rand() / RAND_MAX * (0 - 1));
    printf("rulegen =  %s\n",ruleGen(10));
    } */
    // clearenv();
    return EXIT_SUCCESS;

}
