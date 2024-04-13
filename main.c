/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:23:13 by inikulin          #+#    #+#             */
/*   Updated: 2024/04/13 16:39:39 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_internal.h"

void	parse_map_from_file(int fs, t_screen *s);
void	transform(t_screen *s);
void	display_it(t_screen *s);

int	main(int argc, char **argv)
{
	int			fs;
	t_screen	s;

	if (argc != 2)
		return (finalize(0, "incorrect number of arguments"));
	fs = open(argv[1], O_RDONLY);
	if ((fs == -1) || (read(fs, 0, 0) == -1))
		return (finalize(0, "file not found"));
	parse_map_from_file(fs, &s);
	transform(&s);
	display_it(&s);
	return (finalize(&s, 0));
}
