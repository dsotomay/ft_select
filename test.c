#include <termcap.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"

static int	check_term_info(void)
{
	static char term_buff[2048];
	char		*termtype;
	int			success;

	if (!(termtype = getenv("TERM")))
	{
		printf("No terminal type. Please set with setenv TERM <type>.\n");
		exit(EXIT_FAILURE);
	}
	if ((success = tgetent(term_buff, termtype)) < 0)
	{
		printf("Couldn't access the termcaps databse.\n");
		exit(EXIT_FAILURE);
	}
	if (success == 0)
	{
		printf("Undefined terminal type %s.\n", termtype);
		exit(EXIT_FAILURE);
	}
	return (1);
}

int main()
{
	char buf[30];
	check_term_info();
	ft_errprintf("%s%shello%s%s", tgetstr("so", (char**)&buf), tgetstr("us",
	 (char**)&buf), tgetstr("se", (char**)&buf), tgetstr("ue", (char**)&buf));
}