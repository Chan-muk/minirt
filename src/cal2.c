/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cal2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 12:51:48 by chajung           #+#    #+#             */
/*   Updated: 2023/06/21 12:51:49 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	vec_len(t_vector vec)
{
	return (sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

double	vec_dot(t_vector vec, t_vector vec2)
{
	return (vec.x * vec2.x + vec.y * vec2.y + vec.z * vec2.z);
}

t_vector	vec_prod(t_vector vec, t_vector vec2)
{
	t_vector	new;

	new.x = vec.y * vec2.z - vec.z * vec2.y;
	new.y = vec.z * vec2.x - vec.x * vec2.z;
	new.z = vec.x * vec2.y - vec.y * vec2.x;
	return (new);
}

t_vector	unit_vec(t_vector vec)
{
	double	len;

	len = vec_len(vec);
	if (len == 0.0)
		exit_with_str("Length of vector is 0.", EXIT_FAILURE);
	vec.x /= len;
	vec.y /= len;
	vec.z /= len;
	return (vec);
}

t_vector	vec_cmp(t_vector vec1, t_vector vec2)
{
	if (vec1.x > vec2.x)
		vec1.x = vec2.x;
	if (vec1.y > vec2.y)
		vec1.y = vec2.y;
	if (vec1.z > vec2.z)
		vec1.z = vec2.z;
	return (vec1);
}
