/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_math.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:23:13 by inikulin          #+#    #+#             */
/*   Updated: 2024/05/01 14:41:40 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_internal.h"
#include <math.h>

double	flr(double c)
{
	return ((int)c);
}

double	fpart(double c)
{
	return (c - flr(c));
}

double	rfpart(double c)
{
	return (1.0 - fpart(c));
}

double	rnd(double c)
{
	return (flr(c + 0.5));
}
