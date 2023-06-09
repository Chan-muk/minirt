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
	if (rec->front_face == true)
		rec->normal = rec->normal;
	else
		rec->normal = vec_mul(rec->normal, -1);
}

bool	hit_world(t_hitarr *arr, t_ray *r, t_hit_record *rec)
{
	bool	(*hit_objs[total])(t_hitarr* arr, t_ray *r, t_hit_record *rec);
	int	hit;

	hit = 0;
	// set_hitobjs(hit_objs);
	hit_objs[sp] = hit_sphere;
	while (arr->type)
	{
		if (hit_objs[arr->type](arr, r, rec))
		{
			hit = 1;
			rec->tmax = rec->t;
		}
		arr++;
	}
	return (hit);
}

// void	check_face_normal(void *this, t_ray ray, t_vector outward_normal)
// {
// 	t_hit_record	*rec;

// 	rec = (t_hit_record *)this;
// 	if (vec_dot(ray.dir, outward_normal) > 0.0)
// 	{
// 		rec->normal = cal_inverse_vec(outward_normal);
// 		rec->front_face = false;
// 	}
// 	else
// 	{
// 		rec->normal = outward_normal;
// 		rec->front_face = true;
// 	}
// }

// bool	hit_hittable_list(void *this, t_hitarg arg)
// {
// 	t_hittable_list	*world;
// 	t_hit_record	temp_rec;
// 	bool			hit_anything;
// 	t_hitarg		temp_arg;
// 	int				index;

// 	world = (t_hittable_list *)this;
// 	hit_anything = false;
// 	temp_arg = arg;
// 	temp_arg.rec = &temp_rec;
// 	temp_rec.set_face_normal = check_face_normal;
// 	index = -1;
// 	while (++index < world->list_size)
// 	{
// 		if (world->list[index]->hit(world->list[index], temp_arg))
// 		{
// 			hit_anything = true;
// 			temp_arg.max = temp_rec.t;
// 			*arg.rec = temp_rec;
// 		}
// 	}
// 	return (hit_anything);
// }
