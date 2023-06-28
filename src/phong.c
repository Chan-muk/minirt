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
#include <fenv.h>

t_vector	reflect(t_vector v, t_vector n)
{
	return (vec_sub(v, vec_mul(n, vec_dot(v, n) * 2)));
}

t_color	get_specular(t_scene *scene, t_hit_array *light)
{
	t_vector	light_dir;
	t_vector	view_dir;
	t_vector	reflect_dir;
	double		spec;

	light_dir = unit_vec(vec_sub(light->center, scene->rec.p));
	view_dir = unit_vec(vec_mul(scene->ray.dir, -1));
	reflect_dir = reflect(vec_mul(light_dir, -1), scene->rec.normal);
	spec = pow(fmax(vec_dot(view_dir, reflect_dir), 0.0), (double)KSN);
	return (vec_mul(vec_mul(light->color, (double)KS), spec));
}

t_color	point_light_get(t_scene *scene, t_hit_array *light)
{
	t_vector	light_dir;
	t_color		diffuse;
	t_color		specular;
	double		brightness;
	t_ray		light_ray;

	light_dir = vec_sub(light->center, scene->rec.p);
	light_ray = ray(vec_add(scene->rec.p, vec_mul(scene->rec.normal, EPSILON)), \
	unit_vec(light_dir));
	if (in_shadow(scene->world, light_ray, vec_len(light_dir)))
		return (new_color(0.0, 0.0, 0.0));
	light_dir = unit_vec(light_dir);
	diffuse = \
	vec_mul(light->color, fmax(vec_dot(scene->rec.normal, light_dir), 0.0));
	specular = get_specular(scene, light);
	brightness = light->bright_ratio * (double)LUMEN;
	return (vec_mul(vec_add(diffuse, specular), brightness));
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
