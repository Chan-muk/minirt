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

#include <sys/time.h>

int64_t	get_timestamp(void)
{
	struct timeval	time_val;
	int64_t			time;

	gettimeofday(&time_val, NULL);
	time = (time_val.tv_sec * 1000 + (time_val.tv_usec * 0.001));
	return (time);
}

// int	main(int argc, char **argv)
// {
// 	t_mlx	mlx;
// 	int64_t	time_1;
// 	int64_t	time_2;

// 	check_input(argc, argv);
// 	return (0);

// 	time_1 = get_timestamp();
// 	// arguments_check(argc, argv, &mlx);
// 	initialize(argc, argv, &mlx);
// 	color_window(&mlx);
// 	set_hooks(&mlx);
// 	time_2 = get_timestamp();
// 	printf("time: %ld\n", time_2 - time_1);
// 	mlx_loop(mlx.mlx_ptr);
// 	return (0);
// }


t_vector	_cal_add_vec1(t_vector vec_1, t_vector vec_2)
{
	t_vector	vector;

	vector.x = vec_1.x + vec_2.x;
	vector.y = vec_1.y + vec_2.y;
	vector.z = vec_1.z + vec_2.z;
	return (vector);
}

t_vector	_cal_add_vec2(t_vector *vec_1, t_vector *vec_2)
{
	t_vector	vector;

	vector.x = vec_1->x + vec_2->x;
	vector.y = vec_1->y + vec_2->y;
	vector.z = vec_1->z + vec_2->z;
	return (vector);
}

int	main(int argc, char **argv)
{
	t_vector result;

	result = _cal_add_vec1(new_vec(1, 1, 1), new_vec(1, 1, 1));
	return (0);
}

int	main(int argc, char **argv)
{
	t_vector result;
	t_vector new;

	new = 
	result = _cal_add_vec2(new_vec(1, 1, 1), new_vec(1, 1, 1));
	return (0);
}