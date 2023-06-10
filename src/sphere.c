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

void	get_sphere_data(t_formula *formula, t_hit_array *sp, t_ray *ray)
{
	t_vector	r_center;

	r_center = vec_sub(ray->org, sp->center);
	formula->a = vec_dot(ray->dir, ray->dir);
	formula->b = vec_dot(r_center, ray->dir);
	formula->c = vec_dot(r_center, r_center) - (sp->radius * sp->radius);
	formula->discriminant = \
	(formula->b * formula->b) - (formula->a * formula->c);
}

bool	hit_sphere(t_hit_array *sp, t_ray *ray, t_hit_record *rec)
{
	t_formula	formula;
	double		root;

	get_sphere_data(&formula, sp, ray);
	if (formula.discriminant < 0.0)
		return (false);
	root = (-(formula.b) - sqrt(formula.discriminant)) / formula.a;
	if (root < rec->tmin || rec->tmax < root)
	{
		root = (-(formula.b) + sqrt(formula.discriminant)) / formula.a;
		if (root < rec->tmin || rec->tmax < root)
			return (false);
	}
	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->normal = vec_div(vec_sub(rec->p, sp->center), sp->radius);
	set_face_normal(ray, rec);
	return (true);
}
