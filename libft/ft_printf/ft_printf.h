/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dysotoma <dysotoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 13:57:12 by dysotoma          #+#    #+#             */
/*   Updated: 2019/05/06 19:06:19 by dysotoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include "../../libft/libft.h"
# define MAX_BUFF (size_t)1024 * type->count - 2

typedef	struct	s_type
{
	char	*str;
	char	*buff;
	size_t	bytes;
	int		count;
	int		width;
	int		precision;
}				t_type;

typedef	void	(*t_func)(int *formatted, va_list arg, t_type *type, int base);

/*
** struct t_func			spec
** {
** 	t_func	funct[128];
** 	funct[(int)'s'] = s;
** 	funct[(int)'S'] = up_s;
** 	funct[(int)'p'] = p;
** 	funct[(int)'d'] = d;
** 	funct[(int)'D'] = up_d;
** 	funct[(int)'i'] = i;
** 	funct[(int)'o'] = o;
** 	funct[(int)'O'] = up_o;
** 	funct[(int)'u'] = u;
** 	funct[(int)'U'] = up_u;
** 	funct[(int)'x'] = x;
** 	funct[(int)'X'] = up_x;
** 	funct[(int)'c'] = c;
** 	funct[(int)'C'] = up_c;
** };
*/

typedef	struct	s_dispatch
{
	void	(*func)(int *formatted, va_list arg, t_type *type, int base);
}				t_dispatch;

int				ft_printf(char *format, ...);
int				ft_sprintf(char *str, char *format, ...);
int				ft_errprintf(char *format, ...);
void			parse(char *format, va_list arg, int *i, t_type *type);
void			handle(char *format, va_list arg, int *i, t_type *type);
void			resize(t_type *type);
int				flags(char c);
int				length(char c);
int				specifier(char c);
void			set_specifier(int *formatted, va_list arg, t_type *type);
void			set_length(int *formatted, va_list arg, t_type *type, int base);
void			set_width(char *format, va_list arg, int *i, t_type *type);
int				check_length(int *formatted);
void			put_min_max_width(int *formatted, t_type *type);
void			reset(int *formatted);
void			width(int *formatted, t_type *type, int i);
t_func			spec(int num);

/*
**	specifiers
*/

void			s(int *formatted, va_list arg, t_type *type, int base);
void			up_s(int *formatted, va_list arg, t_type *type, int base);
void			p(int *formatted, va_list arg, t_type *type, int base);
void			d(int *formatted, va_list arg, t_type *type, int base);
void			up_d(int *formatted, va_list arg, t_type *type, int base);
void			i(int *formatted, va_list arg, t_type *type, int base);
void			o(int *formatted, va_list arg, t_type *type, int base);
void			up_o(int *formatted, va_list arg, t_type *type, int base);
void			u(int *formatted, va_list arg, t_type *type, int base);
void			up_u(int *formatted, va_list arg, t_type *type, int base);
void			x(int *formatted, va_list arg, t_type *type, int base);
void			up_x(int *formatted, va_list arg, t_type *type, int base);
void			c(int *formatted, va_list arg, t_type *type, int base);
void			up_c(int *formatted, va_list arg, t_type *type, int base);

/*
**	length
*/

void			h(int *formatted, va_list arg, t_type *type, int base);
void			hh(int *formatted, va_list arg, t_type *type, int base);
void			l(int *formatted, va_list arg, t_type *type, int base);
void			ll(int *formatted, va_list arg, t_type *type, int base);
void			j(int *formatted, va_list arg, t_type *type, int base);
void			z(int *formatted, va_list arg, t_type *type, int base);

/*
**	flags
*/

void			hash(int *formatted, t_type *type);
void			minus_plus(int *formatted, t_type *type);

#endif
