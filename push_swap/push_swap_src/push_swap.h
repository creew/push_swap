/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 10:55:57 by eklompus          #+#    #+#             */
/*   Updated: 2019/09/23 10:55:57 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "common.h"

int		calc_optimal(t_stg *stg);
void	paste_optimal(t_stg *stg, t_diff *gres, int *count);

int		find_min_index(t_stack *st);
int		is_cycle_sorted(t_stack *st, int start);
void	sort3items(t_stg *stg, int *count);
int		normalize_stack(t_stg *stg, int *count);
int		is_stack_sorted_index(t_stack *st);

int		get_actual_diff(t_diff *d);
void	set_tdiff(t_diff *d, int s1_diff, int s2_diff);
int		find_min_diff(int s1[], int s2[], t_diff *d);
int		get_prev_i(t_stack *st, int index);
int		*find_max_sorted(t_stack *stack, int *maxlen);
int		find_med_val(t_stack *stack, const int *max_sorted, int *res);
#endif
