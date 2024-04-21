/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 16:39:56 by inikulin          #+#    #+#             */
/*   Updated: 2024/04/21 20:37:07 by inikulin         ###   ########.fr       */
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
	for (int i = 0; i < s->map.height; i ++)
	{
		for (int j = 0; j < s->map.width; j ++)
			printf("%3.3f:%3.3f:%3.3f\t", s->map.nodes[i][j].x, s->map.nodes[i][j].y, s->map.nodes[i][j].z);
		printf("\n");
	}
}

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
}

static void	pad(t_screen *s, double xpad, double ypad)
{
	int		r;
	int		c;

	r = -1;
	while (++ r < s->map.height)
	{
		c = -1;
		while (++ c < s->map.width)
		{
			s->map.nodes[r][c].x += xpad;
			s->map.nodes[r][c].y += ypad;
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

void	transform(t_screen *s)
{
	int		r;
	int		c;
	double	xmin;
	double	ymin;

	make_nodes(s);
	xmin = s->map.nodes[0][0].x;
	ymin = s->map.nodes[0][0].y;
	r = -1;
	while (++ r < s->map.height)
	{
		c = -1;
		while (++ c < s->map.width)
		{
			if (0)
				rotate_z(&s->map.nodes[r][c], M_PI / 4.0);
			if (1)
				isometric(&s->map.nodes[r][c]);
			xmin = *ft_min_dbl(&xmin, &s->map.nodes[r][c].x);
			ymin = *ft_min_dbl(&ymin, &s->map.nodes[r][c].y);
		}
	}
	pad(s, -xmin + MARGIN, -ymin + MARGIN);
}
