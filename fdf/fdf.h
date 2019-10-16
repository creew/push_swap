/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 11:03:20 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/11 11:03:21 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include <stdlib.h>
#include <math.h>
#include "libft.h"
#include "mlx.h"
#include "ft_printf.h"

# define FT_COLOR(r,g,b)		(((r & 0xFFu) << 16u) | ((g & 0xFFu) << 8u) | \
									(b & 0xFFu))

# define FT_32COLOR(r,g,b,a)	(((a & 0xFFu) << 24u) | ((r & 0xFFu) << 16u) | \
									((g & 0xFFu) << 8u) | (b & 0xFFu))

# define FT_32COLOR_GET_R(c)	((c >> 16u) & 0xFFu)
# define FT_32COLOR_GET_G(c)	((c >> 8u) & 0xFFu)
# define FT_32COLOR_GET_B(c)	((c) & 0xFFu)
# define FT_32COLOR_GET_A(c)	((c >> 24u) & 0xFFu)

# define WHITE_COLOR		(0xFFFFFF)
# define BLACK_COLOR		(0)
# define GREEN_COLOR		(0x00FF00)
# define BROWN_COLOR		(0x964B00)

# ifdef __APPLE__
#  define KeyPress			(2)
#  define KeyRelease		(3)
#  define ButtonPress		(4)
#  define ButtonRelease		(5)
#  define MotionNotify		(6)
#  define Expose			(12)
#  define DestroyNotify		(17)

#  define KeyPressMask		(0)
#  define PointerMotionMask	(0)
#  define ButtonPressMask	(0)
#  define ButtonReleaseMask	(0)
#  define ExposureMask		(0)

#  define A_KEY				(0)
#  define Z_KEY				(6)
#  define ONE_KEY			(18)
#  define ONE_NUM_KEY		(83)
#  define TWO_KEY			(19)
#  define TWO_NUM_KEY		(84)
#  define THREE_KEY			(20)
#  define THREE_NUM_KEY		(85)
#  define ESC_KEY			(53)
#  define ZERO_KEY			(29)
#  define ZERO_NUM_KEY		(82)
#  define PLUS_KEY			(24)
#  define PLUS_NUM_KEY		(69)
#  define MINUS_KEY			(27)
#  define MINUS_NUM_KEY		(78)
#  define ARROW_LEFT_KEY	(123)
#  define ARROW_RIGHT_KEY	(124)

#  define WND_WIDTH			(1500)
#  define WND_HEIGHT		(800)
# elif __linux__
#  include <X11/Xlib.h>
#  define A_KEY				(97)
#  define Z_KEY				(122)
#  define ONE_KEY			(49)
#  define ONE_NUM_KEY		(49)
#  define TWO_KEY			(50)
#  define TWO_NUM_KEY		(50)
#  define THREE_KEY			(51)
#  define THREE_NUM_KEY		(51)
#  define ZERO_KEY			(48)
#  define ZERO_NUM_KEY		(48)
#  define PLUS_KEY			(61)
#  define PLUS_NUM_KEY		(61)
#  define MINUS_KEY			(45)
#  define MINUS_NUM_KEY		(45)
#  define ARROW_LEFT_KEY	(65361)
#  define ARROW_RIGHT_KEY	(65363)
#  define ESC_KEY			(65307)

#  define WND_WIDTH			(800)
#  define WND_HEIGHT		(400)
# endif

# define FT_COS30				(0.86602540378443870761)
# define FT_SIN30				(0.5)

# define UB_WIDTH				(WND_WIDTH)
# define UB_HEIGHT				(WND_HEIGHT / 20)

# define BB_WIDTH				(WND_WIDTH)
# define BB_HEIGHT				(WND_HEIGHT / 20)
# define BB_YPOS				(WND_HEIGHT - BB_HEIGHT)


# define MAIN_YPOS				(UB_HEIGHT)
# define MAIN_WIDTH				(WND_WIDTH)
# define MAIN_HEIGHT			(WND_HEIGHT - UB_HEIGHT - BB_HEIGHT)

# define RET_OK					(0)
# define ERR_CAN_T_OPEN_FILE	(-1)
# define ERR_NOT_EQUAL_WIDTH	(-2)
# define ERR_ENOMEM				(-3)

typedef	unsigned int	t_uint;

typedef struct	s_img_param {
	char 		*data;
	int			sizeline;
	int			endian;
	int 		bits_per_pixel;
	int			height;
	int 		width;
}				t_img_param;

typedef struct	s_dpoint
{
	double		x;
	double		y;
	double		z;
}				t_dpoint;

typedef struct	s_point
{
	int			x;
	int			y;
	int			z;
	int 		color;
}				t_point;

typedef struct	s_mousekeys
{
	int			but1_pressed;
	int 		but2_pressed;
	int 		press2_x;
	int			press2_y;
	int 		press1_x;
	int			press1_y;
	int 		cur_x;
	int 		cur_y;
}				t_mousekeys;

typedef struct	s_fdf
{
	t_point		*srcmap;
	t_point		*mapout;
	int			map_width;
	int 		map_height;
	int			wnd_width;
	int			wnd_height;
	void 		*mlx_ptr;
	void		*wnd_ptr;

	int			parallel;

	double		scale;
	double		z_scale;
	long		z_rotate;
	long		xy_rotate;

	long		z_rotate_add;
	long		xy_rotate_add;
	int 		shift_x_add;
	int 		shift_y_add;

	t_mousekeys	mouse_keys;

	int 		shift_x;
	int 		shift_y;

	char		str_out[64];
	void		*upper_border;
	void		*bottom_border;
	void		*main_image;
}				t_fdf;

int				read_file(char *name, t_fdf *fdf);
int				redraw_main_screen(t_fdf *fdf);
int				init_upper_border(t_fdf *fdf);
int				init_bottom_border(t_fdf *fdf);
int				init_main_image(t_fdf *fdf);
void			fill_color(t_img_param *img, t_uint setcolor);

void			redraw_image(t_fdf *fdf);

void			set_key_pressed(t_mousekeys *keys, int button, int x, int y);
void			set_key_released(t_mousekeys *keys, int button, int x, int y);
void			get_key_diff(t_mousekeys *keys, int button, int *x, int *y);
void			set_current_xy(t_mousekeys *keys, int x, int y);
int				is_key_pressed(t_mousekeys *keys, int button);
void			cp_array(t_point *dst, t_point *src, int size);

void			set_size_transform(t_point *arr, int size, double scale, double zscale);
void			set_x_transform(t_point *arr, int size, long x_rotate);
void			set_y_transform(t_point *arr, int size, long y_rotate);
void	 		set_z_transform(t_point *arr, int size, long z);
void			set_iso(t_point *arr, int size);


int				get_start_x(t_fdf *fdf);
int 			get_start_y(t_fdf *fdf);
long			get_z_offset(t_fdf *fdf);
long			get_xy_offset(t_fdf *fdf);

int				button_pressed(int button, int x, int y, void *param);
int				button_released(int button, int x, int y, void *param);
int				mouse_move(int x, int y, void *param);

int				key_hook(int key, void *param);

void			set_point(t_img_param *img, int x, int y, int color);
void			draw_line(t_img_param *img, t_point *p1, t_point *p2);

void			do_transformations(t_fdf *fdf);

void			calc_optimal_size(t_fdf *fdf);
void			normalize_map(t_point *point, int width, int height);

int				get_color(int color1, int color2, int total, int step);
void			colorize_not(t_point *point, int size);
void			colorise_map(t_point *point, int size);
#endif
