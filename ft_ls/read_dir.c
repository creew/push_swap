/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 16:27:31 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/03 17:35:46 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <dirent.h>
#include <sys/stat.h>

static int	f_cmp(t_list *l1, t_list *l2, void *param)
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

t_result	read_dir(t_lsdata *lsd, t_fentry *parent, char *path)
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
		if (stat(path, &ffentry->fs) < 0)
			return (ERR_STAT);
		if (S_ISDIR(ffentry->fs.st_mode) && lsd->flags & F_RECURSIVE &&
			ft_strcmp(ffentry->name, ".") && ft_strcmp(ffentry->name, ".."))
			read_dir(lsd, ffentry, path);
		ft_lstaddsorted(&parent->child, lst, &(lsd->flags), f_cmp);
	}
	closedir(dir);
	path[plen] = '\0';
	return (RET_OK);
}

t_result	add_param(t_lsdata *lsd, char *name)
{
	t_list		*lst;
	t_fentry	*fentry;
	char		path[1024];

	if ((lst = ft_lstnewblank(sizeof(t_fentry))) == NULL)
		return (ERR_ENOMEM);
	fentry = (t_fentry *)(lst->content);
	if (stat(name, &fentry->fs) != 0)
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
