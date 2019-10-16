/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_maps.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 16:03:16 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/16 16:03:17 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	calc_limits(t_point *map, int size, t_point *wh, t_point *start)
{
	int		i;

	start->x = 2147483647;
	start->y = start->x;
	wh->x = -2147483648;
	wh->y = wh->x;
	i = -1;
	while (++i < size)
	{
		start->x = MIN(start->x, map->x);
		start->y = MIN(start->y, map->y);
		wh->x = MAX(wh->x, map->x);
		wh->y = MAX(wh->y, map->y);
		map++;
	}
	wh->x = wh->x - start->x;
	if (wh->x < 0)
		wh->x = -wh->x;
	wh->y = wh->y - start->y;
	if (wh->y < 0)
		wh->y = -wh->y;
}

void		calc_optimal_size(t_fdf *fdf)
{
	t_point		start;
	t_point		wh;
	double		main_height;
	double		main_width;

	main_height = MAIN_HEIGHT;
	main_width = MAIN_WIDTH;
	fdf->scale = 1;
	fdf->shift_x = 0;
	fdf->shift_y = 0;
	fdf->xy_rotate = 0;
	fdf->z_rotate = 0;
	do_transformations(fdf);
	calc_limits(fdf->mapout, fdf->map_width * fdf->map_height, &wh, &start);
	fdf->scale = MIN(main_height / wh.y, main_width / wh.x) * 0.99;
	do_transformations(fdf);
	calc_limits(fdf->mapout, fdf->map_width * fdf->map_height, &wh, &start);
	fdf->shift_x = MAIN_WIDTH / 2 - start.x - wh.x / 2;
	fdf->shift_y = MAIN_HEIGHT / 2 - start.y - wh.y / 2;
}

void		normalize_map(t_point *point, int width, int height)
{
	int i;
	int j;
	int	hw;
	int hh;

	hw = width / 2;
	hh = height / 2;
	i = -1;
	while (++i < height)
	{
		j = -1;
		while (++j < width)
		{
			point->x = j - hw;
			point->y = i - hh;
			point++;
		}
	}
}
