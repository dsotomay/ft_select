/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_and_resize_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dysotoma <dysotoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 18:07:23 by dysotoma          #+#    #+#             */
/*   Updated: 2019/05/06 19:12:56 by dysotoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	clear_screen(void)
{
	char buf[30];
	char *clear;

	clear = buf;
	ft_errprintf("%s", tgetstr("cl", &clear));
}

void	print_curr(char *str, int width)
{
	char	*print;
	char	buff[2048];

	print = buff;
	ft_bzero(print, 2048);
	ft_errprintf("%s%-*s%s ", tgetstr("us", &print), width, str,
	tgetstr("ue", &print));
}

void	print_selected(char *str, int width)
{
	char	*print;
	char	buff[2048];

	print = buff;
	ft_bzero(print, 2048);
	ft_errprintf("%s%-*s%s ", tgetstr("so", &print), width, str,
	tgetstr("se", &print));
}

void	print_select_curr(char *str, int width)
{
	char	*print;
	char	buff[2048];

	print = buff;
	ft_bzero(print, 2048);
	ft_errprintf("%s%s%-*s%s%s ", tgetstr("so", &print), tgetstr("us", &print),
	width, str, tgetstr("se", &print), tgetstr("ue", &print));
}

void	get_screen_size(void)
{
	ioctl(STDERR_FILENO, TIOCGWINSZ, &g_select.ws);
}
