/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mygo <mygo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 15:29:31 by mygo              #+#    #+#             */
/*   Updated: 2023/05/21 15:29:32 by mygo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	ray_primary(t_camera *cam, double u, double v)
{
	t_ray		ray;
	t_point		viewport_point;

	ray.org = cam->org;
	viewport_point = vec_add( vec_add(cam->left_bottom, \
	vec_mul(cam->right_normal, u)), vec_mul(cam->up_normal, v));
	ray.dir = unit_vec(vec_sub(viewport_point, ray.org));
	return (ray);
}

t_color	ray_color(t_ray *ray, t_hit_array *array)
{
	t_hit_record	rec;
	t_vector		n;
	double			t;

	rec.tmin = 0.00000001;
	rec.tmax = MAXFLOAT;
	if (hit_world(array, ray, &rec))
		return (vec_mul(vec_add(rec.normal, new_color(1, 1, 1)), 0.5));
	else
	{
		t = 0.5 * (ray->dir.y + 1.0);
		return (vec_add(vec_mul(new_color(1, 1, 1), 1.0 - t), \
		vec_mul(new_color(0.5, 0.7, 1.0), t)));
	}
}

void	color_each_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->data_addr + (y * img->size_line + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	write_color(t_color pixel_color)
{
	return (((int)(255.999 * pixel_color.x) << 16) + \
	((int)(255.999 * pixel_color.y) << 8) + (int)(255.999 * pixel_color.z));
}

void	color_pixels(t_mlx *mlx, t_hit_array *array)
{
	int			i;
	int			j;
	t_color		pixel_color;
	t_camera	cam;
	t_ray		ray;

	cam = camera(new_point(0, 0, 5), new_point(0, 0, -1), 90);
	j = WIN_HEIGHT - 1;
	while (j >= 0)
	{
		i = 0;
		while (i < WIN_WIDTH)
		{
			ray = ray_primary(&cam, i, j);
			pixel_color = ray_color(&ray, array);
			color_each_pixel(&mlx->img, i, (WIN_HEIGHT - 1 - j), write_color(pixel_color));
			++i;
		}
		--j;
	}
}

void	color_window(t_mlx *mlx, t_hit_array *array)
{
	mlx_clear_window(mlx->mlx_ptr, mlx->win_ptr);
	color_pixels(mlx, array);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.img_ptr, 0, 0);
}

// int	_get_color(t_vector vec)
// {
// 	return (((int)(255.999 * vec.x) << 16) + ((int)(255.999 * vec.y) << 8) + (int)(255.999 * vec.z));
// }

// /* ray_color */
// t_vector	__get_color_vec(t_ray *ray, t_hittable *world, int depth)
// {
// 	t_hit_record	rec;
// 	t_vector		unit_vector;
// 	double			t;
// 	t_hitarg 		hit_arg;
// 	t_ray			__ray;

// 	if (depth <= 0)
// 		return (new_vec(0.0, 0.0, 0.0));

// 	hit_arg.ray = ray;
// 	hit_arg.min = 0.00000001;
// 	hit_arg.max = MAXFLOAT;
// 	hit_arg.max = __DBL_MAX__;
// 	hit_arg.rec = &rec;
// 	rec.set_face_normal = check_face_normal;

// 	if (world->hit(world, hit_arg))
// 	{
// 		t_ray			scattered;
// 		t_vector		attenuation;
// 		t_material_arg	mat_arg;

// 		mat_arg.ray_in = ray;
// 		mat_arg.rec = &rec;
// 		mat_arg.attenuation = &attenuation;
// 		mat_arg.scattered = &scattered;
// 		if (rec.mat_ptr->scatter(rec.mat_ptr, mat_arg))
// 			return (cal_multi_vec(attenuation, __get_color_vec(&scattered, world, depth - 1)));
// 		return (new_vec(0.0, 0.0, 0.0));
// 	}
// 	unit_vector = unit_vec(ray->dir);
// 	t = 0.5 * ((unit_vector.y) + 1.0);
// 	unit_vector = new_vec(1.0 - 0.5 * t, 1.0 - 0.3 * t, 1.0);
// 	return (unit_vector);
// }

// t_ray	__get_color_ray(void *this, double u, double v)
// {
// 	t_camera	camera;
// 	t_ray		ray;

// 	camera = *(t_camera *)this;
// 	camera.lower_left_corner = new_vec(-2.0, -1.0, -1.0);
// 	camera.horizontal = new_vec(4.0, 0.0, 0.0);
// 	camera.vertical = new_vec(0.0, 2.0, 0.0);
// 	camera.orgin = new_vec(0.0, 0.0, 0.0);

// 	ray.org = camera.orgin;
// 	ray.dir = cal_subtract_vec(cal_add_vec(cal_add_vec(camera.lower_left_corner, \
// 	cal_multiply_vec(camera.horizontal, u)), \
// 	cal_multiply_vec(camera.vertical, v)), camera.orgin);
// 	return (ray);
// }

