/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 10:50:27 by chajung           #+#    #+#             */
/*   Updated: 2023/05/26 10:50:28 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	hit_plane(t_hit_array* pl, t_ray *ray, t_hit_record *rec)
{
	double	numrator;
	double	denominator;
	double	root;

	denominator = vec_dot(ray->dir, pl->norm);
	if (fabs(denominator) < rec->tmin)
		return (false);
	numrator = vec_dot(vec_sub(pl->center, ray->org), pl->norm);
	root = numrator / denominator;
	if (root < rec->tmin || root > rec->tmax)
		return (false);
	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->normal = pl->norm;
	set_face_normal(ray, rec);
	rec->albedo = pl->albedo;
	return (true);
}
