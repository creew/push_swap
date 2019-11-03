/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_stacks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 12:33:49 by eklompus          #+#    #+#             */
/*   Updated: 2019/11/03 12:33:49 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "ft_printf.h"

static void	print_delim(void)
{
	ft_printf("{red}-------------------------------------{eoc}\n");
}

static void	print_end(void)
{
	ft_printf("{red}|{eoc}\n");
}

static void	print_str(char *str)
{
	ft_printf("{red}|{eoc}   {blue}%-14s{eoc}", str);
}

static void	print_val(int val)
{
	ft_printf("{red}|{eoc}   {blue}%-14d{eoc}", val);
}

void		print_stacks(t_stack *st1, t_stack *st2)
{
	size_t	size1;
	size_t	size2;

	print_delim();
	print_str("stack A");
	print_str("stack B");
	print_end();
	print_delim();
	size1 = st1->pos;
	size2 = st2->pos;
	if (size1 || size2)
	{
		while (size1 || size2)
		{
			size1 ? print_val(st1->stack[--size1]) : print_str("");
			size2 ? print_val(st2->stack[--size2]) : print_str("");
			print_end();
		}
		print_delim();
	}
}
