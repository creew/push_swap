/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readarg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 16:01:30 by eklompus          #+#    #+#             */
/*   Updated: 2019/09/24 16:08:53 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int		arg_read(int n, char *av[], t_stack *st1)
{
	int		res;
	int		ret;

	ret = ERROR_NO_ARGUMENTS;
	while (n > 1)
	{
		if ((ret = safe_atoi(av[n - 1], &res)) != RET_OK)
			break ;
		stack_push(st1, res);
		n--;
	}
	return (ret);
}
