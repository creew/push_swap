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
	if (key == ESC_KEY)  // q
	{
		mlx_destroy_window(fdf->mlx_ptr, fdf->wnd_ptr);
		exit(0);
	}
	ft_sprintf(fdf->str_out, "key: %d", key);
	ft_printf("%s\n", fdf->str_out);
	redraw_main_screen(fdf);
	return (0);
}

int		button_pressed(int button, int x, int y, void *param)
{
	t_fdf *fdf;

	fdf = (t_fdf *)param;
	ft_sprintf(fdf->str_out, "button pressed: %d, x: %d, y: %d", button, x, y);
	ft_printf("%s\n", fdf->str_out);
	redraw_main_screen(fdf);
	return (0);
}

int		button_released(int button, int x, int y, void *param)
{
	t_fdf *fdf;

	fdf = (t_fdf *)param;
	ft_sprintf(fdf->str_out, "button released: %d, x: %d, y: %d", button, x, y);
	ft_printf("%s\n", fdf->str_out);
	redraw_main_screen(fdf);
	return (0);
}

int		mouse_move(int x, int y, void *param)
{
	t_fdf *fdf;

	fdf = (t_fdf *)param;
	ft_sprintf(fdf->str_out, "mouse move x: %d, y: %d", x, y);
	redraw_main_screen(fdf);
	return (0);
}

int		expose_hook(void *param)
{
	t_fdf *fdf;
	fdf = (t_fdf *)param;
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
	fdf->map = 0;
	fdf->map_height = 0;
	fdf->map_width = 0;
	fdf->wnd_width = WND_WIDTH;
	fdf->wnd_height = WND_HEIGHT;
	fdf->upper_border = 0;
	fdf->bottom_border = 0;
	fdf->str_out[0] = '\0';
}

int		main(int ac, char *av[])
{
	(void)ac;
	(void)av;
	t_fdf fdf;

	initfdf(&fdf);
	fdf.mlx_ptr = mlx_init();
	read_file("./fdf_demo/maps/elem-col.fdf", &fdf);
	for (int i = 0; i < fdf.map_height; i++)
	{
		for (int j = 0; j < fdf.map_width; j++)
			ft_printf("%d ", fdf.map[i * fdf.map_width + j]);
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
			mlx_expose_hook(fdf.wnd_ptr, expose_hook, &fdf);
			mlx_hook(fdf.wnd_ptr, MotionNotify, PointerMotionMask, mouse_move, &fdf);
			mlx_hook(fdf.wnd_ptr, GraphicsExpose, 0, close_notify, &fdf);
			mlx_hook(fdf.wnd_ptr, ButtonPress, ButtonPressMask, button_pressed, &fdf);
			mlx_hook(fdf.wnd_ptr, ButtonRelease, ButtonReleaseMask, button_released, &fdf);
			mlx_loop(fdf.mlx_ptr);
		}
	}
	return (0);
}
