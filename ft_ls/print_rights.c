/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_rights.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 11:38:22 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/03 16:30:31 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_result	print_other_perm(t_lsdata *lsd, mode_t st, mode_t x)
{
	if (st)
		write_cout(lsd, x ? 't' : 'T');
	else
		write_cout(lsd, x ? 'x' : '-');
	return (RET_OK);
}

static t_result	print_owngrp_perm(t_lsdata *lsd, mode_t id, mode_t x)
{
	if (id)
		write_cout(lsd, x ? 's' : 'S');
	else
		write_cout(lsd, x ? 'x' : '-');
	return (RET_OK);
}

static t_result	print_filetype(t_lsdata *lsd, mode_t mode)
{
	if (S_ISBLK(mode))
		write_cout(lsd, 'b');
	else if (S_ISCHR(mode))
		write_cout(lsd, 'c');
	else if (S_ISDIR(mode))
		write_cout(lsd, 'd');
	else if (S_ISLNK(mode))
		write_cout(lsd, 'l');
	else if (S_ISSOCK(mode))
		write_cout(lsd, 's');
	else if (S_ISFIFO(mode))
		write_cout(lsd, 'p');
	else if (S_ISREG(mode))
		write_cout(lsd, '-');
	else
		write_cout(lsd, '?');
	return (RET_OK);
}

t_result		print_rights(t_lsdata *lsd, t_fentry *entry, struct stat *fs)
{
	print_filetype(lsd, fs->st_mode);
	write_cout(lsd, fs->st_mode & S_IRUSR ? 'r' : '-');
	write_cout(lsd, fs->st_mode & S_IWUSR ? 'w' : '-');
	print_owngrp_perm(lsd, fs->st_mode & S_ISUID, fs->st_mode & S_IXUSR);
	write_cout(lsd, fs->st_mode & S_IRGRP ? 'r' : '-');
	write_cout(lsd, fs->st_mode & S_IWGRP ? 'w' : '-');
	print_owngrp_perm(lsd, fs->st_mode & S_ISGID, fs->st_mode & S_IXOTH);
	write_cout(lsd, fs->st_mode & S_IROTH ? 'r' : '-');
	write_cout(lsd, fs->st_mode & S_IWOTH ? 'w' : '-');
	print_other_perm(lsd, fs->st_mode & S_ISVTX, fs->st_mode & S_IXOTH);
	if (entry->xattr == XATTR_ATTR)
		write_cout(lsd, '@');
	else if (entry->xattr == XATTR_ACL)
		write_cout(lsd, '+');
	else
		write_cout(lsd, ' ');
	write_cout(lsd, ' ');
	return (RET_OK);
}
