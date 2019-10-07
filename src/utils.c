

#include "../header/utils.h"
#include "../header/automate.h"
#include <string.h>

int mod(int a,int b){ 

    return (a % b + b) % b;
}

int bin_to_int(char*s){

    int n = 0;
    for(int i = 0;i<(int)strlen(s);i++){
        char c = s[strlen(s)-1-i];
        n+=atoi(&c)*pow(2,i);
    }
        return n;

}

// bout de code tiré de : http://graphics.stanford.edu/~seander/bithacks.html#IntegerLog10Obvious
int nb_char_int(int v){
    return (v >= 1000000000) ? 9 : (v >= 100000000) ? 8 : (v >= 10000000) ? 7 : 
    (v >= 1000000) ? 6 : (v >= 100000) ? 5 : (v >= 10000) ? 4 : 
    (v >= 1000) ? 3 : (v >= 100) ? 2 : (v >= 10) ? 1 : 0;
}

void strreverse(char* begin, char* end) {
	
	char aux;
	
	while(end>begin)
	
		aux=*end, *end--=*begin, *begin++=aux;
	
}
	
void itoa(int value, char* str, int base) {
	
	static char num[] = "0123456789abcdefghijklmnopqrstuvwxyz";
	
	char* wstr=str;
	
	int sign;
	
	div_t res;
	


	
	// Validate base
	
	if (base<2 || base>35){ *wstr='\0'; return; }
	

	
	// Take care of sign
	
	if ((sign=value) < 0) value = -value;
	


	
	// Conversion. Number is reversed.
	
	do {
	
		res = div(value,base);
	
		*wstr++ = num[res.rem];
        value = res.quot;
	
	}while(value);
	
	if(sign<0) *wstr++='-';
	
	*wstr='\0';
	


	
	// Reverse string
	
	strreverse(str,wstr-1);
	
}

void saveScreener(){
	char* rule = NULL;
	setvbuf(stdout,NULL,_IOFBF,BUFSIZ);
	for(int i =0;i<1000;i++){
		// srand(time(NULL));
        rule = ruleGen(10);
		int width = NCOL;
		_Rule _rule = initRule(rule,applyRule);
		int pos = i%(width -1);
        Autom a = automateGen(3,3,width,NLI,pos,_rule);
		
        free(rule);
        rule = NULL;
        generiqueDisplay(a,fancyAutomateDisplay);
        free(a->linesSave);
        free(a);
        a = NULL;
		//fflush(stdout);
    }
}


int** tabstrToTab2dInt(char* str,int size_1D,int size_2D){

	int x=0,y=0;

	int** tab2dInt = (int**)calloc(size_1D,sizeof(int*)*size_1D);

	for(int i = 0; i < size_1D; i++){
		tab2dInt[i] = calloc(size_2D,sizeof(int) * size_2D);
	}


	for(int i= 0 ;i < (int) strlen(str); i++){

		char c = str[i];
		
		if(c == '\n')
		{
			x = 0;
			y++;
			
		}else{
			char* sc = (char*) calloc(2,sizeof(char)*2);
			sc[0] = c;
			strcat(sc,"\0");
			// printf("%c\n",sc[0]);
			int ic =  atoi(sc);
			free(sc);
			sc = NULL;
			tab2dInt[y][x] =ic;
			if(ic >1)printf("\nx = %d\ny = %d\nstr[%d]=%c and ic = %d\n",x,y,i,c,ic);
			x++;
		}
		

	}

	return tab2dInt;
}

void displayTab2int(int**tab2d,int size_1D,int size_2D){
	for(int i = 0; i<size_1D;i++){
		for(int j = 0; j< size_2D;j++){
			printf("%d",tab2d[i][j]);
		}
		puts("");
	}
}
bool regexBool(char*str,char*reg){
	regex_t preg;
	int err;
	// char* reg = "[0-3]{10}|[01]{8}";

	err =  regcomp(&preg,reg,0);
	if(err  != 0){
		printf("regex fail\n");
		regfree(&preg);
		return false;
	}else{

		int match = regexec(&preg,str,0,NULL,0);
		if(match!=0){
			// printf("match pas\n");
			regfree(&preg);
			return false;
		}else{
			// printf("match !\n");
			regfree(&preg);
			return true;
		}
	}
    regfree(&preg);
	return false;
}


