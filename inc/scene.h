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
typedef struct s_canvas	t_canvas;

enum e_type
{
	_end = 0,
	_plane,
	_sphere,
	_cylinder,
	_cone,
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
	double		viewport_h;
	double		viewport_w;
	t_vector	horizontal;
	t_vector	vertical;
	double		focal_len;
	t_point		left_bottom;
};

struct	s_canvas
{
	int		width;
	int		height;
	double	aspect_ratio;
};

/* scene */
t_canvas	canvas(int width, int height);
t_camera	camera(t_canvas *canvas, t_point org);

/* color */
void		color_window(t_mlx *mlx, t_hit_array *array);
#endif
