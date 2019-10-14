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

int			get_start_x(t_fdf *fdf)
{
	return (fdf->shift_x + fdf->shift_x_add);
}

int 		get_start_y(t_fdf *fdf)
{
	return (fdf->shift_y + fdf->shift_y_add);
}

long		get_z_offset(t_fdf *fdf)
{
	return (fdf->z_rotate + fdf->z_rotate_add);
}

long		get_xy_offset(t_fdf *fdf)
{
	return (fdf->xy_rotate + fdf->xy_rotate_add);
}

static void	draw_points111(t_fdf *fdf)
{
	double x;
	double y;
	double z;
	double cosf;
	double sinf;
	double new_x;
	double new_y;
	double cos_xy;
	double sin_xy;

	cos_xy = cos((double)(fdf->xy_rotate + fdf->xy_rotate_add) * M_PI / 180);
	sin_xy = sin((double)(fdf->xy_rotate + fdf->xy_rotate_add) * M_PI / 180);

	cosf =  cos((double)(fdf->z_rotate + fdf->z_rotate_add) * M_PI / 180) * fdf->scale;
	sinf =  sin((double)(fdf->z_rotate + fdf->z_rotate_add) * M_PI / 180) * fdf->scale;

	for (int i = 0; i < fdf->map_height; i++)
	{
		for (int j = 0; j < fdf->map_width; j++)
		{
			z = fdf->srcmap[i * fdf->map_width + j].z;
			x = j * cos_xy - i * sin_xy * sin_xy + z * cos_xy * sin_xy;
			y = i * cos_xy + z * sin_xy;
			z = -j * sin_xy - i * sin_xy * cos_xy + z * cos_xy * cos_xy;

			new_x = x * cosf - y * sinf;
			new_y = x * sinf + y * cosf;

			x = (new_x - new_y) * FT_COS30;
			y = -z*fdf->scale + (new_x + new_y) * FT_SIN30;
			mlx_pixel_put(fdf->mlx_ptr, fdf->wnd_ptr, x + get_start_x(fdf), y + get_start_y(fdf), FT_COLOR(255, 255,255));
		}
	}
}

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

static void	set_size_transform(t_point *arr, int width, int height, double scale)
{
	int			i;
	int			j;

	i = -1;
	while (++i < height)
	{
		j = -1;
		while (++j < width)
		{
			arr->x = (int)(arr->x * scale);
			arr->y = (int)(arr->y * scale);
			arr->z = (int)(arr->z * scale);
			arr++;
		}
	}
}

static void	set_z_transform(t_point *arr, int width, int height, long z)
{
	int			i;
	int			j;
	t_dpoint	dp;
	double		cosf;
	double		sinf;

	cosf =  cos((double)(z) * M_PI / 180);
	sinf =  sin((double)(z) * M_PI / 180);
	i = -1;
	while (++i < height)
	{
		j = -1;
		while (++j < width)
		{
			dp.x = arr->x * cosf - arr->y * sinf;
			dp.y = arr->x * sinf + arr->y * cosf;
			arr->x = (int)(dp.x);
			arr->y = (int)(dp.y);
			arr++;
		}
	}
}

int 	redraw_main_screen(t_fdf *fdf)
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