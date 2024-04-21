/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minmax_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 14:28:56 by inikulin          #+#    #+#             */
/*   Updated: 2024/04/21 19:47:02 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>

char	*ft_min_c(char *a, char *b)
{
	if (*a < *b)
		return (a);
	return (b);
}

char	*ft_max_c(char *a, char *b)
{
	if (*a > *b)
		return (a);
	return (b);
}

char	*ft_min_c_va(int sz, ...)
{
	char		*res;
	char		*cur;
	va_list	args;

	va_start(args, sz);
	res = va_arg(args, char *);
	while (-- sz)
	{
		cur = va_arg(args, char *);
		if (*cur < *res)
			res = cur;
	}
	return (res);
}

char	*ft_max_c_va(int sz, ...)
{
	char		*res;
	char		*cur;
	va_list	args;

	va_start(args, sz);
	res = va_arg(args, char *);
	while (-- sz)
	{
		cur = va_arg(args, char *);
		if (*cur > *res)
			res = cur;
	}
	return (res);
}
