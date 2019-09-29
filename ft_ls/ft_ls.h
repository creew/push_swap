/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 10:27:18 by eklompus          #+#    #+#             */
/*   Updated: 2019/09/29 16:11:04 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
#define FT_LS_H

#include <sys/stat.h>
#include "libft.h"

# define 	STR_CURRENT_DIR		"."
# define	LEGAL_OPTIONS		"Ralrt"

#ifdef __linux__
#define DD_NAME_LEN(x)	(ft_strlen(x->d_name))
#elif __APPLE__
#define DD_NAME_LEN(x)	(x->d_namlen))
#endif
typedef int 			t_result;

typedef unsigned int	t_uint;

#define		RET_OK				(0)
#define		ERR_ENOMEM			(-1)
#define		ERR_ILLEGAL_ARGS	(-2)
#define		ERR_OPEN_DIR		(-3)
#define		ERR_STAT			(-4)

#define 	F_LONG_FORMAT	(1u << 0u)
#define		F_RECURSIVE		(1u << 1u)
#define		F_INCLUDE_DIR	(1u << 2u)
#define		F_REVERSE		(1u << 3u)
#define		F_SORTTIME		(1u << 4u)
#define		F_SORTATIME		(1u << 5u)
#define 	F_NOT_SORTED	(1u << 6u)
#define		F_GROUP_NAME	(1u << 7u)
#define		F_DIR_LIKE_FILE	(1u << 8u)
#define		F_COLORISED		(1u << 9u)
#define		F_SHOWBLCKSZ	(1u << 10u)
#define		F_ERROR			(0xFFFFFFFF)

typedef	struct	s_fentry
{
	char				name[1024];
	size_t 				name_len;
	struct stat			fs;
	t_list				*child;
}				t_fentry;

typedef struct	s_lsdata
{
	t_list		*files;
	t_list		*dirs;
	t_uint		flags;
}				t_lsdata;

t_result		parse_args(t_lsdata *lsdata, int ac, char *av[]);
t_result		add_param(t_lsdata *lsd, char *name);

size_t			set_path(char *path);
size_t			add_pathdir(char *path, const char *dir);
#endif
