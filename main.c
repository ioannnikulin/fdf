/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:23:13 by inikulin          #+#    #+#             */
/*   Updated: 2024/03/30 17:37:33 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_internal.h"

static t_action	parse_key(int keycode)
{
	if (keycode == 65307)
		return (EXIT);
	return (NO);
}

static int	finalize(t_screen *s)
{
	mlx_destroy_window(s->mlx, s->win);
	exit(0);
	return (0);
}

static int	handle_keyboard(int keycode, void *param)
{
	t_action	action;

	action = parse_key(keycode);
	if (action == NO)
		return (0);
	t_screen	*s = (t_screen *)param;
	char	*buf = ft_itoa(keycode);
	mlx_clear_window(s->mlx, s->win);
	mlx_string_put(s->mlx, s->win, 512, 512, 255 + 256 * 255 + 256 * 256 * 255, buf);
	free(buf);
	if (action == EXIT)
		finalize(s);
	return (0);
}

/*
 * 1 LMB, 2 wheel, 3 RMB, 4 up, 5 down
*/

static int	handle_mouse(int button, int x, int y, void *param)
{
	t_screen	*s = (t_screen *)param;
	if (button != 1)
		return (0);
	char	*buf = ft_itoa(x);
	mlx_clear_window(s->mlx, s->win);
	mlx_string_put(s->mlx, s->win, 512, 512, 255 + 256 * 255 + 256 * 256 * 255, buf);
	free(buf);
	buf = ft_itoa(y);
	mlx_string_put(s->mlx, s->win, 550, 512, 255 + 256 * 255 + 256 * 256 * 255, buf);
	free(buf);
	return (0);
}

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
	mlx_key_hook(s->win, handle_keyboard, s);
	mlx_mouse_hook(s->win, handle_mouse, s);
	mlx_hook(s->win, 17, 0, finalize, s);
	mlx_loop(s->mlx);
}

static int	parse_map_from_file(int fs, t_screen *s)
{
	(void)fs;
	(void)s;
	return (1);
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
