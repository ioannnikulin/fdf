/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_pixel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:23:13 by inikulin          #+#    #+#             */
/*   Updated: 2024/05/01 14:52:25 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_internal.h"

int	higher(t_color a, t_color b)
{
	if (b.r == 0 && b.g == 0 && b.b == 0)
		return (1);
	if (a.r == 0 && a.g == 0 && a.b == 0)
		return (0);
	if (*ft_max_dbl(&a.clr, &b.clr) == a.clr 
		&& *ft_max_dbl(&a.clr, &b.clr) != b.clr)
		return (1);
	return (0);
}

t_color	color(double clr, double alpha)
{
	t_color	res;

	res.r = 255 * alpha;
	res.g = 255 * (1 - clr) * alpha;
	res.b = res.g;
	res.clr = clr;
	res.alpha = alpha;
	return (res);
}

void	pixel(t_screen *s, int x, int y, t_color clr)
{
	int		tgt;
	t_color	cur;

	if (x < 0 || x > WIN_WIDTH || y < 0 || y > WIN_HEIGHT)
		return ;
	tgt = y * s->img.linesz + x * s->img.bpp / 8;
	cur.r = s->img.data[tgt + s->img.rd];
	cur.g = s->img.data[tgt + s->img.gd];
	cur.b = s->img.data[tgt + s->img.bd];
	if (higher(clr, cur))
	{
		s->img.data[tgt + s->img.rd] = clr.r;
		s->img.data[tgt + s->img.gd] = clr.g;
		s->img.data[tgt + s->img.bd] = clr.b;
	}
}
