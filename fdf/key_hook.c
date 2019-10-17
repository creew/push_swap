/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 08:20:33 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/15 08:20:33 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		set_mode(t_fdf *fdf, int mode)
{
	fdf->z_scale = 0.2;
	fdf->z_rotate = 0;
	fdf->x_rotate = 0;
	fdf->y_rotate = 0;
	fdf->parallel = mode;
	if (fdf->parallel)
	{
		fdf->x_rotate = 60;
		fdf->y_rotate = 60;
	}
	calc_optimal_size(fdf, 0);
}

static int	process_key2(t_fdf *fdf, int key)
{
	if (key == ONE_KEY || key == ONE_NUM_KEY)
		set_mode(fdf, 0);
	else if (key == TWO_KEY || key == TWO_NUM_KEY)
		set_mode(fdf, 1);
	else if (key == THREE_KEY || key == THREE_NUM_KEY)
	{
		colorise_map(fdf->mapout, fdf->map_height * fdf->map_width);
		redraw_main_screen(fdf);
		return (0);
	}
	else if (key == POINT_KEY || key == POINT_NUM_KEY)
		fdf->woo = !fdf->woo;
	return (1);
}

static int	process_key(t_fdf *fdf, int key)
{
	if (key == ESC_KEY)
	{
		//mlx_destroy_window(fdf->mlx_ptr, fdf->wnd_ptr);
		destroy_all_exit(fdf);
	}
	else if (key == ZERO_NUM_KEY || key == ZERO_KEY)
		calc_optimal_size(fdf, 1);
	else if (key == ARROW_LEFT_KEY)
		fdf->z_rotate -= 5;
	else if (key == ARROW_RIGHT_KEY)
		fdf->z_rotate += 5;
	else if (key == Z_KEY)
		fdf->z_scale -= 0.1;
	else if (key == A_KEY)
		fdf->z_scale += 0.1;
	else if (key == PLUS_KEY || key == PLUS_NUM_KEY)
		fdf->scale += 0.2;
	else if (key == MINUS_KEY || key == MINUS_NUM_KEY)
		fdf->scale -= 0.2;
	else
	{
		if (process_key2(fdf, key) == 0)
			return (0);
	}
	return (1);
}

int			key_hook(int key, void *param)
{
	t_fdf *fdf;

	fdf = (t_fdf *)param;
	if (process_key(fdf, key) == 0)
		return (0);
	redraw_image(fdf);
	ft_sprintf(fdf->str_out, "key: %d", key);
	ft_printf("%s\n", fdf->str_out);
	redraw_main_screen(fdf);
	return (0);
}
