/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_dir.h                                           :+:      :+:    :+:   */
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

enum {
	S_SA,
	S_SB,
	S_SS,
	S_PA,
	S_PB,
	S_RA,
	S_RB,
	S_RR,
	S_RRA,
	S_RRB,
	S_RRR,
	S_ERROR
};

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
# define ERROR_UNKNOWN			(-12)

# define RET_ENDL				(1)
# define RET_OK					(0)

# define STACK_SIZE				(128)

typedef struct	s_stack
{
	int			*stack;
	size_t		max_size;
	union {
		size_t		pos;
		size_t		size;
	};

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
	int			is_colorized;
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

int				read_int_val(char *arg, int *res);

char			*get_action_str(int i);

void			print_stacks(t_stg *stg);
#endif
