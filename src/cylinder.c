/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 13:18:08 by chajung           #+#    #+#             */
/*   Updated: 2023/05/29 13:18:09 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	hit_cylinder(void *this, t_hitarg arg)
{
	t_cylinder	*cylinder;
	t_vector	r_center;
	double		a;
	double		b;
	double		c;
	double		discriminant;
	double		root;

	double		vh;
	double		wh;

	cylinder = (t_cylinder *)this;
	vh = cal_inner_vec(arg.ray->org, unit_vec(cal_subtract_vec(cylinder->height, cylinder->center)));
	wh = cal_inner_vec(r_center, unit_vec(cal_subtract_vec(cylinder->height, cylinder->center)));

	r_center = cal_subtract_vec(arg.ray->org, cylinder->center);
	a = cal_inner_vec(arg.ray->dir, arg.ray->dir) - (vh * vh);
	b = 2 * (cal_inner_vec(arg.ray->dir, r_center) - (vh * wh));
	c = cal_inner_vec(r_center, r_center) - (wh * wh) - ((cylinder->diameter / 2) * (cylinder->diameter / 2));

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
	outward_normal = cal_divide_vec(cal_subtract_vec(arg.rec->p, cylinder->center), cylinder->diameter / 2);
	arg.rec->set_face_normal(arg.rec, *arg.ray, outward_normal);
	arg.rec->mat_ptr = cylinder->mat_ptr;
	return (true);
}
