/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 16:27:31 by eklompus          #+#    #+#             */
/*   Updated: 2019/09/26 18:26:24 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <dirent.h>
#include <sys/stat.h>

int stat(const char *restrict path, struct stat *restrict buf);

t_result	read_dir(char *name, t_uint flags)
{
	DIR *dir;
	struct dirent *dd;

	dir = opendir(name);
	if (dir == NULL)
		return (ERR_OPEN_DIR);
	while ((dd = readdir(dir)) != NULL)
	{

	}
	closedir(dir);
	return (RET_OK);
}