/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:23:13 by inikulin          #+#    #+#             */
/*   Updated: 2024/04/28 20:20:58 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_internal.h"

void	line(t_screen *s, t_point *f, t_point *t);
void	transform(t_screen *s);

void	draw(t_screen *s)
{
	int	r;
	int	c;

	s->img.img = mlx_new_image(s->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!s->img.img)
		finalize(s, "couldn't create an image");
	s->img.data = mlx_get_data_addr(s->img.img, &(s->img.bpp),
		&(s->img.linesz), &(s->img.endian));
	transform(s);
	r = -1;
	while (++ r < s->map.height - 1)
	{
		c = -1;
		while (++ c < s->map.width - 1)
		{
			line(s, &s->map.nodes[r][c], &s->map.nodes[r][c + 1]);
			line(s, &s->map.nodes[r][c], &s->map.nodes[r + 1][c]);
		}
		line(s, &s->map.nodes[r][c], &s->map.nodes[r + 1][c]);
	}
	c = -1;
	while (++ c < s->map.width - 1)
		line(s, &s->map.nodes[r][c], &s->map.nodes[r][c + 1]);
	mlx_put_image_to_window(s->mlx, s->win, s->img.img, 0, 0);
}
