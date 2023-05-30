/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 10:50:27 by chajung           #+#    #+#             */
/*   Updated: 2023/05/26 10:50:28 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	hit_plane(void *this, t_hitarg arg)
{
	t_plane		*plane;
	t_vector	r_center;
	double		numerator;
	double		denominator;
	double		root;
	
	plane = (t_plane *)this;
	denominator = cal_inner_vec(arg.ray->dir, unit_vec(plane->normal_vector));
	numerator = \
	cal_inner_vec(cal_subtract_vec(plane->center, arg.ray->org), unit_vec(plane->normal_vector));
	if (denominator == 0 && numerator != 0)
		return (false);
	root = numerator / denominator;
	if (root < arg.min || root > 1.0)
		return (false);
	arg.rec->t = root;
	arg.rec->p = cal_ray(*arg.ray, arg.rec->t);
	arg.rec->normal = plane->normal_vector;
	arg.rec->set_face_normal(arg.rec, *arg.ray, arg.rec->normal);
	arg.rec->mat_ptr = plane->mat_ptr;
	return (true);
}

// bool	check_plane(t_plane *plane, t_hitarg arg)
// {
// 	if (arg.rec->p.x < plane->center.x - ((double)((double)plane->size / 2)) || arg.rec->p.x > plane->center.x + ((double)((double)plane->size / 2)))
// 		return (false);
// 	if (arg.rec->p.y < plane->center.y - ((double)((double)plane->size / 2)) || arg.rec->p.y > plane->center.y + ((double)((double)plane->size / 2)))
// 		return (false);
// 	if (arg.rec->p.z < plane->center.z - ((double)((double)plane->size / 2)) || arg.rec->p.z > plane->center.z + ((double)((double)plane->size / 2)))
// 		return (false);
// 	return (true);
// }

// bool	hit_plane(void *this, t_hitarg arg)
// {
// 	t_plane		*plane;
// 	t_vector	r_center;
// 	double		numerator;
// 	double		denominator;
// 	double		root;
	
// 	plane = (t_plane *)this;
// 	denominator = cal_inner_vec(arg.ray->dir, unit_vec(plane->normal_vector));
// 	// if (denominator == 0)
// 	// 	return (false);
// 	if (fabs(denominator) < arg.min)
// 		return (false);
// 	numerator = cal_inner_vec(cal_subtract_vec(plane->center, arg.ray->org), unit_vec(plane->normal_vector));
// 	// numerator = cal_inner_vec(cal_subtract_vec(arg.ray->org, plane->center), plane->normal_vector);
// 	// if (fabs(denominator) < arg.min)
// 	// {
// 	// 	if (fabs(numerator) < arg.min)
// 	// 		return (false);
// 	// }
// 	root = numerator / denominator;
// 	// printf("min: %f, max: %f\n", arg.min, arg.max);
// 	// if (root < arg.min || arg.max < root)
// 	if (root < arg.min || 1.0 < root)
// 		return (false);
// 	arg.rec->t = root;
// 	arg.rec->p = cal_ray(*arg.ray, arg.rec->t);
// 	// if (check_plane(plane, arg) == false)
// 	// 	return (false);
// 	arg.rec->normal = plane->normal_vector;
// 	arg.rec->set_face_normal(arg.rec, *arg.ray, unit_vec(arg.rec->normal));
// 	arg.rec->mat_ptr = plane->mat_ptr;

// 	// rec->albedo = pl_obj->albedo;

// 	// set_face_normal(ray, rec);
// 	// rec->color = pl_obj->color;
// 	// if (check_plane(plane, arg) == false)
// 	// 	return (false);
// 	return (true);
// }

// bool	hit_plane(void *this, t_hitarg arg)
// {
// 	t_plane		*plane;
// 	t_vector	r_center;
// 	double		a;
// 	double		b;
// 	double		root;

// 	plane = (t_plane *)this;
// 	r_center = cal_subtract_vec(arg.ray->org, plane->center);
// 	a = cal_inner_vec(arg.ray->dir, plane->normal_vector);
// 	b = cal_inner_vec(r_center, plane->normal_vector);

// 	root = -b / a;
// 	// if (root < arg.min || arg.max < root)
// 	if (fabs(a) < arg.min || 1.0 < fabs(a))
// 	{
// 		// printf("A\n");
// 		return (false);
// 	}
// 	if (fabs(b) < arg.min || 1.0 < fabs(b))
// 	{
// 		// printf("B\n");
// 		// root = -b / a;
// 		// if (root < arg.min || arg.max < root)
// 			return (false);
// 	}
// 	// printf("x: %f, y: %f, z: %f\n", arg.ray->dir.x, arg.ray->dir.y, arg.ray->dir.z);
// 	// return (true);

// 	arg.rec->t = root;
// 	arg.rec->p = cal_ray(*arg.ray, arg.rec->t);
	
// 	// t_vector	outward_normal;
// 	// outward_normal = cal_divide_vec(cal_subtract_vec(arg.rec->p, plane->center), plane->radius);
// 	arg.rec->set_face_normal(arg.rec, *arg.ray, plane->normal_vector);
	
// 	arg.rec->mat_ptr = plane->mat_ptr;
// 	return (true);
// }
