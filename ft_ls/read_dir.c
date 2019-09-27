/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 16:27:31 by eklompus          #+#    #+#             */
/*   Updated: 2019/09/27 11:35:37 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <dirent.h>
#include <sys/stat.h>

t_result	read_dir(char *name, t_uint flags)
{
	DIR				*dir;
	struct dirent	*dd;

	dir = opendir(name);
	if (dir == NULL)
		return (ERR_OPEN_DIR);
	while ((dd = readdir(dir)) != NULL)
	{

	}
	closedir(dir);
	return (RET_OK);
}

static int	f_cmp(t_list *l1, t_list *l2, void *param)
{
	t_fentry	*f1;
	t_fentry	*f2;
	t_uint		flags;

	flags = *(t_uint *)(param);
	f1 = (t_fentry *)(l1->content);
	f2 = (t_fentry *)(l2->content);
	return (ft_strcmp(f1->name, f2->name));
}

t_result	add_param(t_lsdata *lsd, char *name)
{
	t_list		*lst;
	t_fentry	*fentry;

	if ((lst = ft_lstnewblank(sizeof(t_fentry))) == NULL)
		return (ERR_ENOMEM);
	fentry = (t_fentry *)(lst->content);
	if (stat(name, &fentry->fs) != 0)
		return (ERR_STAT);
	strcpy(fentry->name, name);
	if (S_ISDIR(fentry->fs.st_mode))
	{
		ft_lstaddsorted(&lsd->dirs, lst, &(lsd->flags), f_cmp);
	}
	else
	{
		ft_lstaddsorted(&lsd->files, lst, &(lsd->flags), f_cmp);
	}
	return (RET_OK);
}