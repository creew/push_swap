/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 10:17:41 by eklompus          #+#    #+#             */
/*   Updated: 2019/09/13 19:14:24 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	size_t	ft_wcslen(wchar_t *ws)
{
	size_t	len;

	len = 0;
	while (ws[len])
		len++;
	return (len);
}

int				parse_string(char type, t_print *print, va_list *ptr)
{
	char		*cstr;
	wchar_t		*wstr;
	int			count;

	count = 0;
	if (type == 's' && print->lenmod != LENMOD_L)
	{
		cstr = va_arg(*ptr, char *);
		if (!cstr)
			cstr = "(null)";
		print->str_len = ft_strlen(cstr);
		if (print->is_precision && print->precision < print->str_len)
			print->str_len = print->precision;
		count += add_c_with_flag(print, cstr, print->str_len);
	}
	return (count);
	wstr = va_arg(*ptr, wchar_t *);
	if (!wstr)
		wstr = L"(null)";
	print->str_len = ft_wcslen(wstr);
	if (print->is_precision && print->precision < print->str_len)
		print->str_len = print->precision;
	count += add_wc_with_flag(print, wstr, print->str_len);
	return (count);
}
