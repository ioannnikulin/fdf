/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_internal.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:43:40 by inikulin          #+#    #+#             */
/*   Updated: 2024/03/30 22:09:40 by inikulin         ###   ########.fr       */
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

typedef struct	s_screen
{
	void	*mlx;
	void	*win;
	t_map	*map;
}	t_screen;

#endif
