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

static void	draw_points(t_fdf *fdf, char *data, t_img_param *img)
{
	int		i;
	int		size;
	t_point	*point;

	i = -1;
	size = fdf->map_height * fdf->map_width;
	point = fdf->mapout;
	while (++i < size)
	{
		set_point(data, img, point->x + get_start_x(fdf),
					  point->y + get_start_y(fdf), point->color);
		point++;
	}
}

static void	draw_lines(t_fdf *fdf, char *data, t_img_param *img)
{
	int		i;
	int 	j;
	t_point	*point;

	point = fdf->mapout;
	i = -1;
	while (++i < fdf->map_height)
	{
		j = -1;
		while (++j < fdf->map_width)
		{
			if (i != (fdf->map_height - 1))
			{
				draw_line(data, img, point[i * fdf->map_width + j].x + get_start_x(fdf),
						  point[i * fdf->map_width + j].y + + get_start_y(fdf),
						  point[(i + 1) * fdf->map_width + j].x + get_start_x(fdf),
						  point[(i + 1) * fdf->map_width + j].y + + get_start_y(fdf),
						  point[i * fdf->map_width + j].color, point[(i + 1) * fdf->map_width + j].color);
			}
			if (j != (fdf->map_width - 1))
			{
				draw_line(data, img, point[i * fdf->map_width + j].x + get_start_x(fdf),
						  point[i * fdf->map_width + j].y + get_start_y(fdf),
						  point[i * fdf->map_width + j + 1].x + get_start_x(fdf),
						  point[i * fdf->map_width + j + 1].y + get_start_y(fdf),
						  point[i * fdf->map_width + j].color, point[i * fdf->map_width + j + 1].color);
			}
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

void		do_transformations(t_fdf *fdf)
{
	cp_array(fdf->mapout, fdf->srcmap, fdf->map_width, fdf->map_height);
	set_size_transform(fdf->mapout, fdf->map_width * fdf->map_height, fdf->scale, fdf->z_scale);
	set_z_transform(fdf->mapout, fdf->map_width, fdf->map_height, get_z_offset(fdf));
	set_xy_transform(fdf->mapout, fdf->map_width, fdf->map_height, get_xy_offset(fdf));
	if (!fdf->parallel)
		set_iso(fdf->mapout, fdf->map_width, fdf->map_height);
	colorize_not(fdf->mapout, fdf->map_width * fdf->map_height);
}

void		redraw_image(t_fdf *fdf)
{
	char			*img_data;
	t_img_param		img;

	img.height = MAIN_HEIGHT;
	img.width = MAIN_WIDTH;
	img_data = mlx_get_data_addr(fdf->main_image, &img.bits_per_pixel,
								 &img.sizeline, &img.endian);
	if (img_data)
	{
		fill_color(img_data, &img, FT_32COLOR(0u,0u,0u,0u));
		do_transformations(fdf);
		draw_points(fdf, img_data, &img);
		draw_lines(fdf, img_data, &img);
	}
}

int 		redraw_main_screen(t_fdf *fdf)
{
	mlx_clear_window(fdf->mlx_ptr, fdf->wnd_ptr);
	if (fdf->upper_border)
		mlx_put_image_to_window(fdf->mlx_ptr, fdf->wnd_ptr, fdf->upper_border, 0, 0);
	if (fdf->bottom_border)
		mlx_put_image_to_window(fdf->mlx_ptr, fdf->wnd_ptr, fdf->bottom_border, 0, BB_YPOS);
	if (fdf->main_image)
		mlx_put_image_to_window(fdf->mlx_ptr, fdf->wnd_ptr, fdf->main_image, 0, MAIN_YPOS);
	ft_sprintf(fdf->str_out, "scale: %d%%", (int)(fdf->scale * 100));
	mlx_string_put(fdf->mlx_ptr, fdf->wnd_ptr, 20, 10, FT_COLOR(255, 255,255), fdf->str_out);
	ft_sprintf(fdf->str_out, "z scale: %d%%", (int)(fdf->z_scale * 100));
	mlx_string_put(fdf->mlx_ptr, fdf->wnd_ptr, 20, 50, FT_COLOR(255, 255,255), fdf->str_out);
	ft_sprintf(fdf->str_out, "z angle: %d degree", (fdf->z_rotate + fdf->z_rotate_add) % 360);
	mlx_string_put(fdf->mlx_ptr, fdf->wnd_ptr, 200, 50, FT_COLOR(255, 255,255), fdf->str_out);
	//mlx_string_put(fdf->mlx_ptr, fdf->wnd_ptr, WND_HEIGHT - 300, 20, FT_COLOR(255, 255,255), fdf->str_out);
	return (RET_OK);
}
