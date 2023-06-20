/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:19:41 by chajung           #+#    #+#             */
/*   Updated: 2023/06/09 15:19:45 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_face_normal(t_ray *r, t_hit_record *rec)
{
	if (vec_dot(r->dir, rec->normal) < 0)
		rec->front_face = true;
	else
		rec->front_face = false;
	if (rec->front_face == true)
		rec->normal = rec->normal;
	else
		rec->normal = vec_mul(rec->normal, -1);
}

bool	hit_objects(t_hit_array *array, t_ray *ray, t_hit_record *rec)
{
	if (array->type == _plane)
		return (hit_plane(array, ray, rec));
	else if (array->type == _sphere)
		return (hit_sphere(array, ray, rec));
	else if (array->type == _cylinder)
		return (hit_cylinder(array, ray, rec));
	else if (array->type == _cone)
		return (hit_cone(array, ray, rec));
	return (false);
}

bool	hit_world(t_scene *scene)
{
	t_hit_array	*array;
	bool	hit;

	array = scene->world;
	// array = scene->array;
	hit = false;
	while (array->type)
	{
		if (hit_objects(array, &scene->ray, &scene->rec))
		{
			hit = true;
			scene->rec.tmax = scene->rec.t;
		}
		array++;
	}
	return (hit);
}
