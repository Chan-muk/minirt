/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 11:34:47 by chajung           #+#    #+#             */
/*   Updated: 2023/06/27 11:34:48 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	_cone_cap_color(t_hit_array *obj, t_hit_record *rec)
{
	if (obj->flag == _color)
		rec->color = obj->color;
	else if (obj->flag == _checker)
		rec->color = cylinder_checkerboard_cap(rec->p, obj);
	else if (obj->flag == _texture)
	{
		rec->color = cylinder_texture_cap(rec->p, obj);
		cylinder_bump_cap(rec->p, obj, rec);
	}
}

int	cone_cap(t_hit_array *cone, t_ray *ray, t_hit_record *rec, \
double height)
{
	double	numrator;
	double	denominator;
	double	root;
	double	rad;

	if (check_object_height(cone, ray, height))
		return (false);
	denominator = vec_dot(ray->dir, cone->norm);
	if (fabs(denominator) < rec->tmin)
		return (false);
	numrator = vec_dot(vec_sub(cone->center, ray->org), cone->norm);
	root = numrator / denominator;
	if (root < rec->tmin || root > rec->tmax)
		return (false);
	rad = \
	vec_len(vec_sub(vec_add(ray->org, vec_mul(ray->dir, root)), cone->center));
	if ((rad * rad) > (cone->radius * cone->radius) || rad < 0.0)
		return (false);
	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->normal = cone->norm;
	set_face_normal(ray, rec);
	_cone_cap_color(cone, rec);
	return (true);
}
