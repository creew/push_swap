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

#include <stdlib.h>
#include "libft.h"

typedef unsigned int	t_uint;
typedef unsigned char	t_uchar;

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




# define	ERROR_ENOMEM			(-1)
# define	ERROR_GETEMPTY_STACK	(-2)
# define	ERROR_WRONG_INTEGER		(-3)
# define	ERROR_OVERFLOW_INTEGER	(-4)
# define	ERROR_NO_ARGUMENTS		(-5)
# define 	ERROR_INCORRECT_ARGS	(-6)
# define 	ERROR_INCORRECT_STACK_SIZE	(-7)
# define 	ERROR_NOT_SORTED_STACK	(-8)
# define 	ERROR_INVALID_VAL		(-9)
# define	RET_ENDL				(1)
# define	RET_OK					(0)

# define	STACK_SIZE				(1024)

typedef struct	s_stack
{
	int			*stack;
	size_t		max_size;
	size_t		pos;
}				t_stack;

# define	ACTIONS_SIZE			(512)

typedef struct	s_action_array
{
	t_uchar		*array;
	size_t 		pos;
}				t_action_array;

typedef struct	s_dllist
{
	struct s_dllist	*next;
	struct s_dllist	*prev;
	t_action_array	data;
}				t_dllist;

int			stack_init(t_stack *st);
int			stack_push(t_stack *st, int a);
int			stack_pop(t_stack *st, int *a);
int			stack_get_first(t_stack *st, int *a);
int			stack_add_first(t_stack *st, int a);

int			is_stack_sorted(t_stack *st, size_t n, int backward);
int 		stack_free(t_stack *st);
int 		stack_swap(t_stack *st);
int 		stack_rotate(t_stack *st);
int 		stack_rrotate(t_stack *st);

int			run_commands(t_stack *st1, t_stack *st2, int cmd, int *count);

int			safe_atoi(char *arg, int *res);

int			arg_read(int n, char *av[], t_stack *st1);

int 		is_arr_sorts(t_action_array *act, t_stack *st_orig, t_stack *st1, t_stack *st2);

int		add_new_dllist(t_dllist **root, t_dllist **res);
void	rm_dllist(t_dllist **root, t_dllist *dll);
#endif
