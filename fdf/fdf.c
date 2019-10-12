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
#include "mlx.h"
#include "ft_printf.h"

int		key_hook(int key, void *param)
{
	t_fdf *fdf;
	char   buf[64];

	fdf = (t_fdf *)param;
	if (key == ESC_KEY)  // q
	{
		mlx_destroy_window(fdf->mlx_ptr, fdf->wnd_ptr);
		exit(0);
	}
	ft_sprintf(buf, "key: %d", key);
	mlx_clear_window(fdf->mlx_ptr, fdf->wnd_ptr);
	mlx_string_put(fdf->mlx_ptr, fdf->wnd_ptr, 600, 20, FT_COLOR(255, 0,0), buf);
	return (0);
}

int		mouse_hook(int button, int x, int y, void *param)
{
	t_fdf *fdf;
	char buf[64];

	ft_sprintf(buf, "button: %d, x: %d, y: %d", button, x, y);

	fdf = (t_fdf *)param;
	mlx_clear_window(fdf->mlx_ptr, fdf->wnd_ptr);
	mlx_string_put(fdf->mlx_ptr, fdf->wnd_ptr, 600, 20, FT_COLOR(255, 0,0), buf);
	return (0);
}

int		button_pressed(int button, int x, int y, void *param)
{
	t_fdf *fdf;
	char buf[64];

	ft_sprintf(buf, "button pressed: %d, x: %d, y: %d", button, x, y);

	fdf = (t_fdf *)param;
	mlx_clear_window(fdf->mlx_ptr, fdf->wnd_ptr);
	mlx_string_put(fdf->mlx_ptr, fdf->wnd_ptr, 600, 20, FT_COLOR(255, 0,0), buf);
	return (0);
}

int		button_released(int button, int x, int y, void *param)
{
	t_fdf *fdf;
	char buf[64];

	ft_sprintf(buf, "button released: %d, x: %d, y: %d", button, x, y);

	fdf = (t_fdf *)param;
	mlx_clear_window(fdf->mlx_ptr, fdf->wnd_ptr);
	mlx_string_put(fdf->mlx_ptr, fdf->wnd_ptr, 600, 20, FT_COLOR(255, 0,0), buf);
	return (0);
}

int		mouse_move(int x, int y, void *param)
{
	t_fdf *fdf;
	char buf[64];

	ft_sprintf(buf, "mouse move x: %d, y: %d", x, y);

	fdf = (t_fdf *)param;
	mlx_clear_window(fdf->mlx_ptr, fdf->wnd_ptr);
	mlx_string_put(fdf->mlx_ptr, fdf->wnd_ptr, 600, 20, FT_COLOR(255, 0,0), buf);
	return (0);
}

int		expose_hook(void *param)
{
	(void)param;
	return (0);
}

int		close_notify(void *param)
{
	t_fdf *fdf;
	fdf = (t_fdf *)param;
	mlx_destroy_window(fdf->mlx_ptr, fdf->wnd_ptr);
	exit(0);
}

int		main(int ac, char *av[])
{
	(void)ac;
	(void)av;
	t_fdf fdf;
	char *end;

	fdf.mlx_ptr = mlx_init();
	if (fdf.mlx_ptr)
	{
		fdf.wnd_ptr = mlx_new_window(fdf.mlx_ptr, 1000,500, "Превед!");
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
