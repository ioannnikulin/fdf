/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:23:13 by inikulin          #+#    #+#             */
/*   Updated: 2024/03/29 20:51:42 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_internal.h"

static void	video(t_screen *s)
{
	s->mlx = mlx_init();
	if (!s->mlx)
	{
		ft_printf("Error: couldn't establish connection to the X server\n");
		return ;
	}
	s->win = mlx_new_window(s->mlx, 1024, 1024, "Hello world");
	if (!s->win)
	{
		ft_printf("Error: couldn't create a MLX window\n");
		return ;
	}
	mlx_string_put(s->mlx, s->win, 512, 512, 255 + 256 * 255 + 256 * 256 * 255, "Hello world");
	sleep(2);
}

static int	parse_map_from_file(int fs, t_screen *s)
{
	(void)fs;
	(void)s;
	return (1);
}

static void	finalize(t_screen *s)
{
	mlx_destroy_window(s->mlx, s->win);
	(void)s;
}

int	main(int argc, char **argv)
{
	int			fs;
	t_screen	s;

	if (argc != 2)
	{
		ft_printf("Error: incorrect number of arguments\n");
		return (0);
	}
	fs = open(argv[1], O_RDONLY);
	if (fs == -1 || read(fs, 0, 0) == -1)
	{
		ft_printf("Error: specified file not found\n");
		return (0);
	}
	if (parse_map_from_file(fs, &s))
		video(&s);
	finalize(&s);
	return (0);
}
