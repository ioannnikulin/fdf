/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_internal.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:43:40 by inikulin          #+#    #+#             */
/*   Updated: 2024/03/24 19:47:36 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_INTERNAL_H
# define FDF_INTERNAL_H

typedef struct	s_img
{
	int	**map;
	int	mheight;
	int	mwidth;
}	t_img;


typedef struct	s_screen
{
	void	*mlx;
	void	*win;
	t_img	*img;
}	t_screen;

#endif
