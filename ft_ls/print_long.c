/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_long_entry.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 12:06:21 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/09 12:06:23 by eklompus         ###   ########.fr       */
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

static void		print_inode(t_lsdata *lsd, __darwin_ino64_t ino, t_ulong max)
{
	print_ulong(lsd, ino, max, 0);
	write_cout(lsd, ' ');
}

static void		print_blocks(t_lsdata *lsd, blkcnt_t blks, t_ulong max)
{
	print_ulong(lsd, blks, max, 0);
	write_cout(lsd, ' ');
}

t_result		print_long_entry(t_lsdata *lsd, t_fentry *entry,
								unsigned int flags, t_maxvals *vals)
{
	struct stat		*fs;

	fs = &entry->fs;
	read_additional_param(entry);
	if (flags & F_INODES)
		print_inode(lsd, fs->st_ino, vals->inode);
	if (flags & F_SHOWBLCKSZ)
		print_blocks(lsd, fs->st_blocks, vals->blocks);
	print_rights(lsd, entry, fs);
	print_ulong(lsd, fs->st_nlink, vals->links, 0);
	write_cout(lsd, ' ');
	print_uid(lsd, fs->st_uid, vals->owner, flags);
	print_gid(lsd, fs->st_gid, vals->group, flags);
	print_size(lsd, entry, vals);
	write_cout(lsd, ' ');
	print_date(lsd, flags & F_SORTATIME ? entry->fs.ST_ATIME.tv_sec :
					entry->fs.ST_MTIME.tv_sec);
	write_cout(lsd, ' ');
	print_name(lsd, entry, 0);
	write_cout(lsd, '\n');
	return (RET_OK);
}
