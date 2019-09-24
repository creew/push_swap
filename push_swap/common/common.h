/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 12:15:23 by eklompus          #+#    #+#             */
/*   Updated: 2019/09/23 17:52:47 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_COMMON_H
#define PUSH_SWAP_COMMON_H

#include "../libft/libft.h"

#include <stdlib.h>

# define	ARRSIZE(x)				(sizeof(x)/sizeof(x[0]))
# define	MAX_INTMIN				(2147483648)
# define	MAX_INTMAX				(2147483647)
# define	ERROR_ALLOCATING_STACK	(-1)
# define	ERROR_GETEMPTY_STACK	(-2)
# define	ERROR_WRONG_INTEGER		(-3)
# define	ERROR_OVERFLOW_INTEGER	(-4)
# define	ERROR_NO_ARGUMENTS		(-5)
# define 	ERROR_INCORRECT_ARGS	(-6)
# define 	ERROR_INCORRECT_STACK_SIZE	(-7)
# define 	ERROR_NOT_SORTED_STACK	(-8)
# define	RET_ENDL				(1)
# define	RET_OK					(0)

# define	STACK_SIZE				(1024)

# define	S_SA					(1)
# define	S_SB					(2)
# define	S_SS					(3)
# define	S_PA					(4)
# define	S_PB					(5)
# define	S_RA					(6)
# define	S_RB					(7)
# define	S_RR					(8)
# define	S_RRA					(9)
# define	S_RRB					(10)
# define	S_RRR					(11)

typedef struct	s_stack
{
	int			*stack;
	size_t		max_size;
	size_t		pos;
}				t_stack;

int				arg_read(int n, char *av[], t_stack *st1);

int				stack_push(t_stack *st, int a);
int				stack_pop(t_stack *st, int *a);
int				stack_init(t_stack *st);
int				stack_get_first(t_stack *st, int *a);
int				stack_add_first(t_stack *st, int a);
int				stack_free(t_stack *st);
int				stack_swap(t_stack *st);
int				stack_rotate(t_stack *st);
int				stack_rrotate(t_stack *st);
int				is_stack_sorted(t_stack *st);

int				safe_atoi(char *arg, int *res);
#endif
