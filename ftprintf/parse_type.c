/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 09:05:37 by eklompus          #+#    #+#             */
/*   Updated: 2019/09/12 18:06:26 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		parse_type(t_print *print, const char *format)
{
	char c;

	if ((c = *format))
	{
		print->type = c;
		if (ft_strchr(DEPRECATED_STR, c))
			print->type = ft_tolower(c);
		return (1);
	}
	return (0);
}
