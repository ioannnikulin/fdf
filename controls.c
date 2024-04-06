/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:23:13 by inikulin          #+#    #+#             */
/*   Updated: 2024/04/06 16:36:51 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_internal.h"

void	draw(t_screen *s);

static t_action	parse_key(int keycode)
{
	if (keycode == 65307)
		return (EXIT);
	return (NO);
}

static int	close_it(void *param)
{
	finalize((t_screen *)param, 0);
	return (0);
}

static int	handle_keyboard(int keycode, void *param)
{
	t_action	action;
	t_screen	*s;

	action = parse_key(keycode);
	if (action == NO)
		return (0);
	s = (t_screen *)param;
	if (action == EXIT)
		finalize(s, 0);
	return (0);
}

/*
 * 1 LMB, 2 wheel, 3 RMB, 4 up, 5 down
*/

static int	handle_mouse(int button, int x, int y, void *param)
{
	t_screen	*s;
	char		*buf;

	s = (t_screen *)param;
	if (button != 1)
		return (0);
	buf = ft_itoa(x);
	mlx_clear_window(s->mlx, s->win);
	mlx_string_put(s->mlx, s->win, 512, 512, WHITE, buf);
	free(buf);
	buf = ft_itoa(y);
	mlx_string_put(s->mlx, s->win, 550, 512, WHITE, buf);
	free(buf);
	return (0);
}

void	display_it(t_screen *s)
{
	s->mlx = mlx_init();
	if (!s->mlx)
		finalize(s, "couldn't establish connection to the X server");
	s->win = mlx_new_window(s->mlx, WIN_WIDTH, WIN_HEIGHT, "FdF");
	if (!s->win)
		finalize(s, "couldn't create a MLX window");
	draw(s);
	mlx_key_hook(s->win, handle_keyboard, s);
	mlx_mouse_hook(s->win, handle_mouse, s);
	mlx_hook(s->win, 17, 0, close_it, s);
	mlx_loop(s->mlx);
}
