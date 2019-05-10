/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dysotoma <dysotoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 18:00:55 by dysotoma          #+#    #+#             */
/*   Updated: 2019/05/06 20:10:42 by dysotoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include <sys/stat.h>

static void	set_color(char *path)
{
	struct stat	buf;

	if (lstat(path, &buf) == -1)
		ft_putstr_fd(RESTORE, STDERR_FILENO);
	else if (S_ISDIR(buf.st_mode))
		ft_putstr_fd(BLUE, STDERR_FILENO);
	else if (S_ISLNK(buf.st_mode))
		ft_putstr_fd(MAGENTA, STDERR_FILENO);
	else if (buf.st_mode & S_IXUSR)
		ft_putstr_fd(RED, STDERR_FILENO);
}

static void	check_col(void)
{
	g_select.term.row++;
	if (g_select.term.row > g_select.ws.ws_row)
	{
		clear_screen();
		ft_errprintf("Not enough space for arguments. Please resize!\n");
	}
	else
		ft_putchar_fd('\n', STDERR_FILENO);
}

static void	print(t_sl_list *head, int width)
{
	if (head->is_current && head->is_selected)
		print_select_curr((char*)head->content, width);
	else if (head->is_selected)
		print_selected((char*)head->content, width);
	else if (head->is_current)
		print_curr((char*)head->content, width);
	else
		ft_errprintf("%-*s", width + 1, (char*)head->content);
}

static void	handle_print(t_sl_list *head, int width)
{
	int	tmp;
	int	i;

	i = 0;
	clear_screen();
	while (head)
	{
		tmp = width + 1;
		i += tmp;
		if (i > g_select.ws.ws_col && (i = tmp))
			check_col();
		set_color((char*)head->content);
		g_select.term.row <= g_select.ws.ws_row ? print(head, width) : 0;
		ft_putstr_fd(RESTORE, STDERR_FILENO);
		if ((head = head->next) && head == g_select.list)
			break ;
	}
}

void		print_list(void)
{
	int			longest_arg;
	int			tmp;
	t_sl_list	*head;

	head = g_select.list;
	longest_arg = 0;
	g_select.term.row = 1;
	while (head)
	{
		tmp = ft_strlen((char*)head->content);
		if (tmp > longest_arg)
			longest_arg = tmp;
		if ((head = head->next) && head == g_select.list)
			break ;
	}
	g_select.term.width = longest_arg + 1;
	if (longest_arg + 1 > g_select.ws.ws_col)
	{
		clear_screen();
		ft_errprintf("Not enough space for arguments. Please resize!\n");
	}
	else
		handle_print(head, longest_arg);
}
