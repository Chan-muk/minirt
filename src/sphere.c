/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:53:47 by chajung           #+#    #+#             */
/*   Updated: 2023/05/22 13:53:48 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	hit_sphere(void *this, t_hitarg arg)
{
	t_sphere	*sphere;
	t_vector	r_center;
	double		a;
	double		b;
	double		c;
	double		discriminant;
	double		root;

	sphere = (t_sphere *)this;
	r_center = cal_subtract_vec(arg.ray->org, sphere->center);
	a = cal_inner_vec(arg.ray->dir, arg.ray->dir);
	b = cal_inner_vec(r_center, arg.ray->dir);
	c = cal_inner_vec(r_center, r_center) - (sphere->radius * sphere->radius);
	discriminant = (b * b) - (a * c);
	if (discriminant < 0.0)
		return (false);
	root = (-b - sqrt(discriminant)) / a;
	if (root < arg.min || arg.max < root) {
		root = (-b + sqrt(discriminant)) / a;
		if (root < arg.min || arg.max < root)
			return (false);
	}
	arg.rec->t = root;
	arg.rec->p = cal_ray(*arg.ray, arg.rec->t);
	
	t_vector	outward_normal;
	outward_normal = cal_divide_vec(cal_subtract_vec(arg.rec->p, sphere->center), sphere->radius);
	arg.rec->set_face_normal(arg.rec, *arg.ray, outward_normal);
	
	arg.rec->mat_ptr = sphere->mat_ptr;
	return (true);
}
