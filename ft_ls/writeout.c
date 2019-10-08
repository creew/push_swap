/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writeout.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 11:22:28 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/07 11:58:49 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <unistd.h>

void	write_flush(t_lsdata *lsd)
{
	write(1, lsd->bufout, lsd->bufpos);
	lsd->bufpos = 0;
}

int		write_cout(t_lsdata *lsd, char c)
{
	if (lsd->bufpos + 1 >= BUF_SIZE)
		write_flush(lsd);
	lsd->bufout[lsd->bufpos++] = c;
	if (c == '\n')
		write_flush(lsd);
	return (1);
}

int		write_out(t_lsdata *lsd, const char *str)
{
	char		c;
	const char	*src;

	src = str;
	while ((c = *str++))
		write_cout(lsd, c);
	return (int)(str - src - 1);
}

void	write_number(t_lsdata *lsd, t_ulong n)
{
	if (n / 10)
		write_number(lsd, n / 10);
	write_cout(lsd, n % 10 + '0');
}
