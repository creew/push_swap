/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_precision.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 21:12:40 by eklompus          #+#    #+#             */
/*   Updated: 2019/09/20 17:53:13 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		parse_precision(t_print *print, const char *format, va_list *ptr)
{
	size_t			count;
	char			c;
	int				res;
	int				prev_pow;

	if (format[(count = 0)] == '.')
	{
		print->is_precision = 1;
		count++;
		prev_pow = 0;
		while (format[count] == '*' || ft_isdigit(format[count]))
		{
			c = format[count];
			if (c == '*')
			{
				res = va_arg(*ptr, int);
				if (res >= 0)
					print->precision = res;
				else
				{
					if (prev_pow != 0)
					{
						print->flags |= FLAG_MINUS;
						print->width = -res;
					}
					else
						print->precision = -1;
				}
				prev_pow = 0;
			}
			else
			{
				if (prev_pow == 0)
					print->precision = 0;
				print->precision *= 10;
				print->precision += (c - '0');
				prev_pow = 1;
			}
			count++;
		}
		if (print->precision == -1)
		{
			print->is_precision = 0;
			print->precision = 0;
		}
	}
	return (count);
}
