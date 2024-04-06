/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:23:13 by inikulin          #+#    #+#             */
/*   Updated: 2024/04/06 16:38:18 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_internal.h"

void	draw(t_screen *s)
{
	int		r;
	int		c;
	char	*buf;

	r = -1;
	while (++ r < s->map->height)
	{
		c = -1;
		while (++ c < s->map->width)
		{
			buf = ft_itoa(s->map->vals[r * s->map->width + c]);
			mlx_string_put(s->mlx, s->win, 50 + 50 * c, 
				50 + 50 * r, WHITE, buf);
			free(buf);
		}
	}
}
