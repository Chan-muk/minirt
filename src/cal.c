/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cal.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:28:08 by chajung           #+#    #+#             */
/*   Updated: 2023/04/28 12:28:13 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	size_vec(t_vector vec)
{
	return (sqrt((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z)));
}

t_vector	new_vec(double x, double y, double z)
{
	t_vector	vector;

	vector.x = x;
	vector.y = y;
	vector.z = z;
	return (vector);
}

t_ray	new_ray(t_vector org, t_vector dir)
{
	t_ray	ray;

	ray.org = org;
	ray.dir = dir;
	return (ray);
}

t_vector	unit_vec(t_vector vec)
{
	t_vector	vector;
	double		size;

	size = size_vec(vec);
	vector.x = vec.x / size;
	vector.y = vec.y / size;
	vector.z = vec.z / size;
	return (vector);
}

t_vector	cal_add_vec(t_vector vec_1, t_vector vec_2)
{
	t_vector	vector;

	vector.x = vec_1.x + vec_2.x;
	vector.y = vec_1.y + vec_2.y;
	vector.z = vec_1.z + vec_2.z;
	return (vector);
}

t_vector	cal_subtract_vec(t_vector vec_1, t_vector vec_2)
{
	t_vector	vector;

	vector.x = vec_1.x - vec_2.x;
	vector.y = vec_1.y - vec_2.y;
	vector.z = vec_1.z - vec_2.z;
	return (vector);
}

t_vector	cal_inverse_vec(t_vector vec)
{
	t_vector	vector;

	vector.x = (-1.0) * vec.x;
	vector.y = (-1.0) * vec.y;
	vector.z = (-1.0) * vec.z;
	return (vector);
}

t_vector	cal_multiply_vec(t_vector vec, double ratio)
{
	t_vector	vector;

	vector.x = ratio * vec.x;
	vector.y = ratio * vec.y;
	vector.z = ratio * vec.z;
	return (vector);
}

t_vector	cal_arithmetic_vec(t_vector vec_1, t_vector vec_2, double ratio)
{
	t_vector	vector;

	vector.x = ratio * (vec_1.x + vec_2.x);
	vector.y = ratio * (vec_1.y + vec_2.y);
	vector.z = ratio * (vec_1.z + vec_2.z);
	return (vector);
}

t_vector	cal_ray(t_ray ray, double ratio)
{
	t_vector vector;

	vector.x = ray.org.x + (ratio * ray.dir.x);
	vector.y = ray.org.y + (ratio * ray.dir.y);
	vector.z = ray.org.z + (ratio * ray.dir.z);
	return (vector);
}

double	cal_inner_vec(t_vector vec_1, t_vector vec_2)
{
	return ((vec_1.x * vec_2.x) + (vec_1.y * vec_2.y) + (vec_1.z * vec_2.z));
}

t_vector	cal_outer_vec(t_vector vec_1, t_vector vec_2)
{
	t_vector	vector;

	vector.x = (vec_1.y * vec_2.z) + (vec_1.z * vec_2.y);
	vector.y = (vec_1.z * vec_2.x) + (vec_1.x * vec_2.z);
	vector.z = (vec_1.x * vec_2.y) + (vec_1.y * vec_2.x);
	return (vector);
}
