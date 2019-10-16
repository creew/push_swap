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
	int 	j;
	t_point	*point;
	t_point p1;
	t_point p2;

	point = fdf->mapout;
	i = -1;
	while (++i < fdf->map_height)
	{
		j = -1;
		while (++j < fdf->map_width)
		{
			if (i != (fdf->map_height - 1))
			{
				p1.x = point[i * fdf->map_width + j].x + get_start_x(fdf);
				p1.y = point[i * fdf->map_width + j].y + get_start_y(fdf);
				p1.color = point[i * fdf->map_width + j].color;
				p2.x = point[(i + 1) * fdf->map_width + j].x + get_start_x(fdf);
				p2.y = point[(i + 1) * fdf->map_width + j].y + get_start_y(fdf);
				p2.color =  point[(i + 1) * fdf->map_width + j].color;
				draw_line(img, &p1, &p2);
			}
			if (j != (fdf->map_width - 1))
			{
				p1.x = point[i * fdf->map_width + j].x + get_start_x(fdf);
				p1.y = point[i * fdf->map_width + j].y + get_start_y(fdf);
				p1.color = point[i * fdf->map_width + j].color;
				p2.x = point[i * fdf->map_width + j + 1].x + get_start_x(fdf);
				p2.y = point[i * fdf->map_width + j + 1].y + get_start_y(fdf);
				p2.color =  point[i * fdf->map_width + j + 1].color;
				draw_line(img, &p1, &p2);
			}
		}
	}
}

void		cp_array(t_point *dst, t_point *src, int size)
{
	int		i;

	i = -1;
	while (++i < size)
	{
		dst->x = src->x;w
		dst->y = src->y;
		dst->z = src->z;
		dst->color = src->color;
		dst++;
		src++;
	}
}

void		do_transformations(t_fdf *fdf)
{
	int size;

	size = fdf->map_width * fdf->map_height;
	cp_array(fdf->mapout, fdf->srcmap, size);
	set_size_transform(fdf->mapout, size, fdf->scale, fdf->z_scale);
	set_z_transform(fdf->mapout, size, get_z_offset(fdf));
	set_x_transform(fdf->mapout, size, get_xy_offset(fdf));
	set_y_transform(fdf->mapout, size, get_xy_offset(fdf));
	if (!fdf->parallel)
		set_iso(fdf->mapout, size);
	colorize_not(fdf->mapout, size);
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
		fill_color(img.data, &img, FT_32COLOR(0u,0u,0u,0u));
		do_transformations(fdf);
		//draw_points(fdf, &img);
		draw_lines(fdf, &img);
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
