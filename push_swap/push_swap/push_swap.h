/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 10:55:57 by eklompus          #+#    #+#             */
/*   Updated: 2019/09/23 10:55:57 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#include "../common/common.h"
#include "../libft/libft.h"

typedef struct	s_bfs
{
	char			operation;
	struct s_bfs	*children;
}				t_bfs;
#endif