// void	color_pixels(t_mlx *mlx)
// {
// 	int 		x;
// 	int		 	y;
// 	t_vector	color;
// 	t_ray		color_ray;

// 	t_camera	cam;
// 	cam._get_ray = __get_color_ray;
// 	srand(time(NULL));

// 	t_lambertian	*lam[2];
// 	t_metal			*met[2];

// 	lam[0] = &(t_lambertian){scatter_lambertian, new_vec(0.8, 0.8, 0.0)};
// 	lam[1] = &(t_lambertian){scatter_lambertian, new_vec(0.7, 0.3, 0.3)};
// 	met[0] = &(t_metal){scatter_metal, new_vec(0.8, 0.8, 0.8)};
// 	met[1] = &(t_metal){scatter_metal, new_vec(0.8, 0.6, 0.2)};

// 	// t_hittable	*list[4];
// 	// t_hittable	*world = &(t_hittable_list){hit_hittable_list, list, 4};
// 	// list[0] = &(t_sphere){hit_sphere, {0.0, -100.5, -1.0}, 100.0, lam[0]};
// 	// list[1] = &(t_sphere){hit_sphere, {0.0, 0.0, -1.0}, 0.5, lam[1]};
// 	// list[2] = &(t_sphere){hit_sphere, {-1.0, 0.0, -1.0}, 0.5, met[0]};
// 	// list[3] = &(t_sphere){hit_sphere, {1.0, 0.0, -1.0}, 0.5, met[1]};

// 	t_hittable	*list[1];
// 	t_hittable	*world = &(t_hittable_list){hit_hittable_list, list, 1};
// 	list[0] = &(t_plane){hit_plane, {0.0, 0.0, -1.0}, {1.0, 1.0, 1.0}, lam[0]};

// 	// 	t_lambertian	*lam[2];
// 	// 	t_metal			*met[2];

// 	// 	lam[0] = &(t_lambertian){scatter_lambertian, new_vec(0.8, 0.8, 0.0)};
// 	// 	lam[1] = &(t_lambertian){scatter_lambertian, new_vec(0.7, 0.3, 0.3)};
// 	// 	met[0] = &(t_metal){scatter_metal, new_vec(0.8, 0.8, 0.8)};
// 	// 	met[1] = &(t_metal){scatter_metal, new_vec(0.8, 0.6, 0.2)};

// 	// 	t_hittable	*list[2];
// 	// 	t_hittable	*world = &(t_hittable_list){hit_hittable_list, list, 2};
// 	// 	list[0] = &(t_cylinder){hit_cylinder, {0.0, -0.5, -2.0}, {0.0, 1.0, 0.0}, 0.4, 1.0, met[1]};
// 	// 	list[1] = &(t_plane){hit_plane, {0.0, 0.0, -2.0}, {0.0, 1.0, 1.0}, lam[1]};

// 	// 	// list[0] = &(t_plane){hit_plane, {0.0, -0.2, -3.0}, {0.9, -0.5, 0.7}, met[1]};
// 	// 	// list[0] = &(t_plane){hit_plane, {0.0, -0.2, -3.0}, {0.9, -0.5, 0.7}, 1.0, met[1]};

// 	// 	// list[1] = &(t_sphere){hit_sphere, {0.0, 0.0, -1.0}, 0.5, lam[1]};
// 	// 	// list[2] = &(t_sphere){hit_sphere, {-1.0, 0.0, -1.0}, 0.5, met[0]};
// 	// 	// list[3] = &(t_sphere){hit_sphere, {1.0, 0.0, -1.0}, 0.5, met[1]};
// 	// 	// list[4] = &(t_sphere){hit_sphere, {1.0, 0.0, -1.0}, 0.5, met[1]};

// 	y = 0;
// 	while (y < (WIN_HEIGHT + 1))
// 	{
// 		x = 0;
// 		while (x < WIN_WIDTH + 1)
// 		{
// 			color = new_vec(0.0, 0.0, 0.0);
// 			for (int s = 0; s < CAMERA_NS; s++) {
// 				double u = ((double)x + drandom48()) / (double)WIN_WIDTH;
// 				double v = ((double)y + drandom48()) / (double)WIN_HEIGHT;

// 				t_ray	ray = cam._get_ray(&cam, u, v);
// 				t_vector p = cal_ray(ray, 2.0);
// 				// color = cal_add_vec(color, __get_color_vec(&ray, world)); // Chapter 7
// 				color = cal_add_vec(color, __get_color_vec(&ray, world, 50)); // Chapter 8
// 			}
// 			color = cal_divide_vec(color, (double)CAMERA_NS);
// 			color = new_vec(sqrt(color.x), sqrt(color.y), sqrt(color.z));
// 			// color_ray = __get_color_ray(x, y);
// 			// color = __get_color_vec(&color_ray);
// 			color_each_pixel(&mlx->img, x, y, _get_color(color));
// 			x++;
// 		}
// 		y++;
// 	}
// }
