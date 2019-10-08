/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 10:27:18 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/07 16:40:08 by eklompus         ###   ########.fr       */
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
# ifdef __APPLE__
#  include <sys/acl.h>
# endif
# include <sys/xattr.h>
# include "libft.h"

# define BUF_SIZE			1024
# define FT_MAX_PATH		1024
# define STR_CURRENT_DIR	"."
# define LEGAL_OPTIONS		"RalrtsguGnfS1d"

# ifdef __linux__
#  define DD_NAME_LEN(x)	(ft_strlen(x->d_name))
#  define ST_ATIME			st_atim
#  define ST_MTIME			st_mtim
#  define read_additional_param(...)
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
# define F_ONECOLUMN		(1u << 13u)
# define F_ERROR			(0xFFFFFFFF)

# define XATTR_ATTR			(1u)
# define XATTR_ACL			(2u)

# define ANSI_RESET			"\e[0m"
# define ANSI_BLACK			"\e[30m"
# define ANSI_RED			"\e[31m"
# define ANSI_GREEN			"\e[32m"
# define ANSI_YELLOW		"\e[33m"
# define ANSI_BLUE			"\e[34m"
# define ANSI_PURPLE		"\e[35m"
# define ANSI_CYAN			"\e[36m"
# define ANSI_WHITE			"\e[37m"

# define ANSI_BG_GREEN		"\e[42m"
# define ANSI_BG_YELLOW		"\e[43m"

typedef struct	s_fttime
{
	t_ushort	year;
	t_uchar		month;
	t_uchar		day;
	t_uchar		hour;
	t_uchar		minute;
}				t_fttime;

typedef struct	s_maxvals
{
	t_uint		name;
	t_uint		blocks;
	t_uint		links;
	t_uint		owner;
	t_uint		group;
	t_uint		size;
	t_uint		total_blocks;
}				t_maxvals;

typedef	struct	s_smaxvals
{
	t_uint		name;
	t_uint		blocks;
	t_uint		maxw;
	t_uint		col;
	t_uint		row;
}				t_smaxvals;

typedef	struct	s_fentry
{
	t_uchar		xattr;
	struct stat	fs;
	char		*name;
	char		path[1];
}				t_fentry;

typedef struct	s_lsdata
{
	char		bufout[BUF_SIZE];
	t_uint		bufpos;

	int			err;
	int			argcount;
	int			dircount;
	t_ftstack	stack;
	time_t		ctime;
	t_uint		termwidth;
	t_list		*files;
	t_list		*dirs;
	t_uint		flags;
}				t_lsdata;

extern			const char *g_months[12];

t_result		parse_args(t_lsdata *lsdata, int ac, char *av[]);
t_result		add_param(t_lsdata *lsd, char *name);

size_t			set_path(char *path);
t_uint			get_uint_width(t_uint num);
t_uint			get_uid_length(uid_t uid, t_uint flags);
t_uint			get_gid_length(gid_t gid, t_uint flags);
t_uint			get_str_length(char *str);

t_result		parse_time(time_t time, t_fttime *fttime);
int				date_cmp_6month(time_t ttf, time_t ttc);

void			write_flush(t_lsdata *lsd);
int				write_cout(t_lsdata *lsd, char c);
int				write_out(t_lsdata *lsd, const char *str);
void			write_number(t_lsdata *lsd, t_uint n);

t_result		print_long_entry(t_lsdata *lsd, t_fentry *entry,
									unsigned int flags, t_maxvals *vals);
t_result		print_uint(t_lsdata *lsd, t_uint num, size_t width, int right);
t_result		print_rights(t_lsdata *lsd, t_fentry *entry, struct stat *fs);
t_result		print_str(t_lsdata *lsd, char *str, size_t width, int right);
t_result		print_date(t_lsdata *lsd, time_t ti);
t_result		print_name(t_lsdata *lsd, t_fentry *entry, size_t width);

t_result		print_link(t_lsdata *lsd, t_fentry *entry);

void			print_short(t_lsdata *lsd, t_list *lst, int is_files);

t_result		read_dir(t_lsdata *lsd, t_list **root, char *path);
void			printlst(t_lsdata *lsd, t_list *lst, int is_files);

int				cmp_callback(t_list *l1, t_list *l2, void *param);
void			dellst_callback(void *data, size_t content_size);

int				is_notadir(const char *name);
void			print_dir_lst(t_lsdata *lsd, t_list *lst);

t_result		write_usage(void);
t_result		write_illegal_param(char s);
t_result		write_no_such_file(char *s);
t_result		write_perm_denied(char *s);

int				write_out_total(t_lsdata *lsd, t_uint blocks);
int				write_out_path(t_lsdata *lsd, char *path);
t_list			*create_copy_tlist(t_list *lst);

int				is_showed_entry(t_fentry *entry, t_uint flags);
void			get_maxvals(t_list *lst, t_maxvals *vals, t_uint flags);
void			get_smaxvals(t_list *lst, t_smaxvals *vals, t_uint flags);
size_t			get_lst_real_size(t_list *lst, t_uint flags);
t_list			*get_list_by_index(t_list *lst, t_uint flags, int index);
#endif
