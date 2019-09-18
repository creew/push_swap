/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lenmod.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 09:12:58 by eklompus          #+#    #+#             */
/*   Updated: 2019/09/13 19:18:04 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			parse_lenmod(t_print *print, const char *format)
{
	char	c;
	size_t	count;

	count = 0;
	c = *format++;
	if (ft_strchr(LENMOD_STR, c))
	{
		count++;
		if (c == 'h' && *format == 'h' && ++count)
			print->lenmod = LENMOD_HH;
		else if (c == 'h')
			print->lenmod = LENMOD_H;
		else if (c == 'l' && *format == 'l' && ++count)
			print->lenmod = LENMOD_LL;
		else if (c == 'l')
			print->lenmod = LENMOD_L;
		else if (c == 'j')
			print->lenmod = LENMOD_J;
		else if (c == 't')
			print->lenmod = LENMOD_T;
		else if (c == 'z')
			print->lenmod = LENMOD_Z;
		else if (c == 'L')
			print->lenmod = LENMOD_BL;
	}
	return (count);
}
