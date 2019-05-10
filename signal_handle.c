/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dysotoma <dysotoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 16:45:51 by dysotoma          #+#    #+#             */
/*   Updated: 2019/05/06 22:10:14 by dysotoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void	screen_resize(int sig)
{
	if (sig == SIGWINCH)
	{
		clear_screen();
		get_screen_size();
		print_list();
	}
}

static void	suspend(int sig)
{
	if (sig == SIGTSTP)
	{
		restore_terminal();
		clear_screen();
		signal(SIGTSTP, SIG_DFL);
		ioctl(STDERR_FILENO, TIOCSTI, "\x1A");
	}
}

static void	my_kill(int sig)
{
	(void)sig;
	restore_terminal();
	exit(0);
}

static void	resume(int sig)
{
	if (sig == SIGCONT)
	{
		get_screen_size();
		prepare_terminal();
		clear_screen();
		print_list();
		sig_handle();
	}
}

void		sig_handle(void)
{
	signal(SIGWINCH, screen_resize);
	signal(SIGTSTP, suspend);
	signal(SIGCONT, resume);
	signal(SIGINT, my_kill);
	signal(SIGABRT, my_kill);
	signal(SIGFPE, my_kill);
	signal(SIGILL, my_kill);
	signal(SIGSEGV, my_kill);
	signal(SIGTERM, my_kill);
}
