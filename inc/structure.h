/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:47:56 by chajung           #+#    #+#             */
/*   Updated: 2023/05/22 13:47:57 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

# define EXIT_SUCCESS	0
# define EXIT_FAILURE	1
# define WIN_WIDTH		800
# define WIN_HEIGHT		400
# define CAMERA_NS		100
# define KEYPRESS		2
# define DESTROYNOTIFY	17
# define ESC			53
# define LEFT_CLICK		1
# define RIGHT_CLICK	2
# define MIDDLE_CLICK	3
# define SCROLL_UP		4
# define SCROLL_DOWN	5
# define UP				126
# define DOWN			125
# define LEFT			123
# define RIGHT			124
# define R_KEY			15

typedef struct s_img
{
	void	*img_ptr;
	char	*data_addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}	t_img;	

typedef struct s_mlx
{
	void			*mlx_ptr;
	void			*win_ptr;
	struct s_img	img;
}	t_mlx;

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

typedef struct s_ray
{
	struct s_vector	org;
	struct s_vector	dir;
}	t_ray;

typedef struct s_hit_record
{
	bool				(*set_face_normal)(void *this, struct s_ray ray, struct s_vector outward_normal);
	bool				front_face;
	double				t;
	struct s_vector		p;
	struct s_vector		normal;
	struct s_material	*mat_ptr;
}	t_hit_record;

typedef	struct s_hitarg
{
	struct s_ray		*ray;
	double				min;
	double				max;
	struct s_hit_record	*rec;
}	t_hitarg;

typedef struct s_sphere
{
	bool				(*hit)(void *this, struct s_hitarg arg);
	struct s_vector		center;
	double 				radius;
	struct s_material	*mat_ptr;
}	t_sphere;

typedef struct s_plain
{
	bool				(*hit)(void *this, struct s_hitarg arg);
	struct s_vector		center;
	struct s_vector		normal_vector;
	struct s_material	*mat_ptr;
}	t_plain;

typedef struct s_hittable
{
	bool		(*hit)(void *this, struct s_hitarg arg);
}	t_hittable;

typedef struct s_hittable_list
{
	bool				(*hit)(void *this, struct s_hitarg arg);
	struct s_hittable	**list;
	int					list_size;
}	t_hittable_list;

typedef struct s_camera
{
	struct s_vector	lower_left_corner;
	struct s_vector	horizontal;
	struct s_vector	vertical;
	struct s_vector	origin;
	t_ray			(*_get_ray)(void *this, double u, double v);
}	t_camera;

typedef	struct s_material_arg
{
	struct s_ray			*ray_in;
	struct s_hit_record		*rec;
	struct s_vector			*attenuation;
	struct s_ray			*scattered;
}	t_material_arg;

typedef struct s_material
{
	bool			(*scatter)(void *this, struct s_material_arg arg);
}	t_material;

typedef struct s_lambertian
{
	bool			(*scatter)(void *this, struct s_material_arg arg);
	struct s_vector	albedo;
}	t_lambertian;

typedef struct s_metal
{
	bool			(*scatter)(void *this, struct s_material_arg arg);
	struct s_vector	albedo;
}	t_metal;

#endif
