/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:23:13 by inikulin          #+#    #+#             */
/*   Updated: 2024/04/06 16:44:56 by inikulin         ###   ########.fr       */
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
		if (s->map)
			free(s->map->vals);
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
