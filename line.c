/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:23:13 by inikulin          #+#    #+#             */
/*   Updated: 2024/04/21 19:53:06 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_internal.h"
#include <math.h>

static char	mymax(char a, char b)
{
	if ((a < 0 && b > 0) || (a > b && b > 0) || (b < a && a < 0))
		return (a);
	return (b);
}

static void	pixel(t_screen *s, int x, int y, double c)
{
	int		tgt;
	char	ncol;

	if (x < 0 || x > WIN_WIDTH || y < 0 || y > WIN_HEIGHT)
		return ;
	tgt = y * s->img.linesz + x * s->img.bpp / 8;
	ncol = 255 * c;
	s->img.data[tgt] = mymax(s->img.data[tgt], ncol); // TODO: change to color these later
	s->img.data[tgt + 1] = mymax(s->img.data[tgt + 1], ncol);
	s->img.data[tgt + 2] = mymax(s->img.data[tgt + 2], ncol);
}

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

typedef struct	s_line_arg
{
	double		x0;
	double		y0;
	double		x1;
	double		y1;
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
	int			*pxx;
	int			*pxy;
}	t_endpoint_args;

static t_endpoint_args	make_ea(double xend, double yend, double xgap,
							   int *pxx, int *pxy)
{
	t_endpoint_args	r;

	r.xend = xend;
	r.yend = yend;
	r.xgap = xgap;
	r.pxx = pxx;
	r.pxy = pxy;
	return (r);
}

static void	endpoint(t_line_arg *arg, double x, double y, double *intery)
{
	t_endpoint_args	ea;

	ea = make_ea(rnd(x), y + arg->gradient * (rnd(x) - x),
			  rfpart(x + 0.5), &arg->end0x, &arg->end0y);
	if (!intery)
	{
		ea.xgap = fpart(x + 0.5);
		ea.pxx = &arg->end1x;
		ea.pxy = &arg->end1y;
	}
	*(ea.pxx) = ea.xend;
	*(ea.pxy) = floor(ea.yend);
	if (arg->steep)
	{
		pixel(arg->s, *(ea.pxy), *(ea.pxx), rfpart(ea.yend) * ea.xgap);
		pixel(arg->s, *(ea.pxy) + 1, *(ea.pxx), fpart(ea.yend) * ea.xgap);
	}
	else
	{
		pixel(arg->s, *(ea.pxx), *(ea.pxy), rfpart(ea.yend) * ea.xgap);
		pixel(arg->s, *(ea.pxx), *(ea.pxy) + 1, fpart(ea.yend) * ea.xgap);
	}
	if (intery)
		*intery = ea.yend + arg->gradient;
}

static void	loop(t_line_arg *arg)
{
	int	x;

	x = arg->end0x + 1;
	if (arg->steep)
	{
		while (x < arg->end1x)
		{
			pixel(arg->s, flr(arg->intery), x, rfpart(arg->intery));
			pixel(arg->s, flr(arg->intery) + 1, x, fpart(arg->intery));
			arg->intery += arg->gradient;
			x ++;
		}
	}
	else
	{
		while (x < arg->end1x)
		{
			pixel(arg->s, x, flr(arg->intery), rfpart(arg->intery));
			pixel(arg->s, x, flr(arg->intery) + 1, fpart(arg->intery));
			arg->intery += arg->gradient;
			x ++;
		}
	}
}

static t_line_arg	make_la(double x0, double y0, double x1, double y1, t_screen *s)
{
	t_line_arg	arg;

	arg.x0 = x0;
	arg.y0 = y0;
	arg.x1 = x1;
	arg.y1 = y1;
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

void	line(t_screen *s, double x0, double y0, double x1, double y1)
{
	t_line_arg	arg;

	arg = make_la(x0, y0, x1, y1, s);
	prep(&arg);
	endpoint(&arg, arg.x0, arg.y0, &(arg.intery));
	endpoint(&arg, arg.x1, arg.y1, 0);
	// pixel(s, rnd(x0), rnd(y0), 1);
	// pixel(s, rnd(x1), rnd(y1), 1);
	loop(&arg);
	ft_printf("%i:%i-%i:%i\n", arg.end0x, arg.end0y, arg.end1x, arg.end1y);
}
