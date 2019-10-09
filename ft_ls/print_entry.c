/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_entry.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 10:38:00 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/07 16:40:08 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_result	print_uid(t_lsdata *lsd, uid_t uid, size_t width, t_uint flag)
{
	struct passwd *pwd;

	pwd = 0;
	if (!(flag & F_GROUP_NAME))
	{
		if (!(flag & F_ID_NUMBERS))
		{
			pwd = getpwuid(uid);
			if (pwd)
				print_str(lsd, pwd->pw_name, width, 1);
		}
		if (!pwd)
			print_ulong(lsd, uid, width, 0);
		write_cout(lsd, ' ');
		write_cout(lsd, ' ');
	}
	return (RET_OK);
}

t_result	print_gid(t_lsdata *lsd, gid_t gid, size_t width, t_uint flag)
{
	struct group	*grp;

	grp = 0;
	if (!(flag & F_ID_NUMBERS))
	{
		grp = getgrgid(gid);
		if (grp)
			print_str(lsd, grp->gr_name, width, 1);
	}
	if (!grp)
		print_ulong(lsd, gid, width, 1);
	write_cout(lsd, ' ');
	write_cout(lsd, ' ');
	return (RET_OK);
}

t_result	print_link(t_lsdata *lsd, t_fentry *entry)
{
	char		link[FT_MAX_PATH + 1];
	ssize_t		llen;

	if ((lsd->flags & F_LONG_FORMAT) && (S_ISLNK(entry->fs.st_mode)))
	{
		llen = readlink(entry->path, link, FT_MAX_PATH);
		if (llen != -1)
		{
			link[llen] = '\0';
			write_out(lsd, " -> ");
			write_out(lsd, link);
		}
	}
	return (RET_OK);
}

t_result	print_size(t_lsdata *lsd, t_fentry *entry, t_maxvals *vals)
{
	if (S_ISCHR(entry->fs.st_mode) || S_ISBLK(entry->fs.st_mode))
	{
		print_ulong(lsd, major(entry->fs.st_rdev),
			vals->size - vals->minor - 2, 0);
		write_cout(lsd, ',');
		print_ulong(lsd, minor(entry->fs.st_rdev),
					vals->size - vals->major - 2, 0);
	}
	else
	{
		print_ulong(lsd, entry->fs.st_size, vals->size, 0);
	}
	return (RET_OK);
}
