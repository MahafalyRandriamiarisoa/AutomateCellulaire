// ce code n'est pas le mien :https://github.com/Glordim/Termcap_Tetris/blob/master/src/termcap_initializer.c

#include "../header/termcap_initializer.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define USE_TERMCAP

struct s_termcap_cmd tc_cmd;

int init_termcap()
{

	int ret;
	char *term_name = getenv("TERM");

	if (term_name == NULL)
	{
		fprintf(stderr, "Specify a terminal type with 'TERM=<type>'.\n");
		return -1;
	}

	ret = tgetent(NULL, term_name);

	if (ret == -1)
	{
		fprintf(stderr, "Could not access the termcap data base.\n");
		return -1;
	}
	else if (ret == 0)
	{
		fprintf(stderr, "Terminal type '%s' is not defined in termcap database (or too little information).\n", term_name);
		return -1;
	}

	tc_cmd.cl = tgetstr("cl", NULL);
	tc_cmd.cm = tgetstr("cm", NULL);
	tc_cmd.vi = tgetstr("vi", NULL);
	tc_cmd.ve = tgetstr("ve", NULL);
	tc_cmd.ab = tgetstr("AB", NULL);
    tc_cmd.af = tgetstr("AF", NULL);
    tc_cmd.reset = tgetstr("me", NULL);

	tc_cmd.ku = tgetstr("ku", NULL);
	tc_cmd.kd = tgetstr("kd", NULL);
	tc_cmd.kl = tgetstr("kl", NULL);
	tc_cmd.kr = tgetstr("kr", NULL);

    return 0;
}
