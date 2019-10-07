/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_sub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 11:35:06 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/07 12:12:06 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_result	parse_time(time_t time, t_fttime *fttime)
{
	size_t		count;
	char		*stime;

	count = 0;
	stime = ctime(&time);
	while (count < (sizeof(g_months) / sizeof(g_months[0])))
	{
		if (ft_strncmp(stime + 4, g_months[count], 3) == 0)
			break ;
		count++;
	}
	fttime->month = count;
	fttime->day = ft_atoi(stime + 8);
	fttime->hour = ft_atoi(stime + 11);
	fttime->minute = ft_atoi(stime + 14);
	fttime->year = ft_atoi(stime + 20);
	return (RET_OK);
}

int			date_cmp_6month(time_t ttf, time_t ttc)
{
	if (ttf > ttc)
		return ((ttf - ttc) > (182 * 24 * 60 * 60));
	else
		return ((ttc - ttf) > (182 * 24 * 60 * 60));
}
