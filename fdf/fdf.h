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

#include "libft.h"
# define FT_COLOR(r,g,b)	(((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF))

# ifdef __APPLE__
#  define KeyPress			(2)
#  define KeyRelease		(3)
#  define ButtonPress		(4)
#  define ButtonRelease		(5)
#  define MotionNotify		(6)
#  define Expose			(12)
#  define GraphicsExpose	(17)

#  define PointerMotionMask	(0)
#  define ButtonPressMask	(0)
#  define ButtonReleaseMask	(0)
# elif __linux__
#  include <X11/Xlib.h>

#define ESC_KEY		(65307)
# endif


typedef struct	s_fdf
{
	void 	*mlx_ptr;
	void	*wnd_ptr;
}				t_fdf;
#endif
