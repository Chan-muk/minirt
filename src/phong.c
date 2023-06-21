/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 12:58:31 by chajung           #+#    #+#             */
/*   Updated: 2023/06/21 12:58:32 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	reflect(t_vector v, t_vector n)
{
	return (vec_sub(v, vec_mul(n, vec_dot(v, n) * 2)));
}

bool	hit_shadow(t_hit_array *array, t_ray *ray, t_hit_record *rec)
{
	bool	hit;

	hit = false;
	while (array->type)
	{
		if (hit_objects(array, ray, rec))
			hit = true;
		array++;
	}
	return (hit);
}

bool	in_shadow(t_hit_array *objs, t_ray light_ray, double light_len)
{
	t_hit_record	rec;

	rec.tmin = 0;
	rec.tmax = light_len;
	if (hit_shadow(objs, &light_ray, &rec))
		return (true);
	return (false);
}

t_color	phong_lighting(t_scene *scene)
{
	t_color		l_color;
	t_hit_array	*lights_array;

	l_color = new_color(0, 0, 0);
	lights_array = scene->world;
	while (lights_array->type)
	{
		if (lights_array->type == _light)
			l_color = \
			vec_add(l_color, point_light_get(scene, lights_array));
		lights_array++;
	}
	l_color = vec_add(l_color, scene->ambient);
	return (vec_cmp(vec_mul_(l_color, scene->rec.color), new_color(1, 1, 1)));
}

t_color	point_light_get(t_scene *scene, t_hit_array *light)
{
	t_color		diffuse;
	t_vector	light_dir;
	t_color		specular;
	double		light_len;
	t_ray		light_ray;

	light_dir = vec_sub(light->center, scene->rec.p);
	light_len = vec_len(light_dir);
	light_ray = \
	ray(vec_add(scene->rec.p, vec_mul(scene->rec.normal, 0.000001)), light_dir);
	if (in_shadow(scene->world, light_ray, light_len))
		return (new_color(0, 0, 0));
	light_dir = unit_vec(light_dir);
	diffuse = \
	vec_mul(light->color, fmax(vec_dot(scene->rec.normal, light_dir), 0.0));
	specular = vec_mul(vec_mul(light->color, 0.5), \
	pow(fmax(vec_dot(unit_vec(vec_mul(scene->ray.dir, -1)), \
	reflect(vec_mul(light_dir, -1), scene->rec.normal)), 0.0), 64));
	return (vec_div(vec_mul(vec_add(vec_add(\
	scene->ambient, diffuse), specular), \
	light->bright_ratio * 3), (scene->rec.t * scene->rec.t) * 0.05));
}
