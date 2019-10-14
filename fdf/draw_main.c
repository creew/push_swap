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
	return (fdf->shift_x);
}

int 		get_start_y(t_fdf *fdf)
{
	return (fdf->shift_y);
}

static void	draw_points(t_fdf *fdf)
{
	double x;
	double y;
	double cosf;
	double sinf;

	cosf =  cos((double)fdf->z_rotate * M_PI / 180) * fdf->scale;
	sinf =  sin((double)fdf->z_rotate * M_PI / 180) * fdf->scale;
	for (int i = 0; i < fdf->map_height; i++)
	{
		for (int j = 0; j < fdf->map_width; j++)
		{
			x = j * cosf - i * sinf;
			y = j * sinf + i * cosf;
			x = x * cos(DEG_RAD_30);
			y = -fdf->map[i * fdf->map_width + j].z*fdf->scale + y * sin(DEG_RAD_30);
			mlx_pixel_put(fdf->mlx_ptr, fdf->wnd_ptr, x + get_start_x(fdf), y + get_start_y(fdf), FT_COLOR(255, 255,255));
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
	draw_points(fdf);
	return (RET_OK);
}