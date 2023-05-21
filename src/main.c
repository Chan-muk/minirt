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

/* Chapter 8: Metal*/
bool	scatter_lambertian(void *this, struct s_material_arg arg)
{
	t_vector		target;
	t_ray			ray;
	t_lambertian	*lambertian;

	lambertian = (t_lambertian *)this;
	ray = new_ray(arg.rec->p, cal_subtract_vec(target, arg.rec->p));
	arg.scattered = &ray;
	arg.attenuation = &lambertian->albedo;
	return (true);
}

t_vector	reflect(t_vector vec_v, t_vector vec_n)
{
	return (cal_subtract_vec(vec_v, cal_multiply_vec(vec_n, (2 * cal_inner_vec(vec_v, vec_n)))));
}

bool	scatter_metal(void *this, struct s_material_arg arg)
{
	t_metal		*metal;
	t_vector	reflected;
	t_ray		ray;
	
	metal = (t_metal *)this;
	reflected = reflect(unit_vec(arg.ray_in->dir), arg.rec->normal);
	ray = new_ray(arg.rec->p, reflected);
	arg.scattered = &ray;
	arg.attenuation = &metal->albedo;
	if (cal_inner_vec(arg.scattered->dir, arg.rec->normal) > 0)
		return (true);
	else
		return (false);
}
/* Chapter 8: Metal*/

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

t_vector	__get_color_vec(t_ray *ray, t_hitable *world, int depth) //ray_color
{
	t_hit_record	rec;
	t_vector		unit_vector;
	double			t;
	t_hitarg 		arg;
	t_ray			__ray;

	if (depth <= 0)
		return (new_vec(0.0, 0.0, 0.0));

	arg.ray = ray;
	arg.min = 0.001;
	arg.max = MAXFLOAT;
	arg.rec = &rec;

	if (world->hit(world, arg))
	{
		__ray = new_ray(arg.rec->p, cal_subtract_vec(cal_add3_vec(arg.rec->p, arg.rec->normal, random_in_unit_sphere()), arg.rec->p));
		return (cal_multiply_vec(__get_color_vec(&__ray, world, (depth - 1)), 0.5));
	}
	unit_vector = unit_vec(ray->dir);
	t = 0.5 * ((unit_vector.y) + 1.0);
	unit_vector = new_vec(1.0 - 0.5 * t, 1.0 - 0.3 * t, 1.0);
	return (unit_vector);
}

t_ray	__get_color_ray(void *this, double u, double v)
{
	t_camera	camera;
	t_ray		ray;

	camera = *(t_camera *)this;
	camera.lower_left_corner = new_vec(-2.0, -1.0, -1.0);
	camera.horizontal = new_vec(4.0, 0.0, 0.0);
	camera.vertical = new_vec(0.0, 2.0, 0.0);
	camera.origin = new_vec(0.0, 0.0, 0.0);

	ray.org = camera.origin;
	ray.dir = cal_subtract_vec(cal_add_vec(cal_add_vec(camera.lower_left_corner, \
	cal_multiply_vec(camera.horizontal, u)), \
	cal_multiply_vec(camera.vertical, v)), camera.origin);
	return (ray);
}

void	color_pixels(t_mlx *mlx)
{
	int 		x;
	int		 	y;
	t_vector	color;
	t_ray		color_ray;

	t_camera	cam;
	cam._get_ray = __get_color_ray;
	srand(time(NULL));

	t_hitable	*list[2];
	t_hitable	*world = &(t_hitable_list){hit_hitable_list, list, 2};
	list[0] = &(t_sphere){hit_sphere, {0, 0, -1}, 0.5};
	list[1] = &(t_sphere){hit_sphere, {0, -100.5, -1}, 100};

	y = 0;
	while (y < (WIN_HEIGHT + 1))
	{
		x = 0;
		while (x < WIN_WIDTH + 1)
		{
			color = new_vec(0.0, 0.0, 0.0);
			for (int s = 0; s < CAMERA_NS; s++) {
				double u = ((double)x + drandom48()) / (double)WIN_WIDTH;
				double v = ((double)y + drandom48()) / (double)WIN_HEIGHT;

				t_ray	ray = cam._get_ray(&cam, u, v);
				t_vector p = cal_ray(ray, 2.0);
				// color = cal_add_vec(color, __get_color_vec(&ray, world)); // Chapter 7
				color = cal_add_vec(color, __get_color_vec(&ray, world, 50)); // Chapter 8
			}
			color = cal_divide_vec(color, (double)CAMERA_NS);
			color = new_vec(sqrt(color.x), sqrt(color.y), sqrt(color.z));
			// color_ray = __get_color_ray(x, y);
			// color = __get_color_vec(&color_ray);
			color_each_pixel(&mlx->img, x, y, _get_color(color));
			x++;
		}
		y++;
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

/* Chapter 7 */
// t_vector	__get_color_vec(t_ray *ray, t_hitable *world) //ray_color
// {
// 	t_hit_record	rec;
// 	t_vector		unit_vector;
// 	double			t;
// 	t_hitarg 		arg;
// 	t_ray			__ray;

// 	arg.ray = ray;
// 	arg.min = 0.001;
// 	arg.max = MAXFLOAT;
// 	arg.rec = &rec;
// 	if (world->hit(world, arg))
// 	{
// 		__ray = new_ray(arg.rec->p, cal_subtract_vec(cal_add3_vec(arg.rec->p, arg.rec->normal, random_in_unit_sphere()), arg.rec->p));
// 		return (cal_multiply_vec(__get_color_vec(&__ray, world), 0.5));
// 	}
// 	unit_vector = unit_vec(ray->dir);
// 	t = 0.5 * ((unit_vector.y) + 1.0);
// 	unit_vector = new_vec(1.0 - 0.5 * t, 1.0 - 0.3 * t, 1.0);
// 	return (unit_vector);
// }