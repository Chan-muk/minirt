/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:53:47 by chajung           #+#    #+#             */
/*   Updated: 2023/05/22 13:53:48 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// bool	hit_sphere(t_sphere *sp, t_ray *ray, t_hit_record *rec)
bool	hit_sphere(t_hit_array *sp, t_ray *ray, t_hit_record *rec)
{
	t_vector	r_center;
	double		a;
	double		b;
	double		c;
	double		discriminant;
	double		root;

	r_center = vec_sub(ray->org, sp->center);
	a = vec_len_2(ray->dir);
	b = vec_dot(r_center, ray->dir);
	c = vec_len_2(r_center) - sp->radius * sp->radius;
	discriminant = b * b - a * c;
	if (discriminant < 0.0)
		return (false);
	root = (-b - sqrt(discriminant)) / a;
	if (root < rec->tmin || rec->tmax < root)
	{
		root = (-b + sqrt(discriminant)) / a;
		if (root < rec->tmin || rec->tmax < root)
			return (false);
	}
	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->normal = vec_div(vec_sub(rec->p, sp->center), sp->radius);
	set_face_normal(ray, rec);
	return (true);
}

// t_sphere	sphere(t_point center, double radius)
// {
// 	t_sphere sp;

// 	sp.center = center;
// 	sp.radius = radius;
// 	return (sp);
// }

// bool	hit_sphere(void *this, t_hitarg arg)
// {
// 	t_sphere	*sphere;
// 	t_vector	r_center;
// 	double		a;
// 	double		b;
// 	double		c;
// 	double		discriminant;
// 	double		root;

// 	sphere = (t_sphere *)this;
// 	r_center = cal_subtract_vec(arg.ray->org, sphere->center);
// 	a = cal_inner_vec(arg.ray->dir, arg.ray->dir);
// 	b = cal_inner_vec(r_center, arg.ray->dir);
// 	c = cal_inner_vec(r_center, r_center) - (sphere->radius * sphere->radius);
// 	discriminant = (b * b) - (a * c);
// 	if (discriminant < 0.0)
// 		return (false);
// 	root = (-b - sqrt(discriminant)) / a;
// 	if (root < arg.min || arg.max < root) {
// 		root = (-b + sqrt(discriminant)) / a;
// 		if (root < arg.min || arg.max < root)
// 			return (false);
// 	}
// 	arg.rec->t = root;
// 	arg.rec->p = cal_ray(*arg.ray, arg.rec->t);
// 	t_vector	outward_normal;
// 	outward_normal = cal_divide_vec(cal_subtract_vec(arg.rec->p, sphere->center), sphere->radius);
// 	arg.rec->set_face_normal(arg.rec, *arg.ray, outward_normal);
// 	arg.rec->mat_ptr = sphere->mat_ptr;
// 	return (true);
// }


// double	get_find_root_1(t_sphere *sphere, t_hitarg arg, double discriminant)
// {
// 	t_vector	r_center;
// 	double		a;
// 	double		b;

// 	r_center = cal_subtract_vec(arg.ray->org, sphere->center);
// 	a = cal_inner_vec(arg.ray->dir, arg.ray->dir);
// 	b = cal_inner_vec(r_center, arg.ray->dir);
// 	return ((-b - sqrt(discriminant)) / a);
// }

// double	get_find_root_2(t_sphere *sphere, t_hitarg arg, double discriminant)
// {
// 	t_vector	r_center;
// 	double		a;
// 	double		b;

// 	r_center = cal_subtract_vec(arg.ray->org, sphere->center);
// 	a = cal_inner_vec(arg.ray->dir, arg.ray->dir);
// 	b = cal_inner_vec(r_center, arg.ray->dir);
// 	return ((-b + sqrt(discriminant)) / a);
// }

// double	get_sphere_discriminant(t_sphere *sphere, t_hitarg arg)
// {
// 	t_vector	r_center;
// 	double		a;
// 	double		b;
// 	double		c;
// 	double		discriminant;
	
// 	r_center = cal_subtract_vec(arg.ray->org, sphere->center);
// 	a = cal_inner_vec(arg.ray->dir, arg.ray->dir);
// 	b = cal_inner_vec(r_center, arg.ray->dir);
// 	c = cal_inner_vec(r_center, r_center) - (sphere->radius * sphere->radius);
// 	discriminant = (b * b) - (a * c);
// 	return (discriminant);
// }

// bool	hit_sphere(void *this, t_hitarg arg)
// {
// 	t_sphere	*sphere;
// 	t_vector	outward_normal;
// 	double		discriminant;
// 	double		root;

// 	sphere = (t_sphere *)this;
// 	discriminant = get_sphere_discriminant(sphere, arg);
// 	if (discriminant < 0.0)
// 		return (false);
// 	root = get_find_root_1(sphere, arg, discriminant);
// 	if (root < arg.min || arg.max < root)
// 	{
// 		root = get_find_root_2(sphere, arg, discriminant);
// 		if (root < arg.min || arg.max < root)
// 			return (false);
// 	}
// 	arg.rec->t = root;
// 	arg.rec->p = cal_ray(*arg.ray, arg.rec->t);
// 	outward_normal = cal_divide_vec(cal_subtract_vec(arg.rec->p, sphere->center), sphere->radius);
// 	arg.rec->set_face_normal(arg.rec, *arg.ray, outward_normal);
// 	arg.rec->mat_ptr = sphere->mat_ptr;
// 	return (true);
// }
