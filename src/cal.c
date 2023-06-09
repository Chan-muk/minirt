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

t_vec3		vec3(double x, double y, double z)
{
	t_vec3 vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

//포인트3 생성자
t_point3	point3(double x, double y, double z)
{
	t_point3 point;

	point.x = x;
	point.y = y;
	point.z = z;
	return (point);
}

//색상3 생성자
t_point3	color3(double r, double g, double b)
{
	t_color3 color;

	color.x = r;
	color.y = g;
	color.z = b;
	return (color);
}

// 벡터 값 설정
void		vset(t_vec3 *vec, double x, double y, double z)
{
	vec->x = x;
	vec->y = y;
	vec->z = z;
}

// 벡터 길이 제곱
double		vlength2(t_vec3 vec)
{
	return (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

// 벡터 길이
double		vlength(t_vec3 vec)
{
	return (sqrt(vlength2(vec)));
}

// 벡터합
t_vec3		vplus(t_vec3 vec, t_vec3 vec2)
{
	vec.x += vec2.x;
	vec.y += vec2.y;
	vec.z += vec2.z;
	return (vec);
}

// 벡터합2
t_vec3		vplus_(t_vec3 vec, double x, double y, double z)
{
	vec.x += x;
	vec.y += y;
	vec.z += z;
	return (vec);
}

// 벡터차
t_vec3		vminus(t_vec3 vec, t_vec3 vec2)
{
	vec.x -= vec2.x;
	vec.y -= vec2.y;
	vec.z -= vec2.z;
	return (vec);
}

t_vec3		vminus_(t_vec3 vec, double x, double y, double z)
{
	vec.x -= x;
	vec.y -= y;
	vec.z -= z;
	return (vec);
}

// 벡터 * 스칼라 곱연산
t_vec3		vmult(t_vec3 vec, double t)
{
	vec.x *= t;
	vec.y *= t;
	vec.z *= t;
	return (vec);
}

// 벡터 축 값끼리 곱연산
t_vec3		vmult_(t_vec3 vec, t_vec3 vec2)
{
	vec.x *= vec2.x;
	vec.y *= vec2.y;
	vec.z *= vec2.z;
	return (vec);
}

// 벡터 스칼라 나누기
t_vec3		vdivide(t_vec3 vec, double t)
{
	vec.x *= 1 / t;
	vec.y *= 1 / t;
	vec.z *= 1 / t;

	return vec;
}

// 벡터 내적
double		vdot(t_vec3 vec, t_vec3 vec2)
{
	return (vec.x * vec2.x + vec.y * vec2.y + vec.z * vec2.z);
}

// 벡터 외적
t_vec3		vcross(t_vec3 vec, t_vec3 vec2)
{
	t_vec3 new;

	new.x = vec.y * vec2.z - vec.z * vec2.y;
	new.y = vec.z * vec2.x - vec.x * vec2.z;
	new.z = vec.x * vec2.y - vec.y * vec2.x;
	return (new);
}

// 단위 벡터
t_vec3		vunit(t_vec3 vec)
{
	double len = vlength(vec);
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

// 두 벡터의 원소를 비교하여 작은 값들만 반환 
t_vec3	vmin(t_vec3 vec1, t_vec3 vec2)
{
	if (vec1.x > vec2.x)
		vec1.x = vec2.x;
	if (vec1.y > vec2.y)
		vec1.y = vec2.y;
	if (vec1.z > vec2.z)
		vec1.z = vec2.z;
	return (vec1);
}

t_ray	ray(t_point3 orig, t_vec3 dir)
{
	t_ray ray;

	ray.orig = orig;
	ray.dir = vunit(dir);
	return (ray);
}

//ray origin point 부터 방향벡터 ray dir * t 만큼 떨어진 점.
t_point3	ray_at(t_ray *ray, double t)
{
	t_point3 at;

	at = vplus(ray->orig, vmult(ray->dir, t));
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
