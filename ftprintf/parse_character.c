/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_character.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 09:53:18 by eklompus          #+#    #+#             */
/*   Updated: 2019/09/12 20:22:31 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		add_wc_with_flag(t_print *print, wchar_t *wc, int len)
{
	int	count;
	int writed;

	print->str_len = len;
	writed = add_pre_paddings(print);
	count = -1;
	while (++count < len)
		writed += addw_to_out(print, *wc++);
	writed += add_post_paddings(print);
	return (writed);
}

int		add_c_with_flag(t_print *print, char *c, int len)
{
	int	count;
	int writed;

	print->str_len = len;
	writed = add_pre_paddings(print);
	count = -1;
	while (++count < len)
		writed += add_to_out(print, *c++);
	writed += add_post_paddings(print);
	return (writed);
}

int		parse_character(char type, t_print *print, va_list *ptr)
{
	wchar_t			wch;
	unsigned char	val;
	int				count;

	count = 0;
	if (type == 'c' && print->lenmod != LENMOD_L)
	{
		val = (unsigned char)va_arg(*ptr, int);
		count += add_c_with_flag(print, (char *)&val, 1);
	}
	else
	{
		wch = (wchar_t)va_arg(*ptr, wint_t);
		count += add_wc_with_flag(print, &wch, 1);
	}
	return (count);
}
