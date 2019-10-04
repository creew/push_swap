/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 10:27:18 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/04 19:03:28 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/acl.h>
# include <sys/xattr.h>
# include "libft.h"

# define BUF_SIZE			128
# define FT_MAX_PATH		1024
# define STR_CURRENT_DIR	"."
# define LEGAL_OPTIONS		"RalrtsguGnfS"

# ifdef __linux__
#  define DD_NAME_LEN(x)	(ft_strlen(x->d_name))
#  define ST_ATIME			st_atim
#  define ST_MTIME			st_mtim
# elif __APPLE__
#  define DD_NAME_LEN(x)	(x->d_namlen)
#  define ST_ATIME			st_atimespec
#  define ST_MTIME			st_mtimespec
# endif

typedef int				t_result;

typedef unsigned int	t_uint;
typedef unsigned short	t_ushort;
typedef unsigned char	t_uchar;

# define RET_OK				(0)
# define ERR_ENOMEM			(-1)
# define ERR_ILLEGAL_ARGS	(-2)
# define ERR_OPEN_DIR		(-3)
# define ERR_STAT			(-4)
# define STACK_IS_EMPTY		(-5)

# define F_LONG_FORMAT		(1u << 0u)
# define F_RECURSIVE		(1u << 1u)
# define F_INCLUDE_DIR		(1u << 2u)
# define F_REVERSE			(1u << 3u)
# define F_SORTTIME			(1u << 4u)
# define F_SORTATIME		(1u << 5u)
# define F_NOT_SORTED		(1u << 6u)
# define F_GROUP_NAME		(1u << 7u)
# define F_DIR_LIKE_FILE	(1u << 8u)
# define F_COLORISED		(1u << 9u)
# define F_SHOWBLCKSZ		(1u << 10u)
# define F_ID_NUMBERS		(1u << 11u)
# define F_SORTSIZE			(1u << 12u)
# define F_ERROR			(0xFFFFFFFF)

# define XATTR_ATTR		(1u)
# define XATTR_ACL		(2u)

# define ANSI_RESET		"\e[0m"
# define ANSI_BLACK		"\e[30m"
# define ANSI_RED		"\e[31m"
# define ANSI_GREEN		"\e[32m"
# define ANSI_YELLOW	"\e[33m"
# define ANSI_BLUE		"\e[34m"
# define ANSI_PURPLE	"\e[35m"
# define ANSI_CYAN		"\e[36m"
# define ANSI_WHITE		"\e[37m"

# define ANSI_BG_GREEN	"\e[42m"
# define ANSI_BG_YELLOW	"\e[43m"

typedef struct	s_fttime
{
	t_ushort	year;
	t_uchar		month;
	t_uchar		day;
	t_uchar		hour;
	t_uchar		minute;
	t_uchar		sec;
}				t_fttime;

typedef struct	s_maxvals
{
	t_uint		name;
	t_uint		blocks;
	t_uint		links;
	t_uint		owner;
	t_uint		group;
	t_uint		size;
}				t_maxvals;

typedef	struct	s_fentry
{
	char		*link;
	t_uchar		xattr;
	struct stat	fs;
	t_fttime	time;
	t_list		*child;
	char		path[1];
}				t_fentry;

typedef struct	s_lsdata
{
	char		bufout[BUF_SIZE];
	t_uint		bufpos;

	char 		**rstack;
	size_t		ssize;
	size_t		sspos;

	t_fttime	ftime;
	time_t		ctime;
	t_uint		termwidth;
	t_list		*files;
	t_list		*dirs;
	t_uint		flags;
}				t_lsdata;

extern			const char *g_months[12];

t_result		parse_args(t_lsdata *lsdata, int ac, char *av[]);
t_result		add_param(t_lsdata *lsd, char *name);
void			delone(void *data, size_t content_size);

size_t			set_path(char *path);
t_uint			get_uint_width(t_uint num);
t_uint			get_uid_length(uid_t uid, t_uint flags);
t_uint			get_gid_length(gid_t gid, t_uint flags);
t_result		parse_time(time_t time, t_fttime *fttime);

void			write_flush(t_lsdata *lsd);
void			write_cout(t_lsdata *lsd, char c);
int				write_out(t_lsdata *lsd, const char *str);
void			write_number(t_lsdata *lsd, t_uint n);

t_result		print_entry(t_lsdata *lsd, t_fentry *entry, unsigned int flags,
							t_maxvals *vals);
t_result		print_uint(t_lsdata *lsd, t_uint num, size_t width, int right);
t_result		print_rights(t_lsdata *lsd, t_fentry *entry,  struct stat *fs);
t_result		print_str(t_lsdata *lsd, char *str, size_t width, int right);
t_result		print_date(t_lsdata *lsd, time_t ti);
t_result		print_name(t_lsdata *lsd, t_fentry *entry);

void			printlst(t_lsdata *lsd, t_list *lst);
#endif
