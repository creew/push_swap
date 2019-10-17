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

#include "fdf.h"

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

void	print_usage()
{
	ft_putendl("Usage: program fdfmap");
	ft_putendl("   Use your mouse with pushed left button for rotate map,");
	ft_putendl("   or with pushed right button for moving map.");
	ft_putendl("   Scrolling mouse wheel for changing scale.");
	ft_putendl("");
	ft_putendl("Keyboard:");
	ft_putendl("   A - increment Z scale.");
	ft_putendl("   Z - decrement Z scale.");
	ft_putendl("   + - increment common scale.");
	ft_putendl("   - - decrement common scale.");
	ft_putendl("   -> - rotate map right.");
	ft_putendl("   <- - rotate map left.");
	ft_putendl("   0 - zeroes scale rotate and position.");
	ft_putendl("   . - toggle woo/bresenham.");
}

void	initfdf(t_fdf *fdf)
{
	bzero(fdf, sizeof(*fdf));
	fdf->wnd_width = WND_WIDTH;
	fdf->wnd_height = WND_HEIGHT;
	fdf->scale = 1;
	fdf->z_scale = 0.2;
}

int		main(int ac, char *av[])
{
	t_fdf fdf;

	if (ac < 2)
	{
		print_usage();
		exit(0);
	}
	initfdf(&fdf);
	if (read_file(av[1], &fdf) != RET_OK)
	{
		exit(0);
	}
	normalize_map(fdf.srcmap, fdf.map_width, fdf.map_height);
	colorize_not(fdf.srcmap, fdf.map_width * fdf.map_height);
	fdf.mlx_ptr = mlx_init();
	fdf.mapout = malloc(sizeof(t_point) * fdf.map_width * fdf.map_height);
	init_upper_border(&fdf);
	init_bottom_border(&fdf);
	init_main_image(&fdf);
	calc_optimal_size(&fdf);
	redraw_image(&fdf);
	if (fdf.mlx_ptr)
	{
		fdf.wnd_ptr = mlx_new_window(fdf.mlx_ptr, fdf.wnd_width, fdf.wnd_height, "Превед!");
		if (fdf.wnd_ptr)
		{
			mlx_hook(fdf.wnd_ptr, KeyPress, KeyPressMask, key_hook, &fdf);
			mlx_hook(fdf.wnd_ptr, Expose, ExposureMask , expose_hook, &fdf);
			mlx_hook(fdf.wnd_ptr, MotionNotify, PointerMotionMask, mouse_move, &fdf);
			mlx_hook(fdf.wnd_ptr, DestroyNotify, 0, close_notify, &fdf);
			mlx_hook(fdf.wnd_ptr, ButtonPress, ButtonPressMask, button_pressed, &fdf);
			mlx_hook(fdf.wnd_ptr, ButtonRelease, ButtonReleaseMask, button_released, &fdf);
			mlx_do_key_autorepeaton(fdf.mlx_ptr);
			mlx_loop(fdf.mlx_ptr);
		}
	}
	return (0);
}
