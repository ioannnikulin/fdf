/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:01:40 by inikulin          #+#    #+#             */
/*   Updated: 2024/03/30 22:25:00 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <limits.h>
#include "libft.h"

static char	sign(const char *nptr, size_t *cur)
{
	char	res;

	res = 1;
	while (ft_isspace(nptr[*cur]) || nptr[*cur] == '-' || nptr[*cur] == '+')
	{
		if (nptr[*cur] == '-')
			res *= -1;
		*cur ++;
	}
	if (!ft_isdigit(nptr[cur]))
		return (0);
	return (res);
}

static int	ret(int what, int *ok, int okv)
{
	if (ok)
		*ok = okv;
	return (what);
}

int	ft_atoi(const char *nptr, int *ok)
{
	long	res;
	char	sign;
	size_t	cur;

	res = 0;
	cur = 0;
	if (!(sign = sign(nptr, &cur)))
		return(ret(0, ok, 0));
	while (nptr[cur] && ft_isdigit(nptr[cur]))
	{
		res = res * 10 + nptr[cur ++] - '0';
		if ((sign == 1 && res > INT_MAX) || -res < INT_MIN)
			return (ret(0, ok, 0));
	}
	return (ret((int)(sign * res), ok, 1));
}
