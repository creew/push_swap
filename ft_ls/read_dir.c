/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 16:27:31 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/03 19:31:09 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <dirent.h>
#include <sys/stat.h>

static t_result	read_additional_param(t_lsdata *lsd, t_fentry *entry, char *path)
{
	acl_t			acl;
	acl_entry_t		dummy;
	ssize_t			xattr;

	dummy = 0;
	if (lsd->flags & F_LONG_FORMAT)
	{
		acl = acl_get_link_np(path, ACL_TYPE_EXTENDED);
		if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &dummy) == -1) {
			acl_free(acl);
			acl = NULL;
		}
		xattr = listxattr(path, NULL, 0, XATTR_NOFOLLOW);
		if (xattr < 0)
			xattr = 0;
		if (xattr > 0)
			entry->xattr = XATTR_ATTR;
		else if (acl != NULL)
			entry->xattr = XATTR_ACL;
		acl_free(acl);
	}
	return (RET_OK);
}

static int		f_cmp(t_list *l1, t_list *l2, void *param)
{
	t_fentry	*f1;
	t_fentry	*f2;
	t_uint		flags;
	long		res;

	flags = *(t_uint *)(param);
	f1 = (t_fentry *)(l1->content);
	f2 = (t_fentry *)(l2->content);
	res = 0;
	if (flags & F_NOT_SORTED)
		return (0);
	if (flags & F_SORTSIZE)
		res = f2->fs.st_size - f1->fs.st_size;
	else if (flags & F_SORTTIME)
	{
		if (flags & F_SORTATIME)
			res = f2->fs.st_atimespec.tv_sec - f1->fs.st_atimespec.tv_sec;
		else
			res = f2->fs.st_mtimespec.tv_sec - f1->fs.st_mtimespec.tv_sec;
	}
	if (res == 0)
		res = ft_strcmp(f1->name, f2->name);
	return ((int)(flags & F_REVERSE ? -res : res));
}

/* TODO Make better recursive reading */
t_result		read_dir(t_lsdata *lsd, t_fentry *parent, char *path)
{
	DIR				*dir;
	struct dirent	*dd;
	t_list			*lst;
	t_fentry		*ffentry;
	size_t			plen;

	plen = set_path(path);
	dir = opendir(path);
	if (dir == NULL)
		return (ERR_OPEN_DIR);
	while ((dd = readdir(dir)) != NULL)
	{
		if ((lst = ft_lstnewblank(sizeof(t_fentry))) == NULL)
			return (ERR_ENOMEM);
		ffentry = (t_fentry *)(lst->content);
		ft_strncpy(ffentry->name, dd->d_name, DD_NAME_LEN(dd));
		ft_strcpy(path + plen, ffentry->name);
		if (lstat(path, &ffentry->fs) < 0)
			return (ERR_STAT);
		read_additional_param(lsd, ffentry, path);
		if (S_ISLNK(ffentry->fs.st_mode))
		{
			ffentry->link = ft_strnew(FT_MAX_PATH);
			readlink(path, ffentry->link, FT_MAX_PATH);
		}
		if (S_ISDIR(ffentry->fs.st_mode) && lsd->flags & F_RECURSIVE &&
			ft_strcmp(ffentry->name, ".") && ft_strcmp(ffentry->name, ".."))
			read_dir(lsd, ffentry, path);
		ft_lstaddsorted(&parent->child, lst, &(lsd->flags), f_cmp);
	}
	closedir(dir);
	path[plen] = '\0';
	return (RET_OK);
}

t_result		add_param(t_lsdata *lsd, char *name)
{
	t_list		*lst;
	t_fentry	*fentry;
	char		path[1024];

	if ((lst = ft_lstnewblank(sizeof(t_fentry))) == NULL)
		return (ERR_ENOMEM);
	fentry = (t_fentry *)(lst->content);
	if (lstat(name, &fentry->fs) != 0)
		return (ERR_STAT);
	ft_strcpy(fentry->name, name);
	if (S_ISDIR(fentry->fs.st_mode))
	{
		ft_strcpy(path, name);
		read_dir(lsd, fentry, path);
		ft_lstaddsorted(&lsd->dirs, lst, &(lsd->flags), f_cmp);
	}
	else
	{
		ft_lstaddsorted(&lsd->files, lst, &(lsd->flags), f_cmp);
	}
	return (RET_OK);
}
