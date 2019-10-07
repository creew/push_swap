/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_strings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 11:51:07 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/07 11:58:49 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		write_out_total(t_lsdata *lsd, t_uint blocks)
{
	write_out(lsd, "total ");
	write_number(lsd, blocks);
	write_cout(lsd, '\n');
	return (1);
}

int		write_out_path(t_lsdata *lsd, char *path)
{
	write_out(lsd, path);
	write_cout(lsd, ':');
	write_cout(lsd, '\n');
	return (1);
}
