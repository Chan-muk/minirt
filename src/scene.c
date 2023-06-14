/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 10:48:29 by chajung           #+#    #+#             */
/*   Updated: 2023/06/10 10:48:30 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	get_tan(double degree)
{
	return (tan(degree * (M_PI / 180)));
}

t_canvas	canvas(int	width, int height)
{
	t_canvas canvas;

	canvas.width = width;
	canvas.height = height;
	canvas.aspect_ratio = (double)width / (double)height;
	return (canvas);
}

// t_camera	camera(t_canvas *canvas, t_point org)
// {
// 	t_camera	cam;
// 	double		focal_len;
// 	double		viewport_height;

// 	viewport_height = 2.0;
// 	focal_len = 1.0;
// 	cam.org = org;
// 	cam.viewport_h = viewport_height;
// 	cam.viewport_w = viewport_height * canvas->aspect_ratio;
// 	cam.focal_len = focal_len;
// 	cam.horizontal = new_vec(cam.viewport_w, 0, 0);
// 	cam.vertical = new_vec(0, cam.viewport_h, 0);
// 	cam.left_bottom = vec_sub(vec_sub(vec_sub(cam.org, vec_div(cam.horizontal, 2)), vec_div(cam.vertical, 2)), new_vec(0, 0, focal_len));
// 	return (cam);
// }

t_camera	camera(t_point org, t_vector dir)
{
	t_camera	cam;
	t_vector	vec_y;
	t_vector	vec_z;
	t_vector	temp;

	vec_y = new_vec(0.0, 1.0, 0.0);
	vec_z = new_vec(0.0, 0.0, -1.0);

	cam.org = org;
	cam.dir = dir;
	cam.fov = 90;
	if (vec_len(vec_prod(vec_y, cam.dir)))
		cam.right_normal = unit_vec(vec_prod(cam.dir, vec_y));
	else 
		cam.right_normal = unit_vec(vec_prod(cam.dir, vec_z));
	cam.up_normal = unit_vec(vec_prod(cam.right_normal, cam.dir));
	cam.focal_len = (double)(WIN_WIDTH * 0.5) / get_tan(cam.fov * 0.5);

	temp = vec_add(cam.org, vec_mul(cam.dir, cam.focal_len));
	temp = vec_sub(temp, vec_mul(cam.right_normal, (double)(WIN_WIDTH - 1) * 0.5));
	temp = vec_sub(temp, vec_mul(cam.up_normal, (double)(WIN_HEIGHT - 1) * 0.5));
	cam.left_bottom = temp;
	// print_vec(cam.right_normal);
	// print_vec(cam.up_normal);
	// print_vec(cam.left_bottom);
	return (cam);
}