/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 16:27:31 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/07 14:16:08 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <dirent.h>
#include <sys/stat.h>

static t_result	read_one_file(t_lsdata *lsd, t_list **root, char *path,
	struct dirent *dd)
{
	t_list			*lst;
	t_fentry		*ffentry;
	size_t			plen;

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
			break ;
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
	if (check_is_dir(fentry, lsd->flags) && !(lsd->flags & F_DIR_LIKE_FILE))
		ft_lstaddrevsorted(&lsd->dirs, lst, &(lsd->flags), cmp_callback);
	else
		ft_lstaddsorted(&lsd->files, lst, &(lsd->flags), cmp_callback);
	return (RET_OK);
}
