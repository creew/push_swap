/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 09:05:37 by eklompus          #+#    #+#             */
/*   Updated: 2019/09/20 19:50:29 by eklompus         ###   ########.fr       */
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
