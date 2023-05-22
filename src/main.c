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

/* Chapter 9.4.: Mirrored Light Reflection */
t_vector	reflect(t_vector vec_1, t_vector vec_2)
{
	return (cal_subtract_vec(vec_1, cal_multiply_vec(vec_2, 2 * cal_inner_vec(vec_1, vec_2))));
}

bool	scatter_metal(void *this, struct s_material_arg arg)
{
	t_metal		*metal;
	t_vector	reflected;
	t_ray		ray;
	
	metal = (t_metal *)this;
	reflected = reflect(unit_vec(arg.ray_in->dir), arg.rec->normal);
	*arg.scattered = new_ray(arg.rec->p, reflected);
	*arg.attenuation = metal->albedo;
	if (cal_inner_vec(arg.scattered->dir, arg.rec->normal) > 0)
		return (true);
	else
		return (false);
}
/* Chapter 9.4.: Mirrored Light Reflection */

/* Chapter 9.3.: Modeling Light Scatter and Reflectance */
bool	near_zero(void *this)
{	// Returns true if the vector is very close to zero in all dimensions
	t_vector	*vec;
	double 		s;

	vec = (t_vector *)this;
	s = 0.00000001;
	return (fabs(vec->x) < s) && (fabs(vec->y) < s) && (fabs(vec->z) < s);
}

bool	scatter_lambertian(void *this, t_material_arg arg)
{
	t_vector		scatter_direction;
	t_lambertian	*lambertian;

	lambertian = (t_lambertian *)this;
	scatter_direction = cal_add_vec(arg.rec->normal, random_unit_vecter());
	if (near_zero(&scatter_direction))
		scatter_direction = arg.rec->normal;
	*arg.scattered = new_ray(arg.rec->p, scatter_direction);
	*arg.attenuation = lambertian->albedo;
	return (true);
}
/* Chapter 9.3.: Modeling Light Scatter and Reflectance */

void	check_face_normal(void *this, t_ray ray, t_vector outward_normal)
{
	t_hit_record	*rec;

	rec = (t_hit_record *)this;
	if (cal_inner_vec(ray.dir, outward_normal) > 0.0)
	{
		rec->normal = cal_inverse_vec(outward_normal);
		rec->front_face = false;
	}
	else
	{
		rec->normal = outward_normal;
		rec->front_face = true;
	}
}

bool	hit_sphere(void *this, t_hitarg arg)
{
	t_sphere	*sphere;
	t_vector	r_center;
	double		a;
	double		b;
	double		c;
	double		discriminant;
	double		root;

	sphere = (t_sphere *)this;
	r_center = cal_subtract_vec(arg.ray->org, sphere->center);
	a = cal_inner_vec(arg.ray->dir, arg.ray->dir);
	b = cal_inner_vec(r_center, arg.ray->dir);
	c = cal_inner_vec(r_center, r_center) - (sphere->radius * sphere->radius);
	discriminant = (b * b) - (a * c);
	if (discriminant < 0.0)
		return (false);
	root = (-b - sqrt(discriminant)) / a;
	if (root < arg.min || arg.max < root) {
		root = (-b + sqrt(discriminant)) / a;
		if (root < arg.min || arg.max < root)
			return (false);
	}
	arg.rec->t = root;
	arg.rec->p = cal_ray(*arg.ray, arg.rec->t);
	
	t_vector	outward_normal;
	outward_normal = cal_divide_vec(cal_subtract_vec(arg.rec->p, sphere->center), sphere->radius);
	arg.rec->set_face_normal(arg.rec, *arg.ray, outward_normal);
	
	arg.rec->mat_ptr = sphere->mat_ptr;
	return (true);
}

bool	hit_hittable_list(void *this, t_hitarg arg)
{
	t_hittable_list	*world;
	t_hit_record	temp_rec;
	bool			hit_anything;
	t_hitarg		temp_arg;

	world = (t_hittable_list *)this;
	hit_anything = false;
	temp_arg = arg;
	temp_arg.rec = &temp_rec;
	temp_rec.set_face_normal = check_face_normal;
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

t_vector	__get_color_vec(t_ray *ray, t_hittable *world, int depth)
{	//ray_color
	t_hit_record	rec;
	t_vector		unit_vector;
	double			t;
	t_hitarg 		hit_arg;
	t_ray			__ray;

	if (depth <= 0)
		return (new_vec(0.0, 0.0, 0.0));

	hit_arg.ray = ray;
	hit_arg.min = 0.001;
	hit_arg.max = MAXFLOAT;
	hit_arg.rec = &rec;
	rec.set_face_normal = check_face_normal;

	if (world->hit(world, hit_arg))
	{
		t_ray			scattered;
		t_vector		attenuation;
		t_material_arg	mat_arg;

		mat_arg.ray_in = ray;
		mat_arg.rec = &rec;
		mat_arg.attenuation = &attenuation;
		mat_arg.scattered = &scattered;
		if (rec.mat_ptr->scatter(rec.mat_ptr, mat_arg))
			return (cal_multi_vec(attenuation, __get_color_vec(&scattered, world, depth - 1)));
		return (new_vec(0.0, 0.0, 0.0));
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

	// t_hittable	*list[2];
	// t_hittable	*world = &(t_hittable_list){hit_hittable_list, list, 2};
	// list[0] = &(t_sphere){hit_sphere, {0, 0, -1}, 0.5};
	// list[1] = &(t_sphere){hit_sphere, {0, -100.5, -1}, 100};

	/* Chapter 9.5. */
	t_lambertian	*lam[2];
	t_metal			*met[2];

	lam[0] = &(t_lambertian){scatter_lambertian, new_vec(0.8, 0.8, 0.0)};
	lam[1] = &(t_lambertian){scatter_lambertian, new_vec(0.7, 0.3, 0.3)};
	met[0] = &(t_metal){scatter_metal, new_vec(0.8, 0.8, 0.8)};
	met[1] = &(t_metal){scatter_metal, new_vec(0.8, 0.6, 0.2)};

	t_hittable	*list[4];
	t_hittable	*world = &(t_hittable_list){hit_hittable_list, list, 4};
	list[0] = &(t_sphere){hit_sphere, {0.0, -100.5, -1.0}, 100.0, lam[0]};
	list[1] = &(t_sphere){hit_sphere, {0.0, 0.0, -1.0}, 0.5, lam[1]};
	list[2] = &(t_sphere){hit_sphere, {-1.0, 0.0, -1.0}, 0.5, met[0]};
	list[3] = &(t_sphere){hit_sphere, {1.0, 0.0, -1.0}, 0.5, met[1]};
	/* Chapter 9.5. */

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
