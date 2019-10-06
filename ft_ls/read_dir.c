/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 16:27:31 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/06 18:51:53 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <dirent.h>
#include <sys/stat.h>

#ifdef __APPLE__

static t_result	read_additional_param(t_lsdata *lsd, t_fentry *entry,
										char *path)
{
	acl_t			acl;
	acl_entry_t		dummy;
	ssize_t			xattr;

	dummy = 0;
	if (lsd->flags & F_LONG_FORMAT)
	{
		acl = acl_get_link_np(path, ACL_TYPE_EXTENDED);
		if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &dummy) == -1)
		{
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

#endif

/*
 * TODO Make better recursive reading
 *
 */

static t_result	read_one_file(t_lsdata *lsd, t_list **root, char *path,
	struct dirent *dd)
{
	t_list			*lst;
	t_fentry		*ffentry;
	size_t 			plen;
	ssize_t			llen;
	char			tmp[FT_MAX_PATH + 1];

	if ((lst = ft_lstnewblank(sizeof(t_fentry) + sizeof(char) *
		(ft_strlen(path) + DD_NAME_LEN(dd) + 1))) == NULL)
		return (ERR_ENOMEM);
	ffentry = (t_fentry *)(lst->content);
	ft_strcpy(ffentry->path, path);
	plen = set_path(ffentry->path);
	ffentry->name = ffentry->path + plen;
	ft_strncpy(ffentry->path + plen, dd->d_name, DD_NAME_LEN(dd));
	if (lstat(ffentry->path, &ffentry->fs) < 0)
	{
		ft_lstdelone(&lst, dellst_callback);
		return (ERR_STAT);
	}
	if (lsd->flags & F_LONG_FORMAT)
	{
		read_additional_param(lsd, ffentry, ffentry->path);
		if (S_ISLNK(ffentry->fs.st_mode))
		{
			llen = readlink(ffentry->path, tmp, FT_MAX_PATH);
			if (llen != -1)
			{
				ffentry->link = ft_strnew(llen + 1);
				if (ffentry->link)
					ft_strncpy(ffentry->link, tmp, llen);
			}
		}
	}
	ft_lstaddsorted(root, lst, &(lsd->flags), cmp_callback);
	return (RET_OK);
}

t_result		read_dir(t_lsdata *lsd, t_list **root, char *path)
{
	DIR				*dir;
	struct dirent	*dd;
	t_result		ret;

	dir = opendir(path);
	if (dir == NULL)
		return (ERR_OPEN_DIR);
	ret = RET_OK;
	while ((dd = readdir(dir)) != NULL)
	{
		if ((ret = read_one_file(lsd, root, path, dd)) != RET_OK)
			break;
	}
	closedir(dir);
	return (ret);
}

t_result		add_param(t_lsdata *lsd, char *name)
{
	t_list		*lst;
	t_fentry	*fentry;

	if ((lst = ft_lstnewblank(
		sizeof(t_fentry) + sizeof(char) * (ft_strlen(name) + 1))) == NULL)
		return (ERR_ENOMEM);
	fentry = (t_fentry *)(lst->content);
	if (lstat(name, &fentry->fs) != 0)
	{
		ft_lstdelone(&lst, dellst_callback);
		return (ERR_STAT);
	}
	ft_strcpy(fentry->path, name);
	fentry->name = fentry->path;
	if (S_ISDIR(fentry->fs.st_mode) && !(lsd->flags & F_DIR_LIKE_FILE))
		ft_lstaddsorted(&lsd->dirs, lst, &(lsd->flags), cmp_callback);
	else
		ft_lstaddsorted(&lsd->files, lst, &(lsd->flags), cmp_callback);
	return (RET_OK);
}
