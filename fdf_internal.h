/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_internal.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:43:40 by inikulin          #+#    #+#             */
/*   Updated: 2024/04/06 17:44:39 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_INTERNAL_H
# define FDF_INTERNAL_H

# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <mlx.h>
# define WIN_WIDTH 1024
# define WIN_HEIGHT 512
# define WHITE 0xffffff

typedef struct	s_map
{
	int	*vals;
	int	height;
	int	width;
}	t_map;

typedef enum	e_action
{
	NO,
	EXIT
}	t_action;

typedef struct	s_point
{
	int	x;
	int	y;
	int	z;
}	t_point;

typedef struct	s_line
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
}	t_mlx_img;

typedef struct	s_screen
{
	void		*mlx;
	void		*win;
	t_map		map;
	t_mlx_img	img;
}	t_screen;

char	*free_arr_s(char **ws, int len, char *ret);
char	*free_arr_i(int *i, char *ret);
int		finalize(t_screen *s, char *err);
#endif
