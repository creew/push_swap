/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 16:43:47 by eklompus          #+#    #+#             */
/*   Updated: 2019/09/21 20:08:34 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			get_base(const char **nptr, int base)
{
	const char *ptr;

	if (base == 0)
	{
		ptr = *nptr;
		if (ptr[0] == '0' && (ptr[1] == 'x' || ptr[1] == 'X'))
		{
			base = 16;
			*nptr = ptr + 2;
		}
		else if (ptr[0] == '0')
		{
			base = 8;
			*nptr = ptr + 1;
		}
		else
			base = 10;
	}
	return (base);
}

static int	get_char_in_range(int c, int base)
{
	if (c >= '0' && c <= '9')
		c -= 10;
	else if (c >= 'a' && c <= 'z')
		c = c - 'a' + 10;
	else if (c >= 'A' && c <= 'Z')
		c = c - 'A' + 10;
	else
		return (-1);
	if (c < base)
		return (c);
	return (-1);
}

long				ft_strtol(const char *nptr, char **endptr, int base)
{
	int		isneg;
	long 	res;
	int		val;
	long	prev_val;

	isneg = 1;
	res = 0;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			isneg = -1;
		nptr++;
	}
	base = get_base(&nptr, base);
	while ((val = get_char_in_range(*nptr, base)) != -1)
	{
		prev_val = res;
		res *= base;
		res += isneg > 0 ? val : -val;
		if (isneg > 0 && res < prev_val)
			return (FT_LMAX);
		if (isneg < 0 && res > prev_val)
			return (-FT_LMIN);
		nptr++;
	}
	if (endptr)
		*endptr = (char *)nptr;
	return (res);
}