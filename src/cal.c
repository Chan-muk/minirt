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

t_vector	new_vec(double x, double y, double z)
{
	t_vector vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

t_point	new_point(double x, double y, double z)
{
	t_point point;

	point.x = x;
	point.y = y;
	point.z = z;
	return (point);
}

t_point	new_color(double r, double g, double b)
{
	t_color color;

	color.x = r;
	color.y = g;
	color.z = b;
	return (color);
}

void	set_vec(t_vector *vec, double x, double y, double z)
{
	vec->x = x;
	vec->y = y;
	vec->z = z;
}

double	vec_len_2(t_vector vec)
{
	return (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

double	vec_len(t_vector vec)
{
	return (sqrt(vec_len_2(vec)));
}

t_vector	vec_add(t_vector vec, t_vector vec2)
{
	vec.x += vec2.x;
	vec.y += vec2.y;
	vec.z += vec2.z;
	return (vec);
}

t_vector	vec_add_(t_vector vec, double x, double y, double z)
{
	vec.x += x;
	vec.y += y;
	vec.z += z;
	return (vec);
}

t_vector	vec_sub(t_vector vec, t_vector vec2)
{
	vec.x -= vec2.x;
	vec.y -= vec2.y;
	vec.z -= vec2.z;
	return (vec);
}

t_vector	vec_sub_(t_vector vec, double x, double y, double z)
{
	vec.x -= x;
	vec.y -= y;
	vec.z -= z;
	return (vec);
}

t_vector	vec_mul(t_vector vec, double t)
{
	vec.x *= t;
	vec.y *= t;
	vec.z *= t;
	return (vec);
}

t_vector	vec_mul_(t_vector vec, t_vector vec2)
{
	vec.x *= vec2.x;
	vec.y *= vec2.y;
	vec.z *= vec2.z;
	return (vec);
}

t_vector	vec_div(t_vector vec, double t)
{
	vec.x *= 1 / t;
	vec.y *= 1 / t;
	vec.z *= 1 / t;

	return vec;
}

double	vec_dot(t_vector vec, t_vector vec2)
{
	return (vec.x * vec2.x + vec.y * vec2.y + vec.z * vec2.z);
}

t_vector	vec_prod(t_vector vec, t_vector vec2)
{
	t_vector new;

	new.x = vec.y * vec2.z - vec.z * vec2.y;
	new.y = vec.z * vec2.x - vec.x * vec2.z;
	new.z = vec.x * vec2.y - vec.y * vec2.x;
	return (new);
}

t_vector	unit_vec(t_vector vec)
{
	double len = vec_len(vec);
	if (len == 0)
	{
		printf("Error\n:Devider is 0");
		exit(0);
	}
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

t_ray	ray(t_point orig, t_vector dir)
{
	t_ray ray;

	ray.org = orig;
	ray.dir = unit_vec(dir);
	return (ray);
}

t_point	ray_at(t_ray *ray, double t)
{
	t_point at;

	at = vec_add(ray->org, vec_mul(ray->dir, t));
	return (at);
}

// double	size_vec(t_vector vec)
// {
// 	return (sqrt((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z)));
// }

// t_vector	new_vec(double x, double y, double z)
// {
// 	t_vector	vector;

// 	vector.x = x;
// 	vector.y = y;
// 	vector.z = z;
// 	return (vector);
// }

// t_ray	new_ray(t_vector org, t_vector dir)
// {
// 	t_ray	ray;

// 	ray.org = org;
// 	ray.dir = dir;
// 	return (ray);
// }

// t_vector	unit_vec(t_vector vec)
// {
// 	t_vector	vector;
// 	double		size;

// 	size = size_vec(vec);
// 	vector.x = vec.x / size;
// 	vector.y = vec.y / size;
// 	vector.z = vec.z / size;
// 	return (vector);
// }

// t_vector	cal_add_vec(t_vector vec_1, t_vector vec_2)
// {
// 	t_vector	vector;

// 	vector.x = vec_1.x + vec_2.x;
// 	vector.y = vec_1.y + vec_2.y;
// 	vector.z = vec_1.z + vec_2.z;
// 	return (vector);
// }

// t_vector	cal_add3_vec(t_vector vec_1, t_vector vec_2, t_vector vec_3)
// {
// 	t_vector	vector;

// 	vector.x = vec_1.x + vec_2.x + vec_3.x;
// 	vector.y = vec_1.y + vec_2.y + vec_3.y;
// 	vector.z = vec_1.z + vec_2.z + vec_3.z;
// 	return (vector);
// }

// t_vector	cal_subtract_vec(t_vector vec_1, t_vector vec_2)
// {
// 	t_vector	vector;

// 	vector.x = vec_1.x - vec_2.x;
// 	vector.y = vec_1.y - vec_2.y;
// 	vector.z = vec_1.z - vec_2.z;
// 	return (vector);
// }

// t_vector	cal_inverse_vec(t_vector vec)
// {
// 	t_vector	vector;

// 	vector.x = (-1.0) * vec.x;
// 	vector.y = (-1.0) * vec.y;
// 	vector.z = (-1.0) * vec.z;
// 	return (vector);
// }

// t_vector	cal_multiply_vec(t_vector vec, double ratio)
// {
// 	t_vector	vector;

// 	vector.x = ratio * vec.x;
// 	vector.y = ratio * vec.y;
// 	vector.z = ratio * vec.z;
// 	return (vector);
// }

// t_vector	cal_multi_vec(t_vector vec_1, t_vector vec_2)
// {
// 	t_vector	vector;

// 	vector.x = vec_1.x * vec_2.x;
// 	vector.y = vec_1.y * vec_2.y;
// 	vector.z = vec_1.z * vec_2.z;
// 	return (vector);
// }

// t_vector	cal_divide_vec(t_vector vec, double ratio)
// {
// 	t_vector	vector;

// 	vector.x = vec.x / ratio;
// 	vector.y = vec.y / ratio;
// 	vector.z = vec.z / ratio;
// 	return (vector);
// }

// t_vector	cal_arithmetic_vec(t_vector vec_1, t_vector vec_2, double ratio)
// {
// 	t_vector	vector;

// 	vector.x = ratio * (vec_1.x + vec_2.x);
// 	vector.y = ratio * (vec_1.y + vec_2.y);
// 	vector.z = ratio * (vec_1.z + vec_2.z);
// 	return (vector);
// }

// t_vector	cal_ray(t_ray ray, double ratio)
// {
// 	t_vector vector;

// 	vector.x = ray.org.x + (ratio * ray.dir.x);
// 	vector.y = ray.org.y + (ratio * ray.dir.y);
// 	vector.z = ray.org.z + (ratio * ray.dir.z);
// 	return (vector);
// }

// double	cal_inner_vec(t_vector vec_1, t_vector vec_2)
// {
// 	return ((vec_1.x * vec_2.x) + (vec_1.y * vec_2.y) + (vec_1.z * vec_2.z));
// }

// t_vector	cal_outer_vec(t_vector vec_1, t_vector vec_2)
// {
// 	t_vector	vector;

// 	vector.x = (vec_1.y * vec_2.z) + (vec_1.z * vec_2.y);
// 	vector.y = (vec_1.z * vec_2.x) + (vec_1.x * vec_2.z);
// 	vector.z = (vec_1.x * vec_2.y) + (vec_1.y * vec_2.x);
// 	return (vector);
// }
