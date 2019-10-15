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
		calc_optimal_size(fdf);
		redraw_image(fdf);
	}
	else if (key == ARROW_LEFT_KEY)
		fdf->z_rotate -=5;
	else if (key == ARROW_RIGHT_KEY)
		fdf->z_rotate +=5;
	else if (key == Z_KEY)
		fdf->z_scale -= 0.1;
	else if (key == A_KEY)
		fdf->z_scale += 0.1;
	else if (key == PLUS_KEY || key == PLUS_NUM_KEY)
		fdf->scale += 0.2;
	else if (key == MINUS_KEY || key == MINUS_NUM_KEY)
		fdf->scale -= 0.2;
	redraw_image(fdf);
	ft_sprintf(fdf->str_out, "key: %d", key);
	ft_printf("%s\n", fdf->str_out);
	redraw_main_screen(fdf);
	return (0);
}