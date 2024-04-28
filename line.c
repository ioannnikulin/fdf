/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:23:13 by inikulin          #+#    #+#             */
/*   Updated: 2024/04/28 21:05:44 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_internal.h"
#include <math.h>

static char	mymax(char a, char b)
{
	if ((a < 0 && b >= 0) || (a > b && b > 0) || (b < a && a < 0))
		return (a);
	return (b);
}
/*
static char	mymin(char a, char b)
{
	if (mymax(a, b) == a)
		return (b);
	return (a);
}*/

static double	flr(double c)
{
	return ((int)c);
}

static double	fpart(double c)
{
	return (c - flr(c));
}

static double rfpart(double c)
{
	return (1.0 - fpart(c));
}

static double	rnd(double c)
{
	return (flr(c + 0.5));
}

typedef struct	s_color
{
	char	r;
	char	g;
	char	b;
	double	alpha;
	double	clr;
} t_color;

static int	higher(t_color a, t_color b)
{
	if (b.r == 0 && b.g == 0 && b.b == 0)
		return (1);
	if (a.r == 0 && a.g == 0 && a.b == 0)
		return (0);
	if (mymax(a.g, b.g) == b.g && mymax(a.g, b.g) != a.g)
		return (1);
	return (0);
}

t_color	color(double clr, double alpha)
{
	t_color	res;

	res.r = 255 * alpha;
	res.g = 255 * (1 - clr) * alpha;
	res.b = res.g;
	res.clr = clr;
	res.alpha = alpha;
	return (res);
}

static void	pixel(t_screen *s, int x, int y, t_color clr)
{
	int		tgt;
	t_color	cur;

	if (x < 0 || x > WIN_WIDTH || y < 0 || y > WIN_HEIGHT)
		return ;
	tgt = y * s->img.linesz + x * s->img.bpp / 8;
	cur.r = s->img.data[tgt + s->img.rd];
	cur.g = s->img.data[tgt + s->img.gd];
	cur.b = s->img.data[tgt + s->img.bd];
	if (higher(clr, cur))
	{
		s->img.data[tgt + s->img.rd] = clr.r;
		s->img.data[tgt + s->img.gd] = clr.g;
		s->img.data[tgt + s->img.bd] = clr.b;
	}
}

typedef struct	s_line_arg
{
	double		x0;
	double		y0;
	double		z0;
	double		clr0;
	double		x1;
	double		y1;
	double		z1;
	double		clr1;
	double		steep;
	double		dx;
	double		dy;
	double		gradient;
	int			end0x;
	int			end0y;
	int			end1x;
	int			end1y;
	double		intery;
	t_screen	*s;
}	t_line_arg;

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

typedef struct	s_endpoint_args
{
	double		xend;
	double		yend;
	double		xgap;
	t_color		clr;
}	t_endpoint_args;

static t_endpoint_args	make_ea(double xend, double yend, double xgap,
							   t_color clr)
{
	t_endpoint_args	r;

	r.xend = xend;
	r.yend = yend;
	r.xgap = xgap;
	r.clr = clr;
	return (r);
}

static void	endpoint0(t_line_arg *arg, double x, double y)
{
	t_endpoint_args	ea;

	ea = make_ea(rnd(x), y + arg->gradient * (rnd(x) - x),
			rfpart(x + 0.5), color((arg->z0 - arg->s->map.zmin)
			/ (arg->s->map.zmax - arg->s->map.zmin), 0));
	arg->end0x = ea.xend;
	arg->end0y = floor(ea.yend);
	if (arg->steep)
	{
		ea.clr = color(ea.clr.clr, rfpart(ea.yend) * ea.xgap);
		pixel(arg->s, arg->end0y, arg->end0x, ea.clr);
		arg->clr0 = ea.clr.clr;
		ea.clr = color(ea.clr.clr, fpart(ea.yend) * ea.xgap);
		pixel(arg->s, arg->end0y + 1, arg->end0x, ea.clr);
	}
	else
	{
		ea.clr = color(ea.clr.clr, rfpart(ea.yend) * ea.xgap);
		pixel(arg->s, arg->end0x, arg->end0y, ea.clr);
		arg->clr0 = ea.clr.clr;
		ea.clr = color(ea.clr.clr, fpart(ea.yend) * ea.xgap);
		pixel(arg->s, arg->end0x, arg->end0y + 1, ea.clr);
	}
	arg->intery = ea.yend + arg->gradient;
}

static void	endpoint1(t_line_arg *arg, double x, double y)
{
	t_endpoint_args	ea;

	ea = make_ea(rnd(x), y + arg->gradient * (rnd(x) - x),
			fpart(x + 0.5), color((arg->z1 - arg->s->map.zmin)
			/ (arg->s->map.zmax - arg->s->map.zmin), 0));
	arg->end1x = ea.xend;
	arg->end1y = floor(ea.yend);
	if (arg->steep)
	{
		ea.clr = color(ea.clr.clr, rfpart(ea.yend) * ea.xgap);
		pixel(arg->s, arg->end1y, arg->end1x, ea.clr);
		arg->clr1 = ea.clr.clr;
		ea.clr = color(ea.clr.clr, fpart(ea.yend) * ea.xgap);
		pixel(arg->s, arg->end1y + 1, arg->end1x, ea.clr);
	}
	else
	{
		ea.clr = color(ea.clr.clr, rfpart(ea.yend) * ea.xgap);
		pixel(arg->s, arg->end1x, arg->end1y, ea.clr);
		arg->clr1 = ea.clr.clr;
		ea.clr = color(ea.clr.clr, fpart(ea.yend) * ea.xgap);
		pixel(arg->s, arg->end1x, arg->end1y + 1, ea.clr);
	}
}

static void	loop(t_line_arg *arg)
{
	int		x;
	double	clr;

	x = arg->end0x + 1;
	if (arg->steep)
	{
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
	else
	{
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
	loop(&arg);
}
