/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 18:03:23 by eklompus          #+#    #+#             */
/*   Updated: 2019/09/30 18:38:30 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

const char *g_months[12] =
	{
		"Jan",
		"Feb",
		"Mar",
		"Apr",
		"May",
		"Jun",
		"Jul",
		"Aug",
		"Sep",
		"Oct",
		"Nov",
		"Dec"
	};

t_result	print_uint(t_lsdata *lsd, t_uint num, size_t width)
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

t_result	print_rights(t_lsdata *lsd, struct stat *fs)
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

	write_cout(lsd, ' ');
	return (RET_OK);
}

t_result	print_str(t_lsdata *lsd, char *str, size_t width)
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

t_result	print_date(t_lsdata *lsd, struct timespec *time)
{
	

}