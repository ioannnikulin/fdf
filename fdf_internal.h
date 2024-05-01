/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_internal.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:43:40 by inikulin          #+#    #+#             */
/*   Updated: 2024/05/01 14:53:18 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_INTERNAL_H
# define FDF_INTERNAL_H

# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <mlx.h>
# define WIN_WIDTH 1500
# define WIN_HEIGHT 700
# define MARGIN 50
# define STEP 50
# define _USE_MATH_DEFINES

typedef struct s_point
{
	double	x;
	double	y;
	double	z;
	double	color;
}	t_point;

typedef struct s_map
{
	int		*vals;
	int		height;
	int		width;
	t_point	**nodes;
	double	xmin;
	double	xmax;
	double	ymin;
	double	ymax;
	double	zmin;
	double	zmax;
}	t_map;

typedef enum e_action
{
	NO,
	EXIT
}	t_action;

typedef struct s_line
{
	t_point	*f;
	t_point	*t;
}	t_line;

typedef struct s_mlx_img
{
	void	*img;
	char	*data;
	int		bpp;
	int		linesz;
	int		endian;
	int		rd;
	int		gd;
	int		bd;
}	t_mlx_img;

typedef struct s_screen
{
	void		*mlx;
	void		*win;
	t_map		map;
	t_mlx_img	img;
}	t_screen;

typedef struct s_color
{
	char	r;
	char	g;
	char	b;
	double	alpha;
	double	clr;
}	t_color;

typedef struct s_line_arg
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

char	*free_arr_s(char **ws, int len, char *ret);
char	*free_arr_i(int *i, char *ret);
int		finalize(t_screen *s, char *err);
#endif
