/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:23:13 by inikulin          #+#    #+#             */
/*   Updated: 2024/04/13 20:50:38 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_internal.h"

void	line(t_screen *s, double x0, double y0, double x1, double y1);

void	draw(t_screen *s)
{
	int	r;
	int	c;

	s->img.img = mlx_new_image(s->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!s->img.img)
		finalize(s, "couldn't create an image");
	s->img.data = mlx_get_data_addr(s->img.img, &(s->img.bpp),
		&(s->img.linesz), &(s->img.endian));
	// for (int i = 0; i < s->map.height; i ++)
	// {
	// 	for (int j = 0; j < s->map.width; j ++)
	// 		ft_printf("%i:%i:%i\t", s->map.nodes[i][j].x, s->map.nodes[i][j].y, s->map.nodes[i][j].z);
	// 	ft_printf("\n");
	// }
	r = -1;
	while (++ r < s->map.height - 1)
	{
		c = -1;
		while (++ c < s->map.width - 1)
		{
			line(s, s->map.nodes[r][c].x, s->map.nodes[r][c].y, s->map.nodes[r][c + 1].x, s->map.nodes[r][c + 1].y);
			line(s, s->map.nodes[r][c].x, s->map.nodes[r][c].y, s->map.nodes[r + 1][c].x, s->map.nodes[r + 1][c].y);
		}
		line(s, s->map.nodes[r][c].x, s->map.nodes[r][c].y, s->map.nodes[r + 1][c].x, s->map.nodes[r + 1][c].y);
	}
	c = -1;
	while (++ c < s->map.width - 1)
		line(s, s->map.nodes[r][c].x, s->map.nodes[r][c].y, s->map.nodes[r][c + 1].x, s->map.nodes[r][c + 1].y);
	mlx_put_image_to_window(s->mlx, s->win, s->img.img, 0, 0);
}
