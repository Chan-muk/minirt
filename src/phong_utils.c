/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 13:01:26 by chajung           #+#    #+#             */
/*   Updated: 2023/06/26 13:01:27 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	hit_shadow(t_hit_array *array, t_ray *ray, t_hit_record *rec)
{
	int	hit;

	hit = false;
	while (array->type)
	{
		if (hit_objects(array, ray, rec))
			hit = true;
		array++;
	}
	return (hit);
}

int	in_shadow(t_hit_array *objs, t_ray light_ray, double light_len)
{
	t_hit_record	rec;

	rec.tmin = 0;
	rec.tmax = light_len;
	if (hit_shadow(objs, &light_ray, &rec))
		return (true);
	return (false);
}
