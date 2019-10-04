

#include "../header/utils.h"
#include "../header/automate.h"

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

	for(int i =0;i<10;i++){

        rule = ruleGen(10);
        Autom a = automateGen(rule);
        free(rule);
        rule = NULL;
        // generiqueDisplay(a,fancyAutomateDisplay);
        free(a->linesSave);
        free(a);
        a = NULL;
    }
}