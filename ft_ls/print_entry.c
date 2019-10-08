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

#ifdef __APPLE__

static t_result	read_additional_param(t_fentry *entry)
{
	acl_t			acl;
	acl_entry_t		dummy;
	ssize_t			xattr;

	dummy = 0;
	acl = acl_get_link_np(entry->path, ACL_TYPE_EXTENDED);
	if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &dummy) == -1)
	{
		acl_free(acl);
		acl = NULL;
	}
	xattr = listxattr(entry->path, NULL, 0, XATTR_NOFOLLOW);
	if (xattr < 0)
		xattr = 0;
	if (xattr > 0)
		entry->xattr = XATTR_ATTR;
	else if (acl != NULL)
		entry->xattr = XATTR_ACL;
	acl_free(acl);
	return (RET_OK);
}

#endif

static t_result	print_uid(t_lsdata *lsd, uid_t uid, size_t width, t_uint flag)
{
	struct passwd *pwd;

	pwd = 0;
	if (!(flag & F_GROUP_NAME))
	{
		if (!(flag & F_ID_NUMBERS))
		{
			pwd = getpwuid(uid);
			if (pwd)
				print_str(lsd, pwd->pw_name, width, 0);
		}
		if (!pwd)
			print_uint(lsd, uid, width, 0);
		write_cout(lsd, ' ');
		write_cout(lsd, ' ');
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
			print_str(lsd, grp->gr_name, width, 1);
	}
	if (!grp)
		print_uint(lsd, gid, width, 1);
	write_cout(lsd, ' ');
	write_cout(lsd, ' ');
	return (RET_OK);
}

t_result		print_link(t_lsdata *lsd, t_fentry *entry)
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

t_result		print_long_entry(t_lsdata *lsd, t_fentry *entry, unsigned int flags,
	t_maxvals *vals)
{
	struct stat		*fs;

	fs = &entry->fs;
	if (!(flags & F_INCLUDE_DIR) && entry->name[0] == '.')
		return (RET_OK);
	read_additional_param(entry);
	if (flags & F_SHOWBLCKSZ)
	{
		print_uint(lsd, fs->st_blocks, vals->blocks, 0);
		write_cout(lsd, ' ');
	}
	print_rights(lsd, entry, fs);
	print_uint(lsd, fs->st_nlink, vals->links, 0);
	write_cout(lsd, ' ');
	print_uid(lsd, fs->st_uid, vals->owner, flags);
	print_gid(lsd, fs->st_gid, vals->group, flags);
	print_uint(lsd, fs->st_size, vals->size, 0);
	write_cout(lsd, ' ');
	print_date(lsd, flags & F_SORTATIME ? entry->fs.ST_ATIME.tv_sec :
					entry->fs.ST_MTIME.tv_sec);
	write_cout(lsd, ' ');
	print_name(lsd, entry, 0);
	write_cout(lsd, '\n');
	return (RET_OK);
}
