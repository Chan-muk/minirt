/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cal0.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:28:08 by chajung           #+#    #+#             */
/*   Updated: 2023/04/28 12:28:13 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	new_vec(double x, double y, double z)
{
	t_vector	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

t_point	new_point(double x, double y, double z)
{
	t_point	point;

	point.x = x;
	point.y = y;
	point.z = z;
	return (point);
}

t_point	new_color(double r, double g, double b)
{
	t_color	color;

	color.x = r;
	color.y = g;
	color.z = b;
	return (color);
}

t_ray	ray(t_point org, t_vector dir)
{
	t_ray	ray;

	ray.org = org;
	ray.dir = unit_vec(dir);
	return (ray);
}

t_point	ray_at(t_ray *ray, double t)
{
	t_point	_ray;

	_ray = vec_add(ray->org, vec_mul(ray->dir, t));
	return (_ray);
}
