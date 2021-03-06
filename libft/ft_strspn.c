/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dysotoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 15:30:38 by dysotoma          #+#    #+#             */
/*   Updated: 2018/09/25 15:31:01 by dysotoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strspn(const char *s1, const char *s2)
{
	size_t	ret;

	ret = 0;
	while (*s1 && ft_strchr(s2, *s1++))
		ret++;
	return (ret);
}
