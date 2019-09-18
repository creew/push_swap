/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_precision.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 21:12:40 by eklompus          #+#    #+#             */
/*   Updated: 2019/09/13 19:10:11 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		parse_precision(t_print *print, const char *format, va_list *ptr)
{
	size_t			count;
	char			c;
	int				f;

	f = 1;
	if (format[(count = 0)] == '.')
	{
		print->is_precision = 1;
		count++;
		while (format[count] == '*' || ft_isdigit(format[count]))
		{
			c = format[count];
			if (c == '*' && (f = 1))
				print->precision = va_arg(*ptr, int);
			else
			{
				if (f && !(f = 0))
					print->precision = 0;
				print->precision *= 10;
				print->precision += (c - '0');
			}
			count++;
		}
	}
	return (count);
}
