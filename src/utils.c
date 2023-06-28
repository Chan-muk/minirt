/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 08:57:27 by chajung           #+#    #+#             */
/*   Updated: 2023/05/01 08:57:28 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	fract(double x)
{
	return (x - floor(x));
}

int	check_object_height(t_hit_array *obj, t_ray *ray, double root)
{
	double	point_on_line;

	point_on_line = \
	vec_dot(vec_sub(vec_add(ray->org, vec_mul(ray->dir, root)), \
	obj->center), obj->norm);
	if (point_on_line < 0.0 || point_on_line > obj->height)
		return (false);
	return (true);
}

void	data_backup(t_hit_record *rec_backup, t_hit_record *rec)
{
	rec_backup->color = rec->color;
	rec_backup->front_face = rec->front_face;
	rec_backup->normal = rec->normal;
	rec_backup->p = rec->p;
	rec_backup->t = rec->t;
	rec_backup->tmax = rec->tmax;
	rec_backup->tmin = rec->tmin;
}

void	check_data(double root, int *flag, t_hit_record *rec, \
t_hit_record *rec_backup)
{
	if (*flag == true && rec_backup->t < rec->t)
		data_backup(rec, rec_backup);
	else
	{
		data_backup(rec_backup, rec);
		*flag = true;
	}
}

void	exit_with_str(const char *str, int exit_code)
{
	ft_putendl_fd("Error", STDERR_FILENO);
	ft_putendl_fd((char *)str, STDERR_FILENO);
	exit(exit_code);
}
