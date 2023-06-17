/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 10:48:41 by chajung           #+#    #+#             */
/*   Updated: 2023/06/10 10:48:42 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

typedef struct s_img	t_img;
typedef struct s_mlx	t_mlx;
typedef struct s_camera	t_camera;
typedef struct s_scene	t_scene;

enum e_type
{
	_end = 0,
	_plane,
	_sphere,
	_cylinder,
	_cone,
	_light,
	_total,
};

struct s_img
{
	void	*img_ptr;
	char	*data_addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
};

struct s_mlx
{
	void			*mlx_ptr;
	void			*win_ptr;
	struct s_img	img;
};

struct  s_camera
{
	t_point		org;
	t_vector	dir;
	t_vector	right_normal;
	t_vector	up_normal;
	t_point		left_bottom;
	double      fov;
	double      focal_len;
};

struct	s_scene
{
	t_camera		cam;
	t_hit_array		*world;
	t_hit_array		*light;
	t_vector		ambient; // 8.4에서 설명할 요소
	t_ray			ray;
	t_hit_record	rec;
};

/* scene */
t_camera	camera(t_point org, t_vector dir, double fov);
void		set_scene(t_scene *scene);

/* color */
void		color_window(t_mlx *mlx, t_scene *scene);

/* phong */
t_color		phong_lighting(t_scene *scene);
t_color		point_light_get(t_scene *scene, t_hit_array *light);
#endif
