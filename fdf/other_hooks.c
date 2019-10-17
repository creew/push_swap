/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 13:41:51 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/17 13:41:52 by eklompus         ###   ########.fr       */
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
