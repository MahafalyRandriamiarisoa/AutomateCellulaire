#include <stdlib.h>
#include <stdio.h>
#include <sys/select.h>
#include <time.h>
#include <regex.h>

#include "header/automate.h"
#include "header/termcap_initializer.h"
#include "header/pgm_img.h"




int main(int argc,char** argv){


    init_termcap(NULL);
    COL = tgetnum("co");
    LI = (tgetnum("li")-1);
    char* rule = "00011110";
        int width = NCOL;
        _Rule _rule = initRule(rule,applyRule);
        // Autom a = automateGen(rule,1,1,width,NLI,width/2,_rule);
    Autom a = lireConfFile("conf"); 



    if(argc>2){
        printf("trop d'arguments");
        exit(EXIT_FAILURE);
    }else{
        if(argc==2){
            char* str = argv[1];
            if (strcmp(str,"sc")==0)
            {
                saveScreener();
            }
            else{
                if (strcmp(str,"pgm")==0) //création d'une image pgm
            {
                generiqueDisplay(a,automateDisplayInPGM);
            }
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
    // generiqueDisplay(a,fancyAutomateDisplay);

        generiqueDisplay(a,displayAutomate);

    
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


// int **tab2 = malloc(sizeof(int*) * 10);
 
// for(int i = 0; i < 10; i++){
//     tab2[i] = malloc(sizeof(int) * 20);
// }
//     int count = 0;
//     for(int i=0;i<10;i++){
//         for(int j = 0;j<20;j++){
//             tab2[i][j] = j%10;
//         }
//     }



        /* rule = "00011110";
        int width = NCOL;
        _Rule _rule = initRule(rule,applyRule);
        Autom a = automateGen(rule,1,1,width,NLI,width/2,_rule);
        rule = NULL; */
        
        // generiqueDisplay(a,fancyAutomateDisplay);
    
        // generiqueDisplay(a,displayAutomate);

        // displayTab2int(tab2d,NLI,NCOL);
        // displayTab2int(tab2,10,20);
        // printf("NLI = %d\nNCOL = %d\n",NLI,NCOL);
       /*  int** tab2d = tabstrToTab2dInt(a->linesSave,NLI,NCOL);
        pgm p = creer_image_pgm(NCOL,NLI,1,tab2d); */
        /* free(a->linesSave);
        free(a);
        a = NULL; */

        // free(tab2d);

        // lireConfFile("conf");
        /* ecrire_image_pgm("TEST3.pgm", p );
        detruire_image_pgm(&p);
        char*t = extractREGEX("azer",".*.*"); */
        /* if(strcmp("azer",t)==0){
            printf("ohh%s\n",t);
        }else{
            printf("AAAAhh: %s\n",t);
        } */
        /* for(int i = 0; i<NLI; i++){

            int * t = p->image[i];
            
            free(t);
        }
        
        free(p->image); */
        // free(p);

       /*  if(p==NULL){
            printf("PUTAIN\n");
        }

        char * chaine = extractREGEX("arez10000111egz","([01]{8})");
        printf("%s\n",chaine);
        free(chaine); */

    
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

   /*  char*test = calloc(3,(sizeof(char)*3));
    test[0] = 'o';
    test[1] = 'u';
    strcat(test,"\0");
    test[3] = '!';
    printf("%ld\n",strlen(test)); */

    return EXIT_SUCCESS;

}
