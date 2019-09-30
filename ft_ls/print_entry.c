/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_entry.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 10:38:00 by eklompus          #+#    #+#             */
/*   Updated: 2019/09/30 15:02:47 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_result	print_uint(t_lsdata *lsd, t_uint num, size_t width)
{
	t_uint size;

	size = get_uint_width(num);
	while (size < width)
	{
		write_cout(lsd, ' ');
		size++;
	}
	write_number(lsd, num);
	return (RET_OK);
}

static t_result	print_rights(t_lsdata *lsd, struct stat *fs, size_t width)
{
	if (S_ISLNK(fs->st_mode))
		write_cout(lsd, 'l');
	else if (S_ISDIR(fs->st_mode))
		write_cout(lsd, 'd');
	else
		write_cout(lsd, '-');

	write_cout(lsd, fs->st_mode & S_IRUSR ? 'r' : '-' );
	write_cout(lsd, fs->st_mode & S_IWUSR ? 'w' : '-' );
	write_cout(lsd, fs->st_mode & S_IXUSR ? 'x' : '-' );

	write_cout(lsd, fs->st_mode & S_IRGRP ? 'r' : '-' );
	write_cout(lsd, fs->st_mode & S_IWGRP ? 'w' : '-' );
	write_cout(lsd, fs->st_mode & S_IXGRP ? 'x' : '-' );

	write_cout(lsd, fs->st_mode & S_IROTH ? 'r' : '-' );
	write_cout(lsd, fs->st_mode & S_IWOTH ? 'w' : '-' );
	write_cout(lsd, fs->st_mode & S_IXOTH ? 'x' : '-' );
	return (RET_OK);
}

static t_result	print_str(t_lsdata *lsd, char *str, size_t width)
{
	t_uint size;

	size = ft_strlen(str);
	while (size < width)
	{
		write_cout(lsd, ' ');
		size++;
	}
	write_out(lsd, str);
	return (RET_OK);
}

t_result		print_entry(t_lsdata * lsd, t_fentry *entry, unsigned int flags)
{
	struct stat *fs;
	struct passwd *pwd;
	struct group *grp;

	fs = &entry->fs;
	if (!(flags & F_INCLUDE_DIR) && entry->name[0] == '.')
		return (RET_OK);
	if (flags & F_LONG_FORMAT || flags & F_GROUP_NAME)
	{
		print_rights(lsd, fs, 12);
		print_uint(lsd, fs->st_nlink, 5);
		pwd = getpwuid(fs->st_uid);
		if (pwd)
			print_str(lsd, pwd->pw_name, 10);
		grp = getgrgid(fs->st_gid);
		if (grp)
			print_str(lsd, grp->gr_name, 10);
		print_uint(lsd, fs->st_size, 10);
		write_out(lsd, entry->name);
		write_cout(lsd, '\n');
	}
	return (RET_OK);
}