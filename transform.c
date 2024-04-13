/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 16:39:56 by inikulin          #+#    #+#             */
/*   Updated: 2024/04/13 20:46:34 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_internal.h"

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
			s->map.nodes[r][c].z = s->map.vals[r * s->map.width + c];
		}
	}
}

void	transform(t_screen *s)
{
	// t_matrix	mzr;

	// mzr = t_matrix();
	make_nodes(s);
	// rotate(s, )
}
