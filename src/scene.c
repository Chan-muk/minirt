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

t_camera	camera(t_point org, t_vector dir, double fov)
{
	t_camera	cam;
	t_vector	vec_y;
	t_vector	vec_z;
	t_vector	temp;

	vec_y = new_vec(0.0, 1.0, 0.0);
	vec_z = new_vec(0.0, 0.0, -1.0);
	cam.org = org;
	cam.dir = dir;
	cam.fov = fov;
	if (vec_len(vec_prod(vec_y, cam.dir)))
		cam.right_normal = unit_vec(vec_prod(cam.dir, vec_y));
	else 
		cam.right_normal = unit_vec(vec_prod(cam.dir, vec_z)); // seg
	cam.up_normal = unit_vec(vec_prod(cam.right_normal, cam.dir));
	cam.focal_len = (double)(WIN_WIDTH * 0.5) / tan((cam.fov * 0.5) * (M_PI / 180));
	temp = vec_add(cam.org, vec_mul(cam.dir, cam.focal_len));
	temp = vec_sub(temp, vec_mul(cam.right_normal, (double)(WIN_WIDTH - 1) * 0.5));
	temp = vec_sub(temp, vec_mul(cam.up_normal, (double)(WIN_HEIGHT - 1) * 0.5));
	cam.left_bottom = temp;
	return (cam);
}

void	set_scene(t_scene *scene)
{
	scene->cam = camera(scene->cam_org, scene->cam_dir, scene->cam_fov);
	scene->rec.tmin = 0.00000001;
	scene->rec.tmax = MAXFLOAT;
}


// void	__set_camera(t_scene *scene)
// {
// 	// t_camera	cam;
// 	t_vector	vec_y;
// 	t_vector	vec_z;
// 	t_vector	temp;

// 	printf("here\n");
// 	// printf("pnt x: %f, y: %f, z: %f\n", (scene->cam.org).x, (scene->cam.org).y, (scene->cam.org).z);
// 	// printf("nor x: %f, y: %f, z: %f\n", (scene->cam.dir).x, (scene->cam.dir).y, (scene->cam.dir).z);
// 	// printf("fov %f\n", scene->cam.fov);

// 	printf("here\n");

// 	vec_y = new_vec(0.0, 1.0, 0.0);
// 	vec_z = new_vec(0.0, 0.0, -1.0);
// 	// cam.org = org;
// 	// cam.dir = dir;
// 	// cam.fov = fov;
// 	if (vec_len(vec_prod(vec_y, scene->cam.dir)))
// 		scene->cam.right_normal = unit_vec(vec_prod(scene->cam.dir, vec_y));
// 	else 
// 		scene->cam.right_normal = unit_vec(vec_prod(scene->cam.dir, vec_z));
// 	scene->cam.up_normal = unit_vec(vec_prod(scene->cam.right_normal, scene->cam.dir));
// 	scene->cam.focal_len = (double)(WIN_WIDTH * 0.5) / tan((scene->cam.fov * 0.5) * (M_PI / 180));
// 	temp = vec_add(scene->cam.org, vec_mul(scene->cam.dir, scene->cam.focal_len));
// 	temp = vec_sub(temp, vec_mul(scene->cam.right_normal, (double)(WIN_WIDTH - 1) * 0.5));
// 	temp = vec_sub(temp, vec_mul(scene->cam.up_normal, (double)(WIN_HEIGHT - 1) * 0.5));
// 	scene->cam.left_bottom = temp;
// 	// return (cam);
// }

// void	set_scene(t_scene *scene)
// {
// 	// double	lighting_ratio;

// 	// scene->cam = camera(new_point(0, 0, 0), new_vec(0, 0, -1), 120);
// 	// scene->cam = camera(scene->cam.org, scene->cam.dir, scene->cam.fov);
// 	// printf("seg test\n");
// 	__set_camera(scene);
// 	// printf("seg test\n");
// 	// set_objects(scene->world);
// 	scene->rec.tmin = 0.00000001;
// 	scene->rec.tmax = MAXFLOAT;
// 	// set_lights(scene->light);
// 	// lighting_ratio = 0.1;
// 	// scene->ambient = vec_mul(new_color(1, 1, 1), lighting_ratio);
// }

// void	set_scene(t_scene *scene)
// {
// 	// double	lighting_ratio;

// 	// printf("pnt x: %f, y: %f, z: %f\n", (scene->cam_org).x, (scene->cam_org).y, (scene->cam_org).z);
// 	// printf("nor x: %f, y: %f, z: %f\n", (scene->cam_dir).x, (scene->cam_dir).y, (scene->cam_dir).z);
// 	// printf("fov %f\n", scene->cam_fov);


// 	// scene->cam = camera(new_point(0, 0, 0), new_vec(0, 0, -1), 120);
// 	scene->cam = camera(scene->cam_org, scene->cam_dir, scene->cam_fov);
// 	// set_objects(scene->world);
// 	scene->rec.tmin = 0.00000001;
// 	scene->rec.tmax = MAXFLOAT;
// 	// set_lights(scene->light);
// 	// lighting_ratio = 0.1;
// 	// scene->ambient = vec_mul(new_color(1, 1, 1), lighting_ratio);
// }
