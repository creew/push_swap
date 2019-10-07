/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 11:03:11 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/07 12:47:13 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_result	write_usage(void)
{
	ft_putstr_fd("usage: ls [-", 2);
	ft_putstr_fd(LEGAL_OPTIONS, 2);
	ft_putstr_fd("] [file ...]", 2);
	ft_putchar_fd('\n', 2);
	return (RET_OK);
}

t_result	write_illegal_param(char s)
{
	ft_putstr_fd("ls: illegal option -- ", 2);
	ft_putchar_fd(s, 2);
	ft_putchar_fd('\n', 2);
	return (RET_OK);
}

t_result	write_no_such_file(char *s)
{
	ft_putstr_fd("ls: ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd(": No such file or directory", 2);
	ft_putchar_fd('\n', 2);
	return (RET_OK);
}

t_result	write_perm_denied(char *s)
{
	ft_putstr_fd("ls: ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd(": Permission denied", 2);
	ft_putchar_fd('\n', 2);
	return (RET_OK);
}
