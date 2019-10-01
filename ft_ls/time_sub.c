/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_sub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 11:35:06 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/01 11:49:49 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_result	parse_time(time_t time, t_fttime *fttime)
{
	int		count;

	count = -1;
	char *stime = ctime(&time);
	while (++count < (sizeof(g_months)/ sizeof(g_months[0])))
	{
		if (ft_strncmp(stime + 4, g_months[count], 3) == 0)
			break;
	}
	fttime->month = count;
	fttime->day = ft_atoi(stime + 8);
	fttime->hour = ft_atoi(stime + 11);
	fttime->minute = ft_atoi(stime + 14);
	fttime->sec = ft_atoi(stime + 17);
	fttime->year = ft_atoi(stime + 20);
	return (RET_OK);
}

int			time_cmp(t_fttime *t1, t_fttime *t2)
{
 	if (t2->year >= t1->year && t2->month >= t1->month && t2->day >= t1->day &&
 		t2->hour >= t1->hour && t2->minute >= t1->minute && t2->sec >= t1->sec)
	{


	}


}

