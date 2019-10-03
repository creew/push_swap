/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_entry.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 10:38:00 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/03 13:16:06 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_result	print_uint_space(t_lsdata *lsd, t_uint val, size_t width)
{
	print_uint(lsd, val, width);
	write_cout(lsd, ' ');
}

static t_result	print_uid(t_lsdata *lsd, uid_t uid, size_t width, t_uint flag)
{
	struct passwd *pwd;

	pwd = 0;
	if (flag & F_LONG_FORMAT)
	{
		if (!(flag & F_ID_NUMBERS))
		{
			pwd = getpwuid(uid);
			if (pwd)
				print_str(lsd, pwd->pw_name, width);
		}
		if (!pwd)
		{
			print_uint(lsd, uid, width);
		}
	}
	return (RET_OK);
}

static t_result	print_gid(t_lsdata *lsd, gid_t gid, size_t width, t_uint flag)
{
	struct group	*grp;

	grp = 0;
	if (!(flag & F_ID_NUMBERS))
	{
		grp = getgrgid(gid);
		if (grp)
			print_str(lsd, grp->gr_name, width);
	}
	if (!grp)
	{
		print_uint(lsd, gid, width);
	}
	return (RET_OK);
}

t_result		print_entry(t_lsdata *lsd, t_fentry *entry, unsigned int flags,
	t_maxvals *vals)
{
	struct stat		*fs;

	fs = &entry->fs;
	if (!(flags & F_INCLUDE_DIR) && entry->name[0] == '.')
		return (RET_OK);
	if (flags & F_SHOWBLCKSZ)
		print_uint_space(lsd, fs->st_blocks, vals->blocks);
	print_rights(lsd, fs);
	print_uint(lsd, fs->st_nlink, vals->links + 1);
	print_uid(lsd, fs->st_uid, vals->owner + 1, flags);
	print_gid(lsd, fs->st_gid, vals->group + 2, flags);
	print_uint_space(lsd, fs->st_size, vals->size + 2);
	print_date(lsd, flags & F_SORTATIME ? entry->fs.ST_ATIME.tv_sec :
					entry->fs.ST_MTIME.tv_sec);
	write_cout(lsd, ' ');
	print_name(lsd, entry);
	write_cout(lsd, '\n');
	return (RET_OK);
}
