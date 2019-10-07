#include <stdlib.h>
#include <stdio.h>
#include <sys/select.h>
#include <time.h>
#include <regex.h>

#include "header/automate.h"
#include "header/termcap_initializer.h"
#include "header/pgm_img.h"




int main(int argc,char** argv){


    init_termcap(NULL);//termcap ne me permet pas de libérer il y a donc des 
    COL = tgetnum("co");  
    LI = (tgetnum("li")-1);
    // char* rule;
    int width = NCOL;
    // _Rule _rule = initRule(rule,applyRule);
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

                }else{
                    if(strcmp(str,"std")==0){
                            generiqueDisplay(a,displayAutomate);
                    }else{

                        if(strcmp(str,"fcy")==0){
                            generiqueDisplay(a,fancyAutomateDisplay);
                        }else{
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
                                    free(a->_rule->rule);
                                    a->_rule->rule = argv[1];
                                }   
                            }
                        }
                    }
                    
                }
            }
        }else{
            free(a->_rule->rule);
            a->_rule->rule = "00011110";
        }
    }
    // free(a->_rule->rule);
    free(a->_rule);
    free(a->linesSave);
    free(a);
    // generiqueDisplay(a,fancyAutomateDisplay);

        // generiqueDisplay(a,displayAutomate);

    
    

    return EXIT_SUCCESS;

}
