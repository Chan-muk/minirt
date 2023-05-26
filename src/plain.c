/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plain.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 10:50:27 by chajung           #+#    #+#             */
/*   Updated: 2023/05/26 10:50:28 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	hit_plain(void *this, t_hitarg arg)
{
	t_plain		*plain;
	t_vector	r_center;
	double		numrator;
	double		denominator;
	double		root;
	
	plain = (t_plain *)this;
	denominator = cal_inner_vec(arg.ray->dir, plain->normal_vector);
	if (fabs(denominator) < arg.min)
		return (false);
	numrator = cal_inner_vec(cal_subtract_vec(plain->center, arg.ray->org), plain->normal_vector);
	// numrator = cal_inner_vec(cal_subtract_vec(arg.ray->org, plain->center), plain->normal_vector);
	root = numrator / denominator;
	// printf("min: %f, max: %f\n", arg.min, arg.max);
	if (root < arg.min || arg.max < root)
		return (false);
	arg.rec->t = root;
	arg.rec->p = cal_ray(*arg.ray, arg.rec->t);
	if (arg.rec->p.x < -1.0 || arg.rec->p.x > 1.0)
		return (false);
	if (arg.rec->p.y < -0.5 || arg.rec->p.y > 0.5)
		return (false);
	arg.rec->normal = plain->normal_vector;
	arg.rec->set_face_normal(arg.rec, *arg.ray, arg.rec->normal);
	arg.rec->mat_ptr = plain->mat_ptr;
	
	// rec->albedo = pl_obj->albedo;

	// set_face_normal(ray, rec);
	// rec->color = pl_obj->color;
	return (true);
}

// bool	hit_plain(void *this, t_hitarg arg)
// {
// 	t_plain		*plain;
// 	t_vector	r_center;
// 	double		a;
// 	double		b;
// 	double		root;

// 	plain = (t_plain *)this;
// 	r_center = cal_subtract_vec(arg.ray->org, plain->center);
// 	a = cal_inner_vec(arg.ray->dir, plain->normal_vector);
// 	b = cal_inner_vec(r_center, plain->normal_vector);

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
// 	// outward_normal = cal_divide_vec(cal_subtract_vec(arg.rec->p, plain->center), plain->radius);
// 	arg.rec->set_face_normal(arg.rec, *arg.ray, plain->normal_vector);
	
// 	arg.rec->mat_ptr = plain->mat_ptr;
// 	return (true);
// }
