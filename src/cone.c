/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conelinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 13:18:08 by chajung           #+#    #+#             */
/*   Updated: 2023/05/29 13:18:09 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	cone_cap(t_hit_array* cone, t_vector c, t_ray *ray, t_hit_record *rec)
{
	double	numrator;
	double	denominator;
	double	root;

	denominator = vec_dot(ray->dir, cone->norm);
	if (fabs(denominator) < 0.0000000001)
		return (false);
	numrator = vec_dot(vec_sub(c, ray->org), cone->norm);
	root = numrator / denominator;
	if (root < rec->tmin || root > rec->tmax)
		return (false);
	t_vector	P = vec_add(ray->org, vec_mul(ray->dir, root));
	double		pc = vec_len(vec_sub(P, c));
	if (pc * pc > (cone->radius * 0.5) * (cone->radius * 0.5) || pc < 0.0)
		return (false);
	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->normal = cone->norm;
	set_face_normal(ray, rec);
	return (true);
}

bool	cone_side(t_hit_array *cone, t_ray *ray, t_hit_record *rec)
{
	double	a;
	double	half_b;
	double	c;
	double	discriminant;
	double	root;

	t_vector	H = vec_add(cone->center, vec_mul(cone->norm, cone->height));
	double		h = vec_len(vec_sub(cone->center, H));
	double		m = (cone->radius * cone->radius) / (h * h);
	t_vector	w = vec_sub(ray->org, H);

	double		vh = vec_dot(ray->dir, cone->norm);
	double		wh = vec_dot(w, cone->norm);

	// a = vec_dot(ray->dir, ray->dir) - (m - 1) * (vec_dot(ray->dir, cone->norm) * vec_dot(ray->dir, cone->norm));
	// half_b = vec_dot(ray->dir, w) - (m - 1) * (vec_dot(ray->dir, cone->norm) * vec_dot(w, cone->norm));
	// c = vec_dot(w, w) - (m - 1) * (vec_dot(w, cone->norm) * vec_dot(w, cone->norm));
	
	a = vec_dot(ray->dir, ray->dir) - (m * (vh * vh)) - (vh * vh);
	half_b = vec_dot(ray->dir, w) - (m * vh * wh) - (vh * wh);
	c = vec_dot(w, w) - (m * (wh * wh)) - (wh * wh);


	discriminant = half_b * half_b - a * c;
	// if (discriminant < 0)
	// 	return (false);
	// root = (-half_b - sqrt(discriminant)) / a;
	// if (root < rec->tmin || root > rec->tmax)
	// 	return (false);
	
	if (discriminant < 0.0)
		return (false);
	root = (-half_b - sqrt(discriminant)) / a;
	if (root < rec->tmin || rec->tmax < root)
	{
		root = (-half_b + sqrt(discriminant)) / a;
		if (root < rec->tmin || rec->tmax < root)
			return (false);
	}

	t_vector	P = vec_add(ray->org, vec_mul(ray->dir, root));
	double		qc = vec_dot(vec_sub(P, cone->center), cone->norm);
	if (qc > cone->height || qc < 0.0)
		return (false);
	
	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->normal = cone->norm;
	set_face_normal(ray, rec);
	return (true);
}

bool	hit_cone(t_hit_array *cone, t_ray *ray, t_hit_record *rec)
{
	int	flag = 0;
	if (cone_side(cone, ray, rec))
		flag++;
	// if (cone_cap(cone, cone->center, ray, rec))
	// 	flag++;
	if (flag)
		return (true);
	return(false);
}
