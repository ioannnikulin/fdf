/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:23:13 by inikulin          #+#    #+#             */
/*   Updated: 2024/04/13 16:14:53 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_internal.h"

// static void	line(t_screen *s, )

void	draw(t_screen *s)
{
	// int	r;
	// int	c;

	s->img.img = mlx_new_image(s->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!s->img.img)
		finalize(s, "couldn't create an image");
	s->img.data = mlx_get_data_addr(s->img.img, &(s->img.bpp),
		&(s->img.linesz), &(s->img.endian));
	for (int i = 0; i < s->map.height; i ++)
	{
		for (int j = 0; j < s->map.width; j ++)
			ft_printf("%i:%i:%i\t", s->map.nodes[i][j].x, s->map.nodes[i][j].y, s->map.nodes[i][j].z);
		ft_printf("\n");
	}
	// r = -1;
	// while (++ r < s->map.height)
	// {
	// 	c = 0;
	// 	while (++ c < s->map.width - 1)
	// 	{
	// 		line(MARGIN + c * STEP)
	// 	}
	// }
}
