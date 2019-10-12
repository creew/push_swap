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

# define FT_COLOR(r,g,b)	(((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF))

# ifdef __APPLE__
#  define FT_MLX_KEY_DOWN	(2)
#  define FT_MLX_KEY_UP		(3)
#  define FT_MLX_MOUSE_DOWN	(4)
#  define FT_MLX_MOUSE_UP	(5)
#  define FT_MLX_MOUSE_MOVED	(6)
#  define FT_MLX_MOUSE_MOVED	(6)
#  define FT_MLX_EXP_NOTIFY	(12)
#  define FT_CLOSE_NOTIFY	(17)
# elif __linux__



# endif


typedef struct	s_fdf
{
	void 	*mlx_ptr;
	void	*wnd_ptr;
}				t_fdf;
#endif
