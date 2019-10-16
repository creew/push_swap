/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 15:14:34 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/13 15:14:35 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_points(t_fdf *fdf, t_img_param *img)
{
	int		i;
	int		size;
	t_point	*point;

	i = -1;
	size = fdf->map_height * fdf->map_width;
	point = fdf->mapout;
	while (++i < size)
	{
		set_point(img, point->x + get_start_x(fdf),
			point->y + get_start_y(fdf), point->color);
		point++;
	}
}

static void	draw_lines(t_fdf *fdf, t_img_param *img)
{
	int		i;
	int		j;
	t_point	*point;

	point = fdf->mapout;
	i = -1;
	while (++i < fdf->map_height)
	{
		j = -1;
		while (++j < fdf->map_width)
		{
			if (i != (fdf->map_height - 1))
				draw_line(img, &point[i * fdf->map_width + j],
					&point[(i + 1) * fdf->map_width + j]);
			if (j != (fdf->map_width - 1))
				draw_line(img, &point[i * fdf->map_width + j],
					&point[i * fdf->map_width + j + 1]);
		}
	}
}

void		redraw_image(t_fdf *fdf)
{
	t_img_param		img;

	img.height = MAIN_HEIGHT;
	img.width = MAIN_WIDTH;
	img.data = mlx_get_data_addr(fdf->main_image, &img.bits_per_pixel,
		&img.sizeline, &img.endian);
	if (img.data)
	{
		fill_color(&img, BLACK_COLOR);
		do_transformations(fdf);
		draw_lines(fdf, &img);
	}
}

int			redraw_main_screen(t_fdf *fdf)
{
	char	buf[64];

	mlx_clear_window(fdf->mlx_ptr, fdf->wnd_ptr);
	if (fdf->upper_border)
		mlx_put_image_to_window(fdf->mlx_ptr, fdf->wnd_ptr,
			fdf->upper_border, 0, 0);
	if (fdf->bottom_border)
		mlx_put_image_to_window(fdf->mlx_ptr, fdf->wnd_ptr,
			fdf->bottom_border, 0, BB_YPOS);
	if (fdf->main_image)
		mlx_put_image_to_window(fdf->mlx_ptr, fdf->wnd_ptr,
			fdf->main_image, 0, MAIN_YPOS);
	ft_sprintf(buf, "scale: %d%%", (int)(fdf->scale * 100));
	mlx_string_put(fdf->mlx_ptr, fdf->wnd_ptr, 20, 10,
		WHITE_COLOR, buf);
	ft_sprintf(buf, "z scale: %d%%", (int)(fdf->z_scale * 100));
	mlx_string_put(fdf->mlx_ptr, fdf->wnd_ptr, 20, 50,
		WHITE_COLOR, buf);
	ft_sprintf(buf, "z angle: %d degree", get_z_offset(fdf) % 360);
	mlx_string_put(fdf->mlx_ptr, fdf->wnd_ptr, 200, 50,
		WHITE_COLOR, buf);
	mlx_string_put(fdf->mlx_ptr, fdf->wnd_ptr, WND_HEIGHT - 300, 20,
		WHITE_COLOR, fdf->str_out);
	return (RET_OK);
}
