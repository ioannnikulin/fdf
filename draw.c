/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:23:13 by inikulin          #+#    #+#             */
/*   Updated: 2024/04/06 17:45:38 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_internal.h"

void	draw(t_screen *s)
{
	int		r;
	int		c;

	s->img->img = mlx_new_image(s->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!s->img->img)
		finalize(s, "couldn't create an image");
	s->img->data = mlx_get_data(s->img->img, &(s->img->bpp),
		&(s->img->linesz), &(s->img->endian));
	r = -1;
	while (++ r < s->map->height)
	{
		c = -1;
		while (++ c < s->map->width)
		{
			mlx_string_put(s->mlx, s->win, 50 + 50 * c, 
				50 + 50 * r, WHITE, buf);
			free(buf);
		}
	}
}
