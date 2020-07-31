/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 12:30:51 by eklompus          #+#    #+#             */
/*   Updated: 2019/09/23 17:16:44 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int			read_int_val(char *arg, int *res)
{
	int ret;

	ret = ft_safe_atoi(arg, res);
	if (ret == FT_ATOI_OK)
		return (RET_OK);
	if (ret == FT_ATOI_OVERFLOW)
		return (ERROR_OVERFLOW_INTEGER);
	if (ret == FT_ATOI_EMPTY_ARG)
		return (ERROR_ARG_ONLY_PM);
	if (ret == FT_ATOI_WRONG_CHAR)
		return (ERROR_WRONG_INTEGER);
	return (ERROR_UNKNOWN);
}

char		*get_action_str(int i)
{
	if (i == S_SA)
		return ("sa");
	if (i == S_SB)
		return ("sb");
	if (i == S_SS)
		return ("ss");
	if (i == S_PA)
		return ("pa");
	if (i == S_PB)
		return ("pb");
	if (i == S_RA)
		return ("ra");
	if (i == S_RB)
		return ("rb");
	if (i == S_RR)
		return ("rr");
	if (i == S_RRA)
		return ("rra");
	if (i == S_RRB)
		return ("rrb");
	if (i == S_RRR)
		return ("rrr");
	return ("");
}
