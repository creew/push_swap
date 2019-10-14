/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 19:03:32 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/14 19:03:33 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
