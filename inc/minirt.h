/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 12:05:42 by chajung           #+#    #+#             */
/*   Updated: 2023/04/23 12:05:43 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

/* renewal */

# include "mlx.h"
# include "structure.h"
# include "../libft/inc/libft.h"

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <math.h>
# include <time.h>

/* init */
void		initialize(int argc, char **argv, t_mlx *mlx);

/* hooks */
void		set_hooks(t_mlx *mlx);

/* utils */
void		exit_with_str(const char *str, int exit_code);

/* color */
void	color_window(t_mlx *mlx);

/* sphere */
t_sphere	sphere(t_point3 center, double radius);
t_bool		hit_sphere(t_sphere *sp, t_ray *ray, t_hit_record *rec);

/* cal */
t_vec3		vec3(double x, double y, double z);
t_point3	point3(double x, double y, double z);
t_point3	color3(double r, double g, double b);
void		vset(t_vec3 *vec, double x, double y, double z);
double		vlength2(t_vec3 vec);
double		vlength(t_vec3 vec);
t_vec3		vplus(t_vec3 vec, t_vec3 vec2);
t_vec3		vplus_(t_vec3 vec, double x, double y, double z);
t_vec3		vminus(t_vec3 vec, t_vec3 vec2);
t_vec3		vminus_(t_vec3 vec, double x, double y, double z);
t_vec3		vmult(t_vec3 vec, double t);
t_vec3		vmult_(t_vec3 vec, t_vec3 vec2);
t_vec3		vdivide(t_vec3 vec, double t);
double		vdot(t_vec3 vec, t_vec3 vec2);
t_vec3		vcross(t_vec3 vec, t_vec3 vec2);
t_vec3		vunit(t_vec3 vec);
t_vec3		vmin(t_vec3 vec1, t_vec3 vec2);
t_ray		ray(t_point3 orig, t_vec3 dir);
t_point3	ray_at(t_ray *ray, double t);

/* renewal */

// # include <stdio.h>
// # include <unistd.h>
// # include <stdlib.h>
// # include <stdbool.h>
// # include <fcntl.h>
// # include <math.h>
// # include <mlx.h>
// # include <time.h>
// # include "structure.h"
// # include "../libft/inc/libft.h"

// int check_input(int argc, char **argv);

// void	check_face_normal(void *this, t_ray ray, t_vector outward_normal);
// bool	hit_hittable_list(void *this, t_hitarg arg);

// /* init */
// void		initialize(int argc, char **argv, t_mlx *mlx);

// /* color */
// void	color_each_pixel(t_img *img, int x, int y, int color);
// int		_get_color(t_vector vec);
// t_vector	__get_color_vec(t_ray *ray, t_hittable *world, int depth);
// t_ray	__get_color_ray(void *this, double u, double v);
// void	color_pixels(t_mlx *mlx);
// void	color_window(t_mlx *mlx);

// /* sphere */
// bool	hit_sphere(void *this, t_hitarg arg);

// /* plane */
// bool	hit_plane(void *this, t_hitarg arg);

// /* cylinder */
// bool	hit_cylinder(void *this, t_hitarg arg);

// /* random */
// double		drandom48(void);
// t_vector	random_in_hemisphere(t_vector normal);
// t_vector	random_unit_vecter(void);
// t_vector	random_in_unit_sphere(void);

// /* scatter */
// bool	scatter_lambertian(void *this, t_material_arg arg);
// bool	scatter_metal(void *this, struct s_material_arg arg);

// /* calculate */
// double		size_vec(t_vector vec);
// t_vector	new_vec(double x, double y, double z);
// t_ray		new_ray(t_vector org, t_vector dir);
// t_vector	unit_vec(t_vector vec);
// t_vector	cal_add_vec(t_vector vec_1, t_vector vec_2);
// t_vector	cal_add3_vec(t_vector vec_1, t_vector vec_2, t_vector vec_3);
// t_vector	cal_subtract_vec(t_vector vec_1, t_vector vec_2);
// t_vector	cal_inverse_vec(t_vector vec);
// t_vector	cal_multiply_vec(t_vector vec, double ratio);
// t_vector	cal_multi_vec(t_vector vec_1, t_vector vec_2);
// t_vector	cal_divide_vec(t_vector vec, double ratio);
// t_vector	cal_arithmetic_vec(t_vector vec_1, t_vector vec_2, double ratio);
// t_vector	cal_ray(t_ray ray, double ratio);
// double		cal_inner_vec(t_vector vec_1, t_vector vec_2);
// t_vector	cal_outer_vec(t_vector vec_1, t_vector vec_2);

// /* hooks */
// void		set_hooks(t_mlx *mlx);

// /* utils */
// void		exit_with_str(const char *str, int exit_code);

#endif
