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

typedef struct s_camera t_camera;
typedef struct s_canvas t_canvas;

struct	s_camera
{
	t_point		org;  // 카메라 원점(위치)
	double		viewport_h; // 뷰포트 세로길이
	double		viewport_w; // 뷰포트 가로길이
	t_vector	horizontal; // 수평길이 벡터
	t_vector	vertical; // 수직길이 벡터
	double		focal_len; // focal length
	t_point		left_bottom; // 왼쪽 아래 코너점
};

struct	s_canvas
{
	int		width; //canvas width
	int		height; //canvas height;
	double	aspect_ratio; //종횡비
};

t_canvas	canvas(int	width, int height);
t_camera	camera(t_canvas *canvas, t_point org);

#endif
