/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_arrays.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 14:55:19 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/14 14:55:20 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		set_xy_transform(t_point *arr, int width, int height, long xy_rotate)
{
	int			i;
	int			size;
	double		cos_xy;
	double		sin_xy;
	t_dpoint	dp;

	cos_xy = cos((double)(xy_rotate) * M_PI / 180);
	sin_xy = sin((double)(xy_rotate) * M_PI / 180);
	size = width * height;
	i = -1;
	while (++i < size)
	{
		dp.x = arr->x * cos_xy - arr->y * sin_xy * sin_xy + arr->z * cos_xy * sin_xy;
		dp.y = arr->y * cos_xy + arr->z * sin_xy;
		dp.z = -arr->x * sin_xy - arr->y * sin_xy * cos_xy + arr->z * cos_xy * cos_xy;
		arr->x = (int)dp.x;
		arr->y = (int)dp.y;
		arr->z = (int)dp.z;
		arr++;
	}
}

void		set_iso(t_point *arr, int width, int height)
{
	int		i;
	int		j;
	double	x1;
	double	y1;

	i = -1;
	while (++i < height)
	{
		j = -1;
		while (++j < width)
		{
			x1 = (arr->x - arr->y) * FT_COS30;
			y1 = -arr->z + (arr->x + arr->y) * FT_SIN30;
			arr->x = (int)x1;
			arr->y = (int)y1;
			arr++;
		}
	}
}

void		cp_array(t_point *dst, t_point *src, int width, int height)
{
	int		i;
	int		size;

	i = -1;
	size = width * height;
	while (++i < size)
	{
		dst->x = src->x;
		dst->y = src->y;
		dst->z = src->z;
		dst->color = src->color;
		dst++;
		src++;
	}
}
