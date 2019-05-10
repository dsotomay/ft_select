/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dysotoma <dysotoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 14:51:07 by dysotoma          #+#    #+#             */
/*   Updated: 2019/05/06 19:14:43 by dysotoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void	up_down(unsigned long c, t_sl_list **head)
{
	int			arg_line_count;
	int			i;
	t_sl_list	*cpy;

	arg_line_count = 0;
	i = 0;
	(*head)->is_current = 0;
	cpy = (*head)->prev;
	while ((cpy = cpy->next))
	{
		i += g_select.term.width;
		if (i > g_select.ws.ws_col)
			break ;
		arg_line_count++;
	}
	if (!up_down_check(*head, arg_line_count, c) && ((*head)->is_current = 1))
		return ;
	while (arg_line_count)
	{
		(*head) = c == UP ? (*head)->prev : (*head)->next;
		arg_line_count--;
	}
	(*head)->is_current = 1;
	print_list();
}

static void	left_right(unsigned long c, t_sl_list **head)
{
	(*head)->is_current = 0;
	(*head) = c == LEFT ? (*head)->prev : (*head)->next;
	(*head)->is_current = 1;
	print_list();
}

static void	my_select(t_sl_list **head)
{
	(*head)->is_current = 0;
	(*head)->is_selected = !(*head)->is_selected ? 1 : 0;
	(*head) = (*head)->next;
	(*head)->is_current = 1;
	print_list();
}

static void	remove_exit(unsigned long c, t_sl_list **head)
{
	if (*head && *head == (*head)->next)
		(*head)->next = NULL;
	if ((c == ESCAPE || (pop(*head) && !(*head)->next)) && restore_terminal())
		exit(0);
	*head = (*head)->next;
	print_list();
}

void		input_loop(void)
{
	unsigned long	c;
	t_sl_list		*head;

	head = g_select.list;
	sig_handle();
	c = 0;
	while (c != ENTER)
	{
		c = 0;
		read(STDERR_FILENO, &c, 6);
		if (c == LEFT || c == RIGHT)
			left_right(c, &head);
		else if (c == UP || c == DOWN)
			up_down(c, &head);
		else if (c == SPACE)
			my_select(&head);
		else if (c == DELETE || c == BACKSPACE || c == ESCAPE)
			remove_exit(c, &head);
	}
}