Autom lireConfFile(const char* file){

	FILE* f = fopen(file,"rb");
	if(f == NULL) {
        fprintf(stderr, "Impossible d'ouvrir le fichier PGM en lecture");
        return NULL;
    }
	bool read = true;
	enum Steps {INIT, RULE,MAX_VALUE, FIRST_VALUE, WIDTH, HEIGHT,POSITION_FIRST_VALUE, END, ERROR };
	_Rule _rule;
	int MAX_V, FIRST_V, WDTH, HGHT,POSITION_FIRST_V;
	
	enum Steps step = INIT;
	const int MAX_LENGTH = 4096;

	char* buf = malloc(sizeof(char)*MAX_LENGTH);
	char* errormsg = (char*) calloc(MAX_LENGTH,sizeof(char)*MAX_LENGTH);
	// errormsg = "Erreur:";
	strcat(errormsg,"Erreur: ");
	char* info;
	int x=0;
	while(read){
		fgets(buf, MAX_LENGTH, f);
		// printf("buf = %s",buf);
		bool b;
		switch(step){

			case INIT:
				b =  regexBool(buf,"\\*\\*\\* INIT_FILE \\*\\*\\*");
				if(b == true ){
					step = RULE;
				
				}else{
					printf("error detected\n");
					step = ERROR;
					strcat(errormsg,"not an INIT FILE");
				}

				break;

			case RULE:
				// b =  regexBool(buf,"^RULE: [01]{8}|[03]{10}");
				b =  regexBool(buf,"RULE: \\d*");
				if(b){
					
					info = extractREGEX(buf,"([01]{8}|[0123]{10})");
					if(b){
					// printf("%s\n",info);
					_rule = initRule(info,applyRule);
					
					
					step = MAX_VALUE;
					}else{
						step = ERROR;
						strcat(errormsg," rule mal définis");
					}
					
				
				}else{
					step = ERROR;
					strcat(errormsg," rule mal définis");
				}
				break;
			case MAX_VALUE:
				b =  regexBool(buf,"MAX_VALUE: [01-9]*");
				if(b){
					info = extractREGEX(buf,"([01-9]+)");
					x = atoi(info);
					// printf("info = %d\n",x);
					if(x>=0){
						MAX_V = x ;
						step = FIRST_VALUE;
					}
					else {
						step = ERROR;
						printf("MAX VALUE = %d\n",x);
						strcat(errormsg," MAX_VALUE mal définis");
					}
					free(info);
					info = NULL;
				}else{
					step = ERROR;
					strcat(errormsg," MAX_VALUE mal définis");
				}	
				
				break;
			case FIRST_VALUE:
				b =  regexBool(buf,"FIRST_VALUE: \\d*");
				if(b){
					info = extractREGEX(buf,"([01-9]+)");
					// printf("info = %s\n",info);
					x = atoi(info);
					if(x>=0){
						FIRST_V = x;
						step = WIDTH;
					}
					else{
						step = ERROR;
						// printf("FIRST VALUE = %d\n",x);
						strcat(errormsg," FIRST_VALUE mal définis");
					}

					
					free(info);
					info = NULL;
				}else{
					step = ERROR;
					strcat(errormsg," FIRST_VALUE mal définis");
				}	
				
				break;


			case WIDTH:
				b =  regexBool(buf,"WIDTH: \\d*");
				if(b){
					info = extractREGEX(buf,"([01-9]+)");
					// printf("info = %s\n",info);
					x = atoi(info);
					if(x>=0){
						WDTH = x;
						step = HEIGHT;
					}
					else{
						step = ERROR;
						// printf("FIRST VALUE = %d\n",x);
						strcat(errormsg," FIRST_VALUE mal définis");
					}

					
					free(info);
					info = NULL;
				}else{
					step = ERROR;
					strcat(errormsg," WIDTH mal définis");
				}	
				
				break;

			case HEIGHT:
				b =  regexBool(buf,"HEIGHT: \\d*");
				if(b){
					info = extractREGEX(buf,"([01-9]+)");
					// printf("info = %s\n",info);
					x = atoi(info);
					free(info);
					info = NULL;
					if(x>=0){
						HGHT = x;
						step = POSITION_FIRST_VALUE;
					}
					else{
						step = ERROR;
						printf("FIRST VALUE = %d\n",x);
						strcat(errormsg," HEIGHT mal définis");
					}
					
				}else{
					step = ERROR;
					strcat(errormsg," WIDTH mal définis");
				}	
				
				break;

			case POSITION_FIRST_VALUE:
				b =  regexBool(buf,"POSITION_FIRST_VALUE: ");
				if(b){
					info = extractREGEX(buf,"(LEFT|CENTER|RIGHT|[01-9]+)");
					
					if(strcmp(info,"LEFT")==0){
						x = 0;
					}else{ 
						if(strcmp(info,"CENTER")==0){
						
							x =WDTH /2;
						}else{
							if(strcmp(info,"RIGHT")==0){
								x = WDTH - 1;
							}else{
								x = atoi(info);
							}
						}
					}
			
					if((x>=0) && (x< WDTH)){
							// printf("x pos = %d\n",x);
						POSITION_FIRST_V = x;
						step = END;
					}
					else{
						step = ERROR;
						// printf("HEROOR = %d\n",x);
						strcat(errormsg," POSITION_FIRST_VALUE mal définis");
					}
					free(info);
					info = NULL;
				}else{
					step = ERROR;
					strcat(errormsg," POSITION_FIRST_VALUE mal définis");
				}	
				
				break;

			case END: 
				printf("Lecture du fichier de configuration terminée !\n");
				read = false;
				break;
			case ERROR:
				printf("%s\n",errormsg);
				read = false;
				break;

			default:
				step = ERROR;
			
		}
	}
		free(buf);
	Autom ate = automateGen(MAX_V, FIRST_V, WDTH, HGHT,POSITION_FIRST_V, _rule);
	free(errormsg);
	fclose(f);
	return ate;
}

