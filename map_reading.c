/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reading.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:23:13 by inikulin          #+#    #+#             */
/*   Updated: 2024/04/13 16:21:17 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_internal.h"

static void	copy_new(int act_len, t_screen *s, char **ws, int *tmp)
{
	int	ok;

	while (act_len -- > 0)
	{
		s->map.vals[s->map.height * s->map.width + act_len]
			= ft_atoi(ws[act_len], &ok);
		if (!ok)
			finalize(s, free_arr_s(ws, act_len,
					free_arr_i(tmp, "unexpected point height")));
	}
}

static void	copy_old(int *tmp, t_screen *s)
{
	int	i;

	i = s->map.height * s->map.width;
	while (i -- > 0)
		s->map.vals[i] = tmp[i];
}

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

	s->map.nodes = malloc(s->map.height * sizeof(t_point *));
	if (!s->map.nodes)
		finalize(s, "no memory for nodes");
	r = -1;
	while (++r < s->map.height)
	{
		s->map.nodes[r] = malloc(s->map.width * sizeof(t_point));
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

static void	parse_line(char *buf, t_screen *s)
{
	int		*tmp;
	char	**ws;
	int		act_len;

	tmp = s->map.vals;
	ws = ft_split_set(buf, "\t\n ", &act_len);
	if (!ws)
		finalize(s, "no memory for the map");
	if (s->map.width && s->map.width != act_len)
		finalize(s, free_arr_s(ws, act_len, "map should be rectangular"));
	if (!s->map.width)
		s->map.width = act_len;
	s->map.vals = malloc(sizeof(int) * (s->map.width * (s->map.height + 1)));
	if (!s->map.vals)
		finalize(s, free_arr_s(ws, act_len, "no memory for the map"));
	copy_new(act_len, s, ws, tmp);
	copy_old(tmp, s);
	s->map.height ++;
	free_arr_s(ws, s->map.width, free_arr_i(tmp, 0));
	make_nodes(s);
}

void	parse_map_from_file(int fs, t_screen *s)
{
	char	*buf;

	s->map.vals = 0;
	s->map.height = 0;
	s->map.width = 0;
	s->mlx = 0;
	s->win = 0;
	s->img.img = 0;
	s->img.data = 0;
	buf = get_next_line(fs);
	if (!buf)
		finalize(s, "file empty");
	parse_line(buf, s);
	while (1)
	{
		buf = get_next_line(fs);
		if (!buf)
			break ;
		parse_line(buf, s);
	}
}
