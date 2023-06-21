/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:47:56 by chajung           #+#    #+#             */
/*   Updated: 2023/05/22 13:47:57 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CALCULATE_H
# define CALCULATE_H

typedef struct s_vector	t_vector;
typedef struct s_vector	t_point;
typedef struct s_vector	t_color;
typedef struct s_ray	t_ray;

struct s_vector
{
	double	x;
	double	y;
	double	z;
};

struct	s_ray
{
	t_point		org;
	t_vector	dir;
};

/* cal0 */
t_vector	new_vec(double x, double y, double z);
t_point		new_point(double x, double y, double z);
t_point		new_color(double r, double g, double b);
t_ray		ray(t_point org, t_vector dir);
t_point		ray_at(t_ray *ray, double t);

/* cal1 */
t_vector	vec_add(t_vector vec, t_vector vec2);
t_vector	vec_sub(t_vector vec, t_vector vec2);
t_vector	vec_mul(t_vector vec, double t);
t_vector	vec_mul_(t_vector vec, t_vector vec2);
t_vector	vec_div(t_vector vec, double t);

/* cal2 */
double		vec_len(t_vector vec);
double		vec_dot(t_vector vec, t_vector vec2);
t_vector	vec_prod(t_vector vec, t_vector vec2);
t_vector	unit_vec(t_vector vec);
t_vector	vec_cmp(t_vector vec1, t_vector vec2);

#endif
