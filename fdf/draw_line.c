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

void set_point(char *data, t_img_param *img, int x, int y, int color)
{
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

int	get_color(int color1, int color2, int total, int step)
{



}

void draw_line(char *data, t_img_param *img, int x1, int y1, int x2, int y2, int color1, int color2)
{
	int dx = (x2 - x1 >= 0 ? 1 : -1);
	int dy = (y2 - y1 >= 0 ? 1 : -1);

	int lengthX = ABS(x2 - x1);
	int lengthY = ABS(y2 - y1);

	int length;

	if (lengthX == 0 && lengthY == 0)
		set_point(data, img, x1, y1, color);

	if (lengthY <= lengthX)
	{
		// Начальные значения
		int x = x1;
		int y = y1;
		int d = -lengthX;

		// Основной цикл
		length = lengthX + 1;
		while(length--)
		{
			set_point(data, img, x, y, color);
			x += dx;
			d += 2 * lengthY;
			if (d > 0) {
				d -= 2 * lengthX;
				y += dy;
			}
		}
	}
	else
	{
		// Начальные значения
		int x = x1;
		int y = y1;
		int d = - lengthY;

		// Основной цикл
		length = lengthY + 1;
		while(length--)
		{
			set_point(data, img, x, y, color);
			y += dy;
			d += 2 * lengthX;
			if (d > 0) {
				d -= 2 * lengthY;
				x += dx;
			}
		}
	}
}