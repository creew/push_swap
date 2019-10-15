/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorize_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 17:44:09 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/15 17:44:10 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		is_colorized(t_point *point, int size)
{
	int		i;
	int		color;

	if (size)
	{
		i = 0;
		color = point->color;
		point++;
		while (++i < size)
		{
			if (point->color != color)
				return (1);
			point++;
		}
	}
	return (0);
}

void	find_min_max(t_point *point, int size, int *minz, int *maxz)
{
	int		i;

	*minz = 0;
	*maxz = 0;
	if (size)
	{
		i = 0;
		*minz = point->z;
		*maxz = point->z;
		while (++i < size)
		{
			if (point->z > *maxz)
				*maxz = point->z;
			if (point->z < *minz)
				*minz = point->z;
			point++;
		}
	}
}

void	colorise_map(t_point *point, int size)
{
	int		i;
	int		maxz;
	int		minz;
	i = -1;

	find_min_max(point, size, &minz, &maxz);
	while (++i < size)
	{
		if (point->z == 0)
			point->color = 0x964B00;
		else if (point->z > 0)
			point->color = get_color(0x964B00, 0xFFFFFF, maxz, point->z);
		else
			point->color = get_color(0x00FF00, 0xFFFFFF, -minz, -point->z);

		point++;
	}
}

void	colorize_not(t_point *point, int size)
{
	if (!is_colorized(point, size))
		colorise_map(point, size);
}