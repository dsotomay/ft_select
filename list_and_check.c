/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_and_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dysotoma <dysotoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 21:56:59 by dysotoma          #+#    #+#             */
/*   Updated: 2019/05/06 19:15:00 by dysotoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void		init_arg_list(char **av)
{
	int i;

	i = 1;
	g_select.list = sl_list_init(av[i++]);
	while (av[i])
		push_back(g_select.list, av[i++]);
	g_select.list->is_current = 1;
}

t_sl_list	*sl_list_init(void *content)
{
	t_sl_list	*new;

	if (!(new = (t_sl_list*)ft_memalloc(sizeof(t_sl_list))))
		return (NULL);
	new->next = new;
	new->prev = new;
	new->content = content;
	return (new);
}

void		push_back(t_sl_list *root, void *content)
{
	t_sl_list *new;

	new = sl_list_init(content);
	if (!root)
		root = new;
	else
	{
		new->prev = root->prev;
		new->next = root;
		root->prev->next = new;
		root->prev = new;
	}
}

void		*pop(t_sl_list *list)
{
	void		*content;
	t_sl_list	*tmp;

	if (!list)
		return (NULL);
	list->is_current = 0;
	content = list->content;
	tmp = list->next;
	if (tmp)
	{
		list->next->prev = list->prev;
		list->prev->next = list->next;
	}
	g_select.list = g_select.list == list ? tmp : g_select.list;
	ft_memdel((void**)&list);
	list = tmp;
	if (list)
		list->is_current = 1;
	return (content);
}

int			up_down_check(t_sl_list *head, int n, unsigned long c)
{
	t_sl_list	*cpy;

	cpy = head;
	while (n)
	{
		cpy = cpy->next;
		if ((c == DOWN && cpy == g_select.list) ||
			(c == UP && head == g_select.list))
			return (0);
		head = head->prev;
		n--;
	}
	return (1);
}
