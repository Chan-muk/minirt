/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 12:04:41 by chajung           #+#    #+#             */
/*   Updated: 2023/04/23 12:04:42 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	color_each_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	y = WIN_HEIGHT - y;
	dst = img->data_addr + (x * img->bits_per_pixel / 8) + (y * img->size_line);
	*(unsigned int *)dst = color;
}

// bool __hit_sphere(t_vector center, double radius, t_ray ray, double min, double max, t_hit_record *rec)
bool	hit_sphere(void *this, t_hitarg arg)
{
	t_sphere	*sphere;
	t_vector	r_center;
	double		a;
	double		b;
	double		c;
	double		discriminant;
	double		temp;

	sphere = (t_sphere *)this;
	r_center = cal_subtract_vec(arg.ray->org, sphere->center);
	a = cal_inner_vec(arg.ray->dir, arg.ray->dir);
	b = cal_inner_vec(r_center, arg.ray->dir);
	c = cal_inner_vec(r_center, r_center) - (sphere->radius * sphere->radius);
	discriminant = (b * b) - (a * c);
	if (discriminant > 0)
	{
		temp = (-b - sqrt(discriminant)) / a;
		if (temp < arg.max && temp > arg.min)
		{
			arg.rec->t = temp;
			arg.rec->p = cal_ray(*arg.ray, arg.rec->t);
			arg.rec->normal = cal_divide_vec(cal_subtract_vec(arg.rec->p, sphere->center), sphere->radius);
			return (true);
		}
		temp = (-b + sqrt(discriminant)) / a;
		if (temp < arg.max && temp > arg.min)
		{
			arg.rec->t = temp;
			arg.rec->p = cal_ray(*arg.ray, arg.rec->t);
			arg.rec->normal = cal_divide_vec(cal_subtract_vec(arg.rec->p, sphere->center), sphere->radius);
			return (true);
		}
	}
	return (false);
}

bool	hit_hitable_list(void *this, t_hitarg arg)
{
	t_hitable_list	*world;
	t_hit_record	temp_rec;
	bool			hit_anything;
	t_hitarg		temp_arg;

	world = (t_hitable_list *)this;
	hit_anything = false;
	temp_arg = arg;
	temp_arg.rec = &temp_rec;
	for (int i = 0; i < world->list_size; i++)
	{
		if (world->list[i]->hit(world->list[i], temp_arg))
		{
			hit_anything = true;
			temp_arg.max = temp_rec.t;
			*arg.rec = temp_rec;
		}
	}
	return (hit_anything);
}

t_vector	color(t_ray *ray, t_hitable *world)
{
	t_hit_record	rec;
	t_vector		unit_vector;
	double			t;
	t_hitarg 		arg;

	arg.ray = ray;
	arg.min = 0.0;
	arg.max = MAXFLOAT;
	arg.rec = &rec;
	if (world->hit(world, arg))
	{
		unit_vector = cal_arithmetic_vec(rec.normal ,new_vec(1.0, 1.0, 1.0), 0.5);
	}
	else
	{
		unit_vector = unit_vec(ray->dir);
		t = 0.5 * ((unit_vector.y) + 1.0);
		unit_vector.x = ((1.0 - t) * 1.0) + (t * 0.5);
		unit_vector.y = ((1.0 - t) * 1.0) + (t * 0.7);
		unit_vector.z = ((1.0 - t) * 1.0) + (t * 1.0);
	}
	return (unit_vector);
}

t_ray	get_ray(double x, double y)
{
	t_ray		ray;
	t_vector	lower_left_corner;
	t_vector	horizontal;
	t_vector	vertical;
	t_vector	origin;

	double		u;
	double		v;

	u = x / (double)WIN_WIDTH;
	v = y / (double)WIN_HEIGHT;

	lower_left_corner = new_vec(-2.0, -1.0, -1.0);
	horizontal = new_vec(4.0, 0.0, 0.0);
	vertical = new_vec(0.0, 2.0, 0.0);
	origin = new_vec(0.0, 0.0, 0.0);

	ray = new_ray(new_vec(0.0, 0.0, 0.0), \
	new_vec(lower_left_corner.x + u * horizontal.x + v * vertical.x,
	lower_left_corner.y + u * horizontal.y + v * vertical.y,
	lower_left_corner.z + u * horizontal.z + v * vertical.z));
	return (ray);
}

t_ray	_get_ray(void *this, double u, double v)
{
	t_camera	camera;
	t_ray		ray;

	camera = *(t_camera *)this;
	camera.lower_left_corner = new_vec(-2.0, -1.0, -1.0);
	camera.horizontal = new_vec(2.0, 0.0, 0.0);
	camera.vertical = new_vec(0.0, 2.0, 0.0);
	camera.origin = new_vec(0.0, 0.0, 0.0);

	ray.org = camera.origin;
	ray.dir = cal_subtract_vec(cal_add_vec(cal_add_vec(camera.lower_left_corner, \
	cal_multiply_vec(camera.horizontal, u)), \
	cal_multiply_vec(camera.vertical, v)), camera.origin);
	return (ray);
}

double drandom48(void)
{
	return (double)rand() / (double)RAND_MAX;
}

void	color_pixels(t_mlx *mlx)
{
	// srand((unsigned int)time(NULL));
	srand(time(NULL));

	double		random;
	int 		x;
	int		 	y;
	int			result;
	t_ray 		ray;
	t_vector	vec;

	t_camera	cam;
	cam._get_ray = _get_ray;

	t_hitable	*list[2];
	t_hitable	*world = &(t_hitable_list){hit_hitable_list, list, 2};
	list[0] = &(t_sphere){hit_sphere, {0, 0, -1}, 0.5};
	list[1] = &(t_sphere){hit_sphere, {0, -100.5, -1}, 100};
	y = WIN_HEIGHT;
	while (y >= 0)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			t_vector	col = new_vec(0.0, 0.0, 0.0);
			for (int s = 0; s < CAMERA_NS; s++) {
				double u = ((double)x + drandom48()) / (double)CAMERA_NS;
				double v = ((double)y + drandom48()) / (double)CAMERA_NS;

				t_ray	ray = cam._get_ray(&cam, u, v);
				t_vector p = cal_ray(ray, 2.0);
				col = cal_add_vec(col, color(&ray, world));
			}
			col = cal_divide_vec(col, (double)CAMERA_NS);

			// ray = get_ray((double)x, (double)y);
			// vec = color(&ray, world);

			result = \
			(((int)(255.99 * col.x) << 16) + ((int)(255.99 * col.y) << 8) + (int)(255.99 * col.z));			
			// result = \
			// (((int)(255.99 * vec.x) << 16) + ((int)(255.99 * vec.y) << 8) + (int)(255.99 * vec.z));
			color_each_pixel(&mlx->img, x, y, result);
			x++;
		}
		y--;
	}
}

void	color_window(t_mlx *mlx)
{
	mlx_clear_window(mlx->mlx_ptr, mlx->win_ptr);
	color_pixels(mlx);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.img_ptr, 0, 0);
}

int	main(int argc, char **argv)
{
	t_mlx	mlx;

	// arguments_check(argc, argv, &mlx);
	initialize(argc, argv, &mlx);
	color_window(&mlx);
	set_hooks(&mlx);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}

