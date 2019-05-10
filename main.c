/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dysotoma <dysotoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 16:47:37 by dysotoma          #+#    #+#             */
/*   Updated: 2019/05/06 20:25:53 by dysotoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void	print_select(void)
{
	int first;

	first = 1;
	while (g_select.list)
	{
		if (!first && g_select.list->is_selected)
			ft_putchar(' ');
		if (g_select.list && g_select.list->is_selected)
		{
			if (g_select.list && g_select.list == g_select.list->next)
				g_select.list->next = NULL;
			ft_printf("%s", (char*)pop(g_select.list));
			first = 0;
		}
		else
		{
			if (g_select.list == g_select.list->next)
				g_select.list->next = NULL;
			pop(g_select.list);
		}
	}
	ft_putchar('\n');
}

static int	check_term_info(void)
{
	static char term_buff[2048];
	char		*termtype;
	int			success;

	if (!(termtype = getenv("TERM")))
	{
		ft_errprintf("No terminal type. Please set with setenv TERM <type>.\n");
		exit(EXIT_FAILURE);
	}
	if ((success = tgetent(term_buff, termtype)) < 0)
	{
		ft_errprintf("Couldn't access the termcaps databse.\n");
		exit(EXIT_FAILURE);
	}
	if (success == 0)
	{
		ft_errprintf("Undefined terminal type %s.\n", termtype);
		exit(EXIT_FAILURE);
	}
	return (1);
}

void		prepare_terminal(void)
{
	char	*print;
	char	buf[30];

	print = buf;
	tcgetattr(STDERR_FILENO, &g_select.term.old);
	tcgetattr(STDERR_FILENO, &g_select.term.new);
	g_select.term.new.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDERR_FILENO, TCSANOW, &g_select.term.new);
	ft_errprintf("%s%s", tgetstr("vi", &print),
						tgetstr("ti", &print));
	g_select.term.row = 1;
}

int			restore_terminal(void)
{
	char	*print;
	char	buf[30];

	print = buf;
	ft_bzero(print, 30);
	tcsetattr(STDERR_FILENO, TCSANOW, &g_select.term.old);
	ft_errprintf("%s%s", tgetstr("ve", &print), tgetstr("te", &print));
	return (1);
}

int			main(int ac, char **av)
{
	if (check_term_info() && ac < 2)
	{
		ft_errprintf("Error: No arguments found!\n");
		exit(EXIT_FAILURE);
	}
	prepare_terminal();
	get_screen_size();
	init_arg_list(av);
	print_list();
	input_loop();
	restore_terminal();
	print_select();
}
