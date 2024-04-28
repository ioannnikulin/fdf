/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 16:39:56 by inikulin          #+#    #+#             */
/*   Updated: 2024/04/28 20:42:33 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_internal.h"
#include <math.h>

static char	*free_nodes(t_map *m, int n, char * ret)
{
	while (--n > 0)
		free(m->nodes[n]);
	free(m->nodes);
	m->nodes = 0;
	return (ret);
}

static void	limits_init(t_screen *s, t_point *p)
{
	s->map.xmin = p->x;
	s->map.xmax = p->x;
	s->map.ymin = p->y;
	s->map.ymax = p->y;
	s->map.zmin = p->z;
	s->map.zmax = p->z;
}

static void	limits_adjust(t_screen *s, t_point *p)
{
	s->map.xmin = *ft_min_dbl(&s->map.xmin, &p->x);
	s->map.xmax = *ft_max_dbl(&s->map.xmax, &p->x);
	s->map.ymin = *ft_min_dbl(&s->map.ymin, &p->y);
	s->map.ymax = *ft_max_dbl(&s->map.ymax, &p->y);
	s->map.zmin = *ft_min_dbl(&s->map.zmin, &p->z);
	s->map.zmax = *ft_max_dbl(&s->map.zmax, &p->z);
}

static void	make_nodes(t_screen *s)
{
	int	r;
	int	c;

	s->map.nodes = ft_calloc(s->map.height, sizeof(t_point *));
	if (!s->map.nodes)
		finalize(s, "no memory for nodes");
	r = -1;
	while (++r < s->map.height)
	{
		s->map.nodes[r] = ft_calloc(s->map.width, sizeof(t_point));
		if (!s->map.nodes[r])
			finalize(s, free_nodes(&(s->map), r, "no memory for nodes"));
		c = -1;
		while (++c < s->map.width)
		{
			s->map.nodes[r][c].x = MARGIN + c * STEP;
			s->map.nodes[r][c].y = MARGIN + r * STEP;
			s->map.nodes[r][c].z = s->map.vals[r * s->map.width + c] * STEP;
		}
	}
	limits_init(s, &s->map.nodes[0][0]);
}
/*
static void	rotate_z(t_point *p, double angle)
{
	double	x;
	double	y;

	if (!p || angle == 0)
		return ;
	x = p->x;
	y = p->y;
	p->x = x * cos(angle) - y * sin(angle);
	p->y = x * sin(angle) + y * cos(angle);
}*/

static void	pad(t_screen *s, double xpad, double ypad)
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

static void	isometric(t_point *p)
{
	int	x;
	int	y;

	x = p->x;
	y = p->y;
	p->x = (x - y) * cos(0.46373398);
	p->y = -p->z + (x + y) * sin(0.46373398);
}

static void	endian_paddings(t_screen *s)
{
	s->img.rd = 2;
	s->img.gd = 1;
	s->img.bd = 0;
	if (s->img.endian)
	{
		s->img.rd = 0;
		s->img.gd = 1;
		s->img.bd = 2;
	}
}

void	transform(t_screen *s)
{
	int		r;
	int		c;

	endian_paddings(s);
	make_nodes(s);
	r = -1;
	while (++ r < s->map.height)
	{
		c = -1;
		while (++ c < s->map.width)
		{
			isometric(&s->map.nodes[r][c]);
			limits_adjust(s, &s->map.nodes[r][c]);
		}
	}
	if (s->map.zmax == s->map.zmin)
		s->map.zmax ++;
	pad(s, -s->map.xmin + MARGIN, -s->map.ymin + MARGIN);
}
