/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 16:24:54 by eklompus          #+#    #+#             */
/*   Updated: 2019/09/04 21:10:51 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	hs_len;
	size_t	ne_len;
	size_t	pos;

	pos = 0;
	hs_len = ft_strlen(haystack);
	ne_len = ft_strlen(needle);
	while (haystack[pos] && ((pos + ne_len) <= len))
	{
		if (ft_strncmp(haystack + pos, needle, ne_len) == 0)
			return (char *)(haystack + pos);
		pos++;
	}
	return (NULL);
}
