/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_limits.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 16:39:56 by inikulin          #+#    #+#             */
/*   Updated: 2024/05/01 14:31:57 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_internal.h"

void	limits_init(t_screen *s, t_point *p)
{
	s->map.xmin = p->x;
	s->map.xmax = p->x;
	s->map.ymin = p->y;
	s->map.ymax = p->y;
	s->map.zmin = p->z;
	s->map.zmax = p->z;
}

void	limits_adjust(t_screen *s, t_point *p)
{
	s->map.xmin = *ft_min_dbl(&s->map.xmin, &p->x);
	s->map.xmax = *ft_max_dbl(&s->map.xmax, &p->x);
	s->map.ymin = *ft_min_dbl(&s->map.ymin, &p->y);
	s->map.ymax = *ft_max_dbl(&s->map.ymax, &p->y);
	s->map.zmin = *ft_min_dbl(&s->map.zmin, &p->z);
	s->map.zmax = *ft_max_dbl(&s->map.zmax, &p->z);
}

void	pad(t_screen *s, double xpad, double ypad)
{
	int		r;
	int		c;
	double	*z;

	r = -1;
	while (++ r < s->map.height)
	{
		c = -1;
		while (++ c < s->map.width)
		{
			s->map.nodes[r][c].x += xpad;
			s->map.nodes[r][c].y += ypad;
			z = &s->map.nodes[r][c].z;
		}
	}
}
