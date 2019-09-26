/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 10:27:18 by eklompus          #+#    #+#             */
/*   Updated: 2019/09/26 11:35:36 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
#define FT_LS_H

#include "libft.h"

typedef struct	s_flist
{

	struct s_flist	*prev;
	struct s_flist	*next;
	struct s_flist	*child;
	char			*name;
}				t_flist;

#endif
