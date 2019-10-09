/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 12:05:34 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/07 12:14:26 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

const char *g_months[12] = {
	"Jan", "Feb", "Mar", "Apr", "May", "Jun",
	"Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

t_result	print_ulong(t_lsdata *lsd, t_ulong num, size_t width, int right)
{
	t_uint size;

	size = get_ulong_width(num);
	while (!right && size++ < width)
		write_cout(lsd, ' ');
	write_number(lsd, num);
	while (right && size++ < width)
		write_cout(lsd, ' ');
	return (RET_OK);
}

t_result	print_str(t_lsdata *lsd, char *str, size_t width, int right)
{
	t_uint size;

	size = ft_strlen(str);
	while (!right && size++ < width)
		write_cout(lsd, ' ');
	write_out(lsd, str);
	while (right && size++ < width)
		write_cout(lsd, ' ');
	return (RET_OK);
}

t_result	print_date(t_lsdata *lsd, time_t ti)
{
	t_fttime	tft;

	parse_time(ti, &tft);
	write_out(lsd, g_months[tft.month]);
	write_cout(lsd, ' ');
	if (get_ulong_width(tft.day) < 2)
		write_cout(lsd, ' ');
	write_number(lsd, tft.day);
	write_cout(lsd, ' ');
	if (date_cmp_6month(ti, lsd->ctime) == 0)
	{
		if (get_ulong_width(tft.hour) < 2)
			write_cout(lsd, '0');
		write_number(lsd, tft.hour);
		write_cout(lsd, ':');
		if (get_ulong_width(tft.minute) < 2)
			write_cout(lsd, '0');
		write_number(lsd, tft.minute);
	}
	else
	{
		write_cout(lsd, ' ');
		write_number(lsd, tft.year);
	}
	return (RET_OK);
}

static int	print_color(t_lsdata *lsd, t_fentry *entry, int f)
{
	if (S_ISDIR(entry->fs.st_mode))
	{
		if ((entry->fs.st_mode & ACCESSPERMS) == ACCESSPERMS)
		{
			write_out(lsd, ANSI_BLACK);
			f = write_out(lsd, entry->fs.st_mode & S_ISVTX ?
						ANSI_BG_GREEN : ANSI_BG_YELLOW);
		}
		else
			f = write_out(lsd, ANSI_BLUE);
	}
	else if (S_ISLNK(entry->fs.st_mode))
		f = write_out(lsd, ANSI_PURPLE);
	else if (S_ISREG(entry->fs.st_mode) && ((entry->fs.st_mode & S_IXUSR) ||
		(entry->fs.st_mode & S_IXGRP) || (entry->fs.st_mode & S_IXOTH)))
		f = write_out(lsd, ANSI_RED);
	else if (S_ISBLK(entry->fs.st_mode) || S_ISCHR(entry->fs.st_mode))
	{
		write_out(lsd, ANSI_BLUE);
		f = write_out(lsd, S_ISBLK(entry->fs.st_mode) ?
						ANSI_BG_CYAN : ANSI_BG_YELLOW);
	}
	return (f);
}

t_result	print_name(t_lsdata *lsd, t_fentry *entry, size_t width)
{
	int		f;
	size_t	len;

	f = 0;
	if (lsd->flags & F_COLORISED)
		f = print_color(lsd, entry, 0);
	len = write_out(lsd, entry->name);
	if (f)
		write_out(lsd, ANSI_RESET);
	while (len++ < width)
		write_cout(lsd, ' ');
	print_link(lsd, entry);
	return (RET_OK);
}
