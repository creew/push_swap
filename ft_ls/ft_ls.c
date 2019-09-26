/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 10:27:11 by eklompus          #+#    #+#             */
/*   Updated: 2019/09/26 14:48:38 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

int main(int ac, char *av[])
{
	t_uint	flags;
	t_list	*args;
	int		ret;

	flags = 0;
	args = NULL;
	if ((ret = parse_args(&args, ac, av, &flags)) == RET_OK)
	{



	}
	return (ret);
}
