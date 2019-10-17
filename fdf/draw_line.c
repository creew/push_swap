/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 08:20:02 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/15 08:20:03 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_point(t_img_param *img, int x, int y, int color)
{
	char *data;

	data = img->data;
	if (x >= 0 && y >= 0 && x < img->width && y < img->height)
	{
		data += y * img->sizeline;
		data += x * img->bits_per_pixel / 8;
		*data = FT_32COLOR_GET_B(color);
		*(data + 1) = FT_32COLOR_GET_G(color);
		*(data + 2) = FT_32COLOR_GET_R(color);
		*(data + 3) = FT_32COLOR_GET_A(color);
	}
}

int		get_color(int color1, int color2, int total, int step)
{
	t_uint	r;
	t_uint	g;
	t_uint	b;
	int		c1;
	int		c2;

	if (total != 0)
	{
		c1 = (color1 >> 16) & 0xFF;
		c2 = (color2 >> 16) & 0xFF;
		r = c1 + (c2 - c1) * step / total;
		c1 = (color1 >> 8) & 0xFF;
		c2 = (color2 >> 8) & 0xFF;
		g = c1 + (c2 - c1) * step / total;
		c1 = (color1) & 0xFF;
		c2 = (color2) & 0xFF;
		b = c1 + (c2 - c1) * step / total;
	}
	else
		return (color1);
	return ((int)(FT_COLOR(r, g, b)));
}

void	draw_line(t_img_param *img, t_point *p1, t_point *p2)
{
	t_point		len;
	t_point		d;
	t_point		xy;
	int			length;
	int			delta;

	len.x = p2->x - p1->x;
	len.y = p2->y - p1->y;
	d.x = len.x >= 0 ? 1 : -1;
	d.y = len.y >= 0 ? 1 : -1;
	len.x = len.x < 0 ? -len.x : len.x;
	len.y = len.y < 0 ? -len.y : len.y;
	if (len.x == 0 && len.y == 0)
		set_point(img, p1->x, p1->y, get_color(p1->color, p2->color, 2, 1));
	xy.x = p1->x;
	xy.y = p1->y;
	if (len.y <= len.x)
	{
		delta = -len.x;
		length = len.x + 1;
		while (length--)
		{
			set_point(img, xy.x, xy.y, get_color(p1->color, p2->color, len.x + 1, len.x + 1 - length));
			xy.x += d.x;
			delta += 2 * len.y;
			if (delta > 0)
			{
				delta -= 2 * len.x;
				xy.y += d.y;
			}
		}
	}
	else
	{
		delta = -len.y;
		length = len.y + 1;
		while (length--)
		{
			set_point(img, xy.x, xy.y, get_color(p1->color, p2->color, len.y + 1, len.y + 1 - length));
			xy.y += d.y;
			delta += 2 * len.x;
			if (delta > 0)
			{
				delta -= 2 * len.y;
				xy.x += d.x;
			}
		}
	}
}

