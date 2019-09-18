#ifndef MAIN_H
# define MAIN_H

#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef unsigned long long  t_ullong;
typedef unsigned long		t_ulong;
typedef unsigned int		t_uint;


typedef union  u_ldouble
{ 
    long double	val;
    struct b_double
    {
        t_ulong	man:64;
        t_ulong	exp:15;
        t_ulong	sign:1;
    }			bldbl;
}               t_ldouble;

typedef struct  s_longb
{
    t_uint      val[65];
    size_t      max_size;
    size_t      size;
    size_t      base;
}               t_longb;

int		calc_big_double(t_longb *longb, t_ullong val, t_ullong bits);
void	print_longb(t_longb *longb);
void	ft_putchar(char c);
int		calc_big_double1(t_longb *longb, t_ullong val, long bits);
#endif