/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 10:27:18 by eklompus          #+#    #+#             */
/*   Updated: 2019/09/26 14:35:16 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
#define FT_LS_H

#include "libft.h"

# define 	STR_CURRENT_DIR		"."
# define	LEGAL_OPTIONS		"Ralrt"


typedef int 			t_result;

typedef unsigned int	t_uint;

#define		RET_OK				(0)
#define		ERR_ENOMEM			(-1)
#define		ERR_ILLEGAL_ARGS	(-2)

#define 	F_LONG_FORMAT	(1u << 0)
#define		F_RECURSIVE		(1u << 1)
#define		F_INCLUDE_DIR	(1u << 2)
#define		F_REVERSE		(1u << 3)
#define		F_SORTTIME		(1u << 4)
#define		F_SORTATIME		(1u << 5)
#define 	F_NOT_SORTED	(1u << 6)
#define		F_GROUP_NAME	(1u << 7)
#define		F_DIR_LIKE_FILE	(1u << 8)
#define		F_COLORISED		(1u << 9)
#define		F_ERROR			(0xFFFFFFFF)

typedef struct	s_flist
{
	struct s_flist	*prev;
	struct s_flist	*next;
	struct s_flist	*child;
	char			*name;
}				t_flist;

t_flist			*add_to_flist(t_flist **flist, char	*name);
t_result		parse_args(t_list **root, int ac, char *av[], t_uint *flags);

#endif
