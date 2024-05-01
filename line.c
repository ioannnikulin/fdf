/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:23:13 by inikulin          #+#    #+#             */
/*   Updated: 2024/05/01 14:50:10 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_internal.h"
#include <math.h>

void	endpoint0(t_line_arg *arg, double x, double y);
void	endpoint1(t_line_arg *arg, double x, double y);
double	flr(double c);
double	fpart(double c);
double	rfpart(double c);
double	rnd(double c);
void	pixel(t_screen *s, int x, int y, t_color clr);
t_color	color(double clr, double alpha);

static void	prep(t_line_arg *arg)
{
	arg->steep = fabs(arg->y1 - arg->y0) > fabs(arg->x1 - arg->x0);
	if (arg->steep)
	{
		ft_swap_d(&(arg->x0), &(arg->y0));
		ft_swap_d(&(arg->x1), &(arg->y1));
	}
	if (arg->x0 > arg->x1)
	{
		ft_swap_d(&(arg->x0), &(arg->x1));
		ft_swap_d(&(arg->y0), &(arg->y1));
		ft_swap_d(&(arg->z0), &(arg->z1));
		ft_swap_d(&(arg->clr0), &(arg->clr1));
	}
	arg->dx = arg->x1 - arg->x0;
	arg->dy = arg->y1 - arg->y0;
	if (arg->dx == 0.0)
		arg->gradient = 1.0;
	else
		arg->gradient = arg->dy / arg->dx;
}

static void	loop_steep(t_line_arg *arg)
{
	int		x;
	double	clr;

	x = arg->end0x + 1;
	while (x < arg->end1x)
	{
		clr = ((double)(x - arg->end0x)) / (arg->end1x - arg->end0x);
		clr = clr * (arg->clr1 - arg->clr0) + arg->clr0;
		pixel(arg->s, flr(arg->intery), x, color(clr, rfpart(arg->intery)));
		pixel(arg->s, flr(arg->intery) + 1, x, color(clr, fpart(arg->intery)));
		arg->intery += arg->gradient;
		x ++;
	}
}

static void	loop_nonsteep(t_line_arg *arg)
{
	int		x;
	double	clr;

	x = arg->end0x + 1;
	while (x < arg->end1x)
	{
		clr = ((double)(x - arg->end0x)) / (arg->end1x - arg->end0x);
		clr = clr * (arg->clr1 - arg->clr0) + arg->clr0;
		pixel(arg->s, x, flr(arg->intery), color(clr, rfpart(arg->intery)));
		pixel(arg->s, x, flr(arg->intery) + 1, color(clr, fpart(arg->intery)));
		arg->intery += arg->gradient;
		x ++;
	}
}

static t_line_arg	make_la(t_point *f, t_point *t, t_screen *s)
{
	t_line_arg	arg;

	arg.x0 = f->x;
	arg.y0 = f->y;
	arg.z0 = f->z;
	arg.x1 = t->x;
	arg.y1 = t->y;
	arg.z1 = t->z;
	arg.steep = 0;
	arg.dx = 0;
	arg.dy = 0;
	arg.gradient = 0;
	arg.end0x = 0;
	arg.end0y = 0;
	arg.end1x = 0;
	arg.end1y = 0;
	arg.intery = 0;
	arg.s = s;
	return (arg);
}

void	line(t_screen *s, t_point *f, t_point *t)
{
	t_line_arg	arg;

	arg = make_la(f, t, s);
	prep(&arg);
	endpoint0(&arg, arg.x0, arg.y0);
	endpoint1(&arg, arg.x1, arg.y1);
	if (arg.steep)
		loop_steep(&arg);
	else
		loop_nonsteep(&arg);
}
