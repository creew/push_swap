/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 15:20:40 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/13 15:20:41 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fill_color(char *data, t_img_param *img, t_uint setcolor)
{
	int		count;
	int		col;
	char	*color;

	count = 0;
	while (count < img->height)
	{
		col = 0;
		while (col < img->sizeline)
		{
			color = data + col;
			*color = FT_32COLOR_GET_B(setcolor);
			*(color + 1) = FT_32COLOR_GET_G(setcolor);
			*(color + 2) = FT_32COLOR_GET_R(setcolor);
			*(color + 3) = FT_32COLOR_GET_A(setcolor);
			col += img->bits_per_pixel / 8;
		}
		data += img->sizeline;
		count++;
	}
}

int		init_upper_border(t_fdf *fdf)
{
	char			*img_data;
	t_img_param		img;

	img.height = UB_HEIGHT;
	img.width = UB_WIDTH;
	fdf->upper_border = mlx_new_image(fdf->mlx_ptr, img.width, img.height);
	if (fdf->upper_border)
	{
		img_data = mlx_get_data_addr(fdf->upper_border, &img.bits_per_pixel,
									 &img.sizeline, &img.endian);
		if (img_data)
		{
			fill_color(img_data, &img, FT_32COLOR(255u,0u,0u,10u));
		}
	}
}

int		init_bottom_border(t_fdf *fdf)
{
	char			*img_data;
	t_img_param		img;

	img.height = BB_HEIGHT;
	img.width = BB_WIDTH;
	fdf->bottom_border = mlx_new_image(fdf->mlx_ptr, img.width, img.height);
	if (fdf->bottom_border)
	{
		img_data = mlx_get_data_addr(fdf->bottom_border, &img.bits_per_pixel,
									 &img.sizeline, &img.endian);
		if (img_data)
		{
			fill_color(img_data, &img, FT_32COLOR(0u,255u,0u,10u));
		}
	}
}
