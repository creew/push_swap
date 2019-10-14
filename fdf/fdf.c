/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 11:03:14 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/11 11:03:15 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "fdf.h"


int		key_hook(int key, void *param)
{
	t_fdf *fdf;

	fdf = (t_fdf *)param;
	if (key == ESC_KEY)
	{
		mlx_destroy_window(fdf->mlx_ptr, fdf->wnd_ptr);
		exit(0);
	}
	else if (key == ZERO_NUM_KEY || key == ZERO_KEY)
	{
		fdf->shift_y = 0;
		fdf->shift_x = 0;
	}
	else if (key == ARROW_LEFT_KEY)
		fdf->z_rotate -=5;
	else if (key == ARROW_RIGHT_KEY)
		fdf->z_rotate +=5;
	ft_sprintf(fdf->str_out, "key: %d", key);
	ft_printf("%s\n", fdf->str_out);
	redraw_main_screen(fdf);
	return (0);
}

int		button_pressed(int button, int x, int y, void *param)
{
	t_fdf *fdf;

	fdf = (t_fdf *)param;

	if (x >= 0 && y >= 0 && x < fdf->wnd_width && y < fdf->wnd_height)
		set_key_pressed(&fdf->mouse_keys, button, x, y);
	if (button == 4)
		fdf->scale += 0.2;
	else if (button == 5)
		fdf->scale -= 0.2;
	ft_sprintf(fdf->str_out, "button pressed: %d, x: %d, y: %d", button, x, y);
	ft_printf("%s\n", fdf->str_out);
	redraw_main_screen(fdf);
	return (0);
}

int		button_released(int button, int x, int y, void *param)
{
	t_fdf	*fdf;
	int		diffx;
	int		diffy;

	fdf = (t_fdf *)param;
	set_key_released(&fdf->mouse_keys, button, x, y);
	if (x >= 0 && y >= 0 && x < fdf->wnd_width && y < fdf->wnd_height)
	{
		if (button == 1)
		{
			get_key_diff(&fdf->mouse_keys, 1, &diffx, &diffy);
			fdf->z_rotate += (diffx)/10;
			fdf->z_rotate %= 360;
			fdf->xy_rotate += (diffy)/10;
			fdf->xy_rotate %= 360;
			fdf->z_rotate_add = 0;
			fdf->xy_rotate_add = 0;

		}
		else if (button == 2)
		{
			get_key_diff(&fdf->mouse_keys, 2, &diffx, &diffy);
			fdf->shift_x += diffx;
			fdf->shift_y += diffy;
			fdf->shift_y_add = 0;
			fdf->shift_x_add = 0;
		}
	}
	ft_sprintf(fdf->str_out, "button released: %d, x: %d, y: %d", button, x, y);
	ft_printf("%s\n", fdf->str_out);
	redraw_main_screen(fdf);
	return (0);
}

int		mouse_move(int x, int y, void *param)
{
	t_fdf 	*fdf;
	int		diffx;
	int		diffy;

	fdf = (t_fdf *)param;
	if (x >= 0 && y >= 0 && x < fdf->wnd_width && y < fdf->wnd_height)
	{
		set_current_xy(&fdf->mouse_keys, x, y);
		if (is_key_pressed(&fdf->mouse_keys, 1))
		{
			get_key_diff(&fdf->mouse_keys, 1, &diffx, &diffy);
			fdf->z_rotate_add = (diffx)/10;
			fdf->z_rotate_add %= 360;
			fdf->xy_rotate_add = (diffy)/10;
			fdf->xy_rotate_add %= 360;
		}
		else if (is_key_pressed(&fdf->mouse_keys, 2))
		{
			get_key_diff(&fdf->mouse_keys, 2, &diffx, &diffy);
			fdf->shift_x_add = diffx;
			fdf->shift_y_add = diffy;
		}
	}
	ft_sprintf(fdf->str_out, "mouse move x: %d, y: %d", x, y);
	redraw_main_screen(fdf);
	return (0);
}

int		expose_hook(void *param)
{
	t_fdf *fdf;
	fdf = (t_fdf *)param;
	ft_sprintf(fdf->str_out, "exposure");
	redraw_main_screen(fdf);
	return (0);
}

int		close_notify(void *param)
{
	t_fdf *fdf;
	fdf = (t_fdf *)param;
	mlx_destroy_window(fdf->mlx_ptr, fdf->wnd_ptr);
	exit(0);
}

void	initfdf(t_fdf *fdf)
{
	bzero(fdf, sizeof(*fdf));
	fdf->wnd_width = WND_WIDTH;
	fdf->wnd_height = WND_HEIGHT;
	fdf->scale = 1;
}

int		main(int ac, char *av[])
{
	(void)ac;
	(void)av;
	t_fdf fdf;

	initfdf(&fdf);
	fdf.mlx_ptr = mlx_init();
	read_file("./fdf_demo/maps/42.fdf", &fdf);
	fdf.mapout = malloc(sizeof(t_point) * fdf.map_width * fdf.map_height);
	for (int i = 0; i < fdf.map_height; i++)
	{
		for (int j = 0; j < fdf.map_width; j++)
		{
			ft_printf("%d ", fdf.srcmap[i * fdf.map_width + j].z);
		}
		ft_printf("\n");
	}
	init_upper_border(&fdf);
	init_bottom_border(&fdf);
	if (fdf.mlx_ptr)
	{
		fdf.wnd_ptr = mlx_new_window(fdf.mlx_ptr, fdf.wnd_width, fdf.wnd_height, "Превед!");
		if (fdf.wnd_ptr)
		{
			mlx_key_hook(fdf.wnd_ptr, key_hook, &fdf);
			mlx_hook(fdf.wnd_ptr, Expose, ExposureMask , expose_hook, &fdf);
			mlx_hook(fdf.wnd_ptr, MotionNotify, PointerMotionMask, mouse_move, &fdf);
			mlx_hook(fdf.wnd_ptr, DestroyNotify, 0, close_notify, &fdf);
			mlx_hook(fdf.wnd_ptr, ButtonPress, ButtonPressMask, button_pressed, &fdf);
			mlx_hook(fdf.wnd_ptr, ButtonRelease, ButtonReleaseMask, button_released, &fdf);
			mlx_loop(fdf.mlx_ptr);
		}
	}
	return (0);
}
