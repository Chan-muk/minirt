/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mygo <mygo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 15:22:53 by mygo              #+#    #+#             */
/*   Updated: 2023/05/21 15:22:54 by mygo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	drandom48(void)
{
	return (double)rand() / (double)RAND_MAX;
}

t_vector	random_in_unit_sphere(void)
{
	t_vector	p;

	p = cal_subtract_vec(\
	cal_multiply_vec(new_vec(drandom48(), drandom48(), drandom48()), 2.0), \
	new_vec(1.0, 1.0, 1.0));
	while ((size_vec(p) * size_vec(p)) >= 1.0)
	{
		p = cal_subtract_vec(\
		cal_multiply_vec(new_vec(drandom48(), drandom48(), drandom48()), 2.0), \
		new_vec(1.0, 1.0, 1.0));
	}
	return (p);
}
