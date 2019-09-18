/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 16:50:30 by eklompus          #+#    #+#             */
/*   Updated: 2019/09/13 19:03:27 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		clear_tprint(t_print *print)
{
	print->type = 0;
	print->is_precision = 0;
	print->flags = 0;
	print->width = 0;
	print->precision = 0;
	print->lenmod = 0;
	print->pre_len = 0;
	print->pad_len = 0;
	print->str_len = 0;
	print->is_val = 0;
	print->is_neg = 0;
}

static int		parse_str(t_print *print, const char *format, va_list *ptr)
{
	size_t	count;

	count = 0;
	count += parse_flags(print, format + count);
	count += parse_width(print, format + count, ptr);
	count += parse_precision(print, format + count, ptr);
	count += parse_lenmod(print, format + count);
	count += parse_type(print, format + count);
	return (count);
}

int				ft_printf(const char *format, ...)
{
	t_print		print;
	va_list		ptr;
	int			out;

	out = 0;
	va_start(ptr, format);
	ft_bzero(&print, sizeof(t_print));
	while (*format)
	{
		if (*format == '%')
		{
			clear_tprint(&print);
			format++;
			format += parse_str(&print, format, &ptr);
			out += parse_format(&print, &ptr);
		}
		else
			out += add_to_out(&print, *format++);
	}
	flush_buf(&print);
	va_end(ptr);
	return (out);
}

int				main(void)
{
	int				len;
	//unsigned int	xren;

	//xren = 0x0001AA00;
	//char *str = "hello";
	unsigned long long dr = 0x0f;
	len = ft_printf("%b str:%s\n", dr, "sad");
	printf("len: %d\n", len);
	return (0);
}
