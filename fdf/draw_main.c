/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 15:14:34 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/13 15:14:35 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static void	draw_points(t_fdf *fdf)
{
	int		size;
	int		i;
	t_point	*point;

	i = -1;
	size = fdf->map_height * fdf->map_width;
	point = fdf->mapout;
	while (++i < size)
	{
		mlx_pixel_put(fdf->mlx_ptr, fdf->wnd_ptr, point->x + get_start_x(fdf),
			point->y + get_start_y(fdf), point->color);
		point++;
	}
}

void		cp_array(t_point *dst, t_point *src, int width, int height)
{
	int		i;
	int		size;

	i = -1;
	size = width * height;
	while (++i < size)
	{
		dst->x = src->x;
		dst->y = src->y;
		dst->z = src->z;
		dst->color = src->color;
		dst++;
		src++;
	}
}

int 		redraw_main_screen(t_fdf *fdf)
{
	mlx_clear_window(fdf->mlx_ptr, fdf->wnd_ptr);
	if (fdf->upper_border)
		mlx_put_image_to_window(fdf->mlx_ptr, fdf->wnd_ptr, fdf->upper_border, 0, 0);
	if (fdf->bottom_border)
		mlx_put_image_to_window(fdf->mlx_ptr, fdf->wnd_ptr, fdf->bottom_border, 0, BB_YPOS);
	mlx_string_put(fdf->mlx_ptr, fdf->wnd_ptr, WND_HEIGHT - 300, 20, FT_COLOR(255, 255,255), fdf->str_out);
	cp_array(fdf->mapout, fdf->srcmap, fdf->map_width, fdf->map_height);
	set_size_transform(fdf->mapout, fdf->map_width, fdf->map_height, fdf->scale);
	set_z_transform(fdf->mapout, fdf->map_width, fdf->map_height, get_z_offset(fdf));
	set_xy_transform(fdf->mapout, fdf->map_width, fdf->map_height, get_xy_offset(fdf));
	set_iso(fdf->mapout, fdf->map_width, fdf->map_height);
	draw_points(fdf);
	return (RET_OK);
}