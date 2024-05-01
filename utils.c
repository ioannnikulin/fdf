/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:23:13 by inikulin          #+#    #+#             */
/*   Updated: 2024/05/01 14:31:43 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_internal.h"

int	finalize(t_screen *s, char *err)
{
	if (err)
		ft_printf("Error: %s\n", err);
	if (s)
	{
		if (s->mlx && s->win)
			mlx_destroy_window(s->mlx, s->win);
		free(s->map.vals);
	}
	exit (0);
	return (0);
}

char	*free_arr_s(char **ws, int len, char *ret)
{
	while (len --)
		free(ws[len]);
	free(ws);
	return (ret);
}

char	*free_arr_i(int *i, char *ret)
{
	free(i);
	return (ret);
}

void	endian_paddings(t_screen *s)
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
