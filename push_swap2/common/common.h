/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 15:05:34 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/21 15:05:35 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include <stdlib.h>
# include "libft.h"

typedef unsigned int	t_uint;
typedef unsigned char	t_uchar;

# define ARRSIZE(x)				(sizeof(x)/sizeof(x[0]))

# define S_SA					(1)
# define S_SB					(2)
# define S_SS					(3)
# define S_PA					(4)
# define S_PB					(5)
# define S_RA					(6)
# define S_RB					(7)
# define S_RR					(8)
# define S_RRA					(9)
# define S_RRB					(10)
# define S_RRR					(11)
# define S_ERROR				(-1)

# define ERROR_ENOMEM			(-1)
# define ERROR_GETEMPTY_STACK	(-2)
# define ERROR_WRONG_INTEGER	(-3)
# define ERROR_OVERFLOW_INTEGER	(-4)
# define ERROR_NO_ARGUMENTS		(-5)
# define ERROR_INCORRECT_ARGS	(-6)
# define ERROR_INCORRECT_STACK_SIZE	(-7)
# define ERROR_NOT_SORTED_STACK	(-8)
# define ERROR_INVALID_VAL		(-9)
# define ERROR_ARG_ONLY_PM		(-10)
# define ERROR_DUPL_VAL			(-11)
# define RET_ENDL				(1)
# define RET_OK					(0)

# define STACK_SIZE				(128)

typedef struct	s_stack
{
	int			*stack;
	size_t		max_size;
	size_t		pos;
}				t_stack;

typedef struct	s_diff
{
	int			s1_diff;
	int			s2_diff;
}				t_diff;

typedef struct	s_stg
{
	t_stack		st1;
	t_stack		st2;
	int			is_show_stat;
}				t_stg;

int				arg_read(int n, char *av[], t_stg *stg);
int				run_commands(t_stg *stg, int n, int *count);

int				stack_push(t_stack *st, int a);
int				stack_pop(t_stack *st, int *a);
int				stack_init(t_stack *st);
int				stack_free(t_stack *st);
int				stack_swap(t_stack *st);
int				stack_rotate(t_stack *st);
int				stack_rrotate(t_stack *st);
int				is_stack_sorted(t_stack *st, size_t n);

int				safe_atoi(char *arg, int *res);

char			*get_action_str(int i);

void			print_stacks(t_stg *stg);
#endif
