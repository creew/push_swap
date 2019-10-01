/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 10:27:18 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/01 17:15:03 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
#define FT_LS_H

#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include "libft.h"

# define	BUF_SIZE			42
# define 	STR_CURRENT_DIR		"."
# define	LEGAL_OPTIONS		"RalrtsguG"

#ifdef __linux__
#define DD_NAME_LEN(x)	(ft_strlen(x->d_name))
#elif __APPLE__
#define DD_NAME_LEN(x)	(x->d_namlen)
#endif

typedef int 			t_result;

typedef unsigned int	t_uint;
typedef unsigned short	t_ushort;
typedef unsigned char	t_uchar;

# define		RET_OK				(0)
# define		ERR_ENOMEM			(-1)
# define		ERR_ILLEGAL_ARGS	(-2)
# define		ERR_OPEN_DIR		(-3)
# define		ERR_STAT			(-4)

# define		F_LONG_FORMAT	(1u << 0u)
# define		F_RECURSIVE		(1u << 1u)
# define		F_INCLUDE_DIR	(1u << 2u)
# define		F_REVERSE		(1u << 3u)
# define		F_SORTTIME		(1u << 4u)
# define		F_SORTATIME		(1u << 5u)
# define		F_NOT_SORTED	(1u << 6u)
# define		F_GROUP_NAME	(1u << 7u)
# define		F_DIR_LIKE_FILE	(1u << 8u)
# define		F_COLORISED		(1u << 9u)
# define		F_SHOWBLCKSZ	(1u << 10u)
# define		F_ERROR			(0xFFFFFFFF)


# define		ANSI_CTL	(27)
# define		ANSI_RESET	"[0m"
# define		ANSI_BLACK	"[30m"
# define		ANSI_RED 	"[31m"
# define		ANSI_GREEN	"[32m"
# define		ANSI_YELLOW	"[33m"
# define		ANSI_BLUE	"[34m"
# define		ANSI_PURPLE	"[35m"
# define		ANSI_CYAN	"[36m"
# define		ANSI_WHITE	"[37m"


typedef struct	s_fttime
{
	t_ushort	year;
	t_uchar		month;
	t_uchar		day;
	t_uchar		hour;
	t_uchar		minute;
	t_uchar 	sec;
}				t_fttime;

typedef struct	s_maxvals
{
	t_uint 		name;
	t_uint		blocks;
	t_uint 		links;
	t_uint 		owner;
	t_uint 		group;
	t_uint		size;
}				t_maxvals;

typedef	struct	s_fentry
{
	char		name[1024];
	struct stat	fs;
	t_fttime	time;
	t_list		*child;
}				t_fentry;

typedef struct	s_lsdata
{
	char		bufout[BUF_SIZE];
	t_uint		bufpos;

	t_fttime	ftime;
	t_uint		termwidth;
	t_list		*files;
	t_list		*dirs;
	t_uint		flags;
}				t_lsdata;

extern 			const char *g_months[12];

t_result		parse_args(t_lsdata *lsdata, int ac, char *av[]);
t_result		add_param(t_lsdata *lsd, char *name);

size_t			set_path(char *path);
t_uint			get_uint_width(t_uint num);
t_uint			get_uid_length(uid_t uid);
t_uint			get_gid_length(gid_t gid);
t_result		parse_time(time_t time, t_fttime *fttime);

void			write_flush(t_lsdata *lsd);
void			write_cout(t_lsdata *lsd, char c);
void			write_out(t_lsdata *lsd, const char *str);
void			write_number(t_lsdata *lsd, t_uint n);
int				write_ansi(t_lsdata *lsd, char *color);

t_result		print_entry(t_lsdata * lsd, t_fentry *entry, unsigned int flags,
							t_maxvals *vals);
t_result		print_uint(t_lsdata *lsd, t_uint num, size_t width);
t_result		print_rights(t_lsdata *lsd, struct stat *fs);
t_result		print_str(t_lsdata *lsd, char *str, size_t width);
t_result		print_date(t_lsdata *lsd, time_t ti);
t_result		print_name(t_lsdata *lsd, t_fentry *entry);
#endif
