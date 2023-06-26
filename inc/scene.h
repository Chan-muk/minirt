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

typedef struct s_img		t_img;
typedef struct s_mlx		t_mlx;
typedef struct s_camera		t_camera;
typedef struct s_scene		t_scene;
typedef struct s_bmpheader	t_bmpheader;

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

struct	s_camera
{
	t_point		org;
	t_vector	dir;
	t_vector	right_normal;
	t_vector	up_normal;
	t_point		left_bottom;
	double		fov;
	double		focal_len;
};

struct	s_scene
{
	t_camera		cam;
	t_point			cam_org;
	t_vector		cam_dir;
	double			cam_fov;
	t_hit_array		*world;
	t_color			ambient;
	t_ray			ray;
	t_hit_record	rec;
	double			ambient_ratio;
	t_color			color;
};

/* scene */
t_camera	camera(t_point org, t_vector dir, double fov);
void		set_scene(t_scene *scene);

/* color */
void		color_window(t_mlx *mlx, t_scene *scene);

/* color_utils */
void		color_each_pixel(t_img *img, int x, int y, int color);
int			write_color(t_color pixel_color);

/* phong */
t_color		phong_lighting(t_scene *scene);

/* phong_utils */
bool		in_shadow(t_hit_array *objs, t_ray light_ray, double light_len);

/* texture */
void		get_bmp_addr(char *path, t_images *img);
t_color		plane_texture(t_vector p, t_hit_array *pl);
t_color		shpere_texture(t_vector p, t_hit_array *sp);

/* bump */
void		shpere_bump(t_vector p, t_hit_array *sp, t_hit_record *rec);
void		plane_bump(t_vector p, t_hit_array *pl, t_hit_record *rec);

#endif
