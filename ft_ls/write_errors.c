
#include "ft_ls.h"

t_result	write_usage(void)
{
	ft_putstr_fd("usage: ls [-", 2);
	ft_putstr_fd(LEGAL_OPTIONS, 2);
	ft_putstr_fd("] [file ...]", 2);
	ft_putchar_fd('\n', 2);
	return (RET_OK);
}

t_result	write_illegal_param(char s)
{
	ft_putstr_fd("ls: illegal option -- ", 2);
	ft_putchar_fd(s, 2);
	ft_putchar_fd('\n', 2);
	return (RET_OK);
}