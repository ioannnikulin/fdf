/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:23:13 by inikulin          #+#    #+#             */
/*   Updated: 2024/04/06 15:29:59 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_internal.h"

static t_action	parse_key(int keycode)
{
	if (keycode == 65307)
		return (EXIT);
	return (NO);
}

static int	finalize(t_screen *s, char *err)
{
	if (err)
		ft_printf("Error: %s\n", err);
	if (s)
	{
		if(s->mlx && s->win)
			mlx_destroy_window(s->mlx, s->win);
		if (s->map)
			free(s->map->vals);
	}
	exit(0);
	return (0);
}

static int	closeit(void *param)
{
	finalize((t_screen *)param, 0);
	return (0);
}

static int	handle_keyboard(int keycode, void *param)
{
	t_action	action;

	action = parse_key(keycode);
	if (action == NO)
		return (0);
	t_screen	*s = (t_screen *)param;
//	char	*buf = ft_itoa(keycode);
//	mlx_clear_window(s->mlx, s->win);
	// mlx_string_put(s->mlx, s->win, 512, 512, 255 + 256 * 255 + 256 * 256 * 255, buf);
	// free(buf);
	if (action == EXIT)
		finalize(s, 0);
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
			mlx_string_put(s->mlx, s->win, 50 + 50 * c, 50 + 50 * r, 255 + 256 * 255 + 256 * 256 * 255, buf);
			free(buf);
		}
	}
}

static void	video(t_screen *s)
{
	if(!(s->mlx = mlx_init()))
		finalize(s, "couldn't establish connection to the X server");
	if(!(s->win = mlx_new_window(s->mlx, WIN_WIDTH, WIN_HEIGHT, "FdF")))
		finalize(s, "couldn't create a MLX window");
	draw(s);
	mlx_key_hook(s->win, handle_keyboard, s);
	mlx_mouse_hook(s->win, handle_mouse, s);
	mlx_hook(s->win, 17, 0, closeit, s);
	mlx_loop(s->mlx);
}

static char	*free_arr_s(char **ws, int len, char *ret)
{
	while (len --)
		free(ws[len]);
	free(ws);
	return (ret);
}

static char	*free_arr_i(int *i, char *ret)
{
	free(i);
	return (ret);
}

static void	parse_line(char *buf, t_screen *s)
{
	int		*tmp;
	char	**ws;
	int		act_len;
	int		ok;

	tmp = s->map->vals;
	if (!(ws = ft_split(buf, '\t', &act_len)))
		finalize(s, "no memory for the map");
	if (s->map->width && s->map->width != act_len)
		finalize(s, free_arr_s(ws, act_len, "map should be rectangular"));
	if (!s->map->width)
		s->map->width = act_len;
	if (!(s->map->vals = malloc(sizeof(int) * (s->map->width * (s->map->height + 1)))))
		finalize(s, free_arr_s(ws, act_len, "no memory for the map"));
	while (act_len -- > 0)
	{
		s->map->vals[s->map->height * s->map->width + act_len] = ft_atoi(ws[act_len], &ok);
		if (!ok)
			finalize(s, free_arr_s(ws, act_len,
					free_arr_i(tmp, "unexpected point height")));
	}
	act_len = s->map->height * s->map->width;
	while (act_len -- > 0)
		s->map->vals[act_len] = tmp[act_len];
	s->map->height ++;
	free_arr_s(ws, s->map->width, free_arr_i(tmp, 0));
}

static void	parse_map_from_file(int fs, t_screen *s)
{
	char	*buf;

	s->map->vals = 0;
	s->map->height = 0;
	s->map->width = 0;
	if (!(buf = get_next_line(fs)))
		finalize(s, "file empty");
	parse_line(buf, s);
	while ((buf = get_next_line(fs)))
		parse_line(buf, s);
}

int	main(int argc, char **argv)
{
	int			fs;
	t_screen	s;

	if (argc != 2)
		return(finalize(0, "incorrect number of arguments"));
	if (((fs = open(argv[1], O_RDONLY)) == -1) || read(fs, 0, 0) == -1)
		return(finalize(0, "file not found"));
	parse_map_from_file(fs, &s);
	video(&s);
	return (finalize(&s, 0));
}
