/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_width.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 20:48:04 by eklompus          #+#    #+#             */
/*   Updated: 2019/09/13 19:16:03 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		parse_width(t_print *print, const char *format, va_list *ptr)
{
	int			count;
	char		c;
	int			f;

	count = 0;
	f = 1;
	while (format[count] == '*' || ft_isdigit(format[count]))
	{
		c = format[count];
		if (c == '*' && (f = 1))
			print->width = va_arg(*ptr, unsigned int);
		else
		{
			if (f && !(f = 0))
				print->width = 0;
			print->width *= 10;
			print->width += (c - '0');
		}
		count++;
	}
	return (count);
}