char* extractREGEX(char*req,char*pattern){
	int err;
   regex_t preg;
   const char *str_request = req;
   const char *str_regex = pattern;

   err = regcomp (&preg, str_regex, REG_EXTENDED);
   if (err == 0)
   {
      int match;
      size_t nmatch = 0;
      regmatch_t *pmatch = NULL;
      
      nmatch = preg.re_nsub;
      pmatch = malloc (sizeof (*pmatch) * nmatch);
      if (pmatch)
      {
         match = regexec (&preg, str_request, nmatch, pmatch, 0);
         regfree (&preg);
         if (match == 0)
         {
            char *sub_string = NULL;
            int start = pmatch[0].rm_so;
            int end = pmatch[0].rm_eo;
            size_t size = end - start;
               
            sub_string = malloc (sizeof (*sub_string) * (size + 1));
		 
            if (sub_string)
            {
            	strncpy (sub_string, &str_request[start], size);
            	sub_string[size] = '\0';
				free(pmatch);
			   return sub_string;
            }
         }
         else if (match == REG_NOMATCH)
         {
            printf ("%s PATTERN NON TROUVE\n", str_request);
         }
         else
         {
            char *text;
            size_t size;

            size = regerror (err, &preg, NULL, 0);
            text = malloc (sizeof (*text) * size);
            if (text)
            {
               regerror (err, &preg, text, size);
               fprintf (stderr, "%s\n", text);
               free (text);
            }
            else
            {
               fprintf (stderr, "Memoire insuffisante\n");
               exit (EXIT_FAILURE);
            }
         }
		 free(pmatch);
      }
      else
      {
		  free(pmatch);
         fprintf (stderr, "Memoire insuffisante\n");
         exit (EXIT_FAILURE);
      }
	  
   }
   return "";
}