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



void	calc_limits(t_point *map, int size, t_point *wh, t_point *start)
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
	wh->x = ABS(wh->x - start->x);
	wh->y = ABS(wh->y - start->y);
}

void	calc_optimal_size(t_fdf *fdf)
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

void	print_usage()
{


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
			mlx_key_hook(fdf.wnd_ptr, key_hook, &fdf);
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
