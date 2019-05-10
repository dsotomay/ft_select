/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dysotoma <dysotoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 18:01:21 by dysotoma          #+#    #+#             */
/*   Updated: 2019/05/06 21:43:21 by dysotoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# define LEN(x) ft_strlen(x)

# include <termcap.h>
# include <termios.h>
# include <signal.h>
# include <sys/ioctl.h>
# include "libft/libft.h"

# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define YELLOW "\x1b[33m"
# define BLUE "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN "\x1b[36m"
# define WHITE "\x1b[37m"
# define RESTORE "\x1b[0m"

# define SPACE 0x20
# define ENTER 0xA
# define ESCAPE 0x1B
# define UP 0x415B1B
# define DOWN 0x425B1B
# define RIGHT 0x435B1B
# define LEFT 0x445B1B
# define BACKSPACE 0x7F
# define DELETE 0x7E335B1B

typedef struct s_sl_list	t_sl_list;
struct			s_sl_list
{
	t_sl_list	*prev;
	t_sl_list	*next;
	void		*content;
	int			is_selected;
	int			is_current;
};

typedef struct	s_sl_terminfo
{
	int				row;
	int				width;
	struct termios	old;
	struct termios	new;
}				t_sl_terminfo;

typedef struct	s_select
{
	t_sl_list		*list;
	t_sl_terminfo	term;
	struct winsize	ws;
}				t_select;

/*
** input and validation
*/

void			input_loop(void);
int				up_down_check(t_sl_list *head, int n, unsigned long c);

/*
** Signal
*/

void			sig_handle(void);

/*
** Print
*/

void			clear_screen(void);
void			print_curr(char *str, int width);
void			print_selected(char *str, int width);
void			print_select_curr(char *str, int width);
void			print_list(void);

/*
** Terminal
*/

void			prepare_terminal(void);
int				restore_terminal(void);
void			get_screen_size(void);

/*
** List
*/

void			init_arg_list(char **av);
t_sl_list		*sl_list_init(void *content);
void			push_back(t_sl_list *root, void *content);
void			*pop(t_sl_list *list);

/*
** Global
*/

t_select		g_select;

#endif
