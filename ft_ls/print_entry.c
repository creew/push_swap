/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_entry.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 10:38:00 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/01 17:43:24 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_result		print_entry(t_lsdata *lsd, t_fentry *entry, unsigned int flags,
	t_maxvals *vals)
{
	struct stat		*fs;
	struct passwd	*pwd;
	struct group	*grp;

	fs = &entry->fs;
	if (!(flags & F_INCLUDE_DIR) && entry->name[0] == '.')
		return (RET_OK);
	if (flags & F_LONG_FORMAT || flags & F_GROUP_NAME)
	{
		if (flags & F_SHOWBLCKSZ)
		{
			print_uint(lsd, entry->fs.st_blocks, vals->blocks);
			write_cout(lsd, ' ');
		}
		print_rights(lsd, fs);
		print_uint(lsd, fs->st_nlink, vals->links + 1);
		if (flags & F_LONG_FORMAT)
		{
			pwd = getpwuid(fs->st_uid);
			if (pwd)
				print_str(lsd, pwd->pw_name, vals->owner + 1);
		}
		grp = getgrgid(fs->st_gid);
		if (grp)
			print_str(lsd, grp->gr_name, vals->group + 2);
		print_uint(lsd, fs->st_size, vals->size + 2);
		write_cout(lsd, ' ');
		print_date(lsd, flags & F_SORTATIME ? entry->fs.ST_ATIME.tv_sec :
					entry->fs.ST_MTIME.tv_sec);
		write_cout(lsd, ' ');
		print_name(lsd, entry);
		write_cout(lsd, '\n');
	}
	return (RET_OK);
}
