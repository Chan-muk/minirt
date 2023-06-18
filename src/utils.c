/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 08:57:27 by chajung           #+#    #+#             */
/*   Updated: 2023/05/01 08:57:28 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	fract(double x)
{
	return (x - floor(x));
}

bool	check_object_height(t_hit_array *obj, t_ray *ray, double root)
{
	double	point_on_line;

	point_on_line = \
	vec_dot(vec_sub(vec_add(ray->org, vec_mul(ray->dir, root)), obj->center), obj->norm);
	if (point_on_line < 0.0 || point_on_line > obj->height)
		return (false);
	return (true);
}

void	data_backup(t_hit_record *rec_backup, t_hit_record *rec)
{
	rec_backup->albedo = rec->albedo;
	rec_backup->front_face = rec->front_face;
	rec_backup->normal = rec->normal;
	rec_backup->p = rec->p;
	rec_backup->t = rec->t;
	rec_backup->tmax = rec->tmax;
	rec_backup->tmin = rec->tmin;
}

void	exit_with_str(const char *str, int exit_code)
{
	ft_putendl_fd((char *)str, STDERR_FILENO);
	exit(exit_code);
}

static int	white_space_sign_check(char *str, int *index)
{
	int	sign;

	sign = 1;
	while ((9 <= str[*index] && str[*index] <= 13) || str[*index] == 32)
		*index += 1;
	if (str[*index] == '+' || str[*index] == '-')
	{
		if (str[*index] == '-')
			sign = sign * (-1);
		*index += 1;
	}
	return (sign);
}

static void	is_double(char *str)
{
	int	sign;
	int	c;
	int	dot;

	sign = 0;
	c = 0;
	dot = 0;
	while (str && *str)
	{
		if (*str == '+' || *str == '-')
			sign++;
		else if (*str == '.')
			dot++;
		else if (!ft_isdigit(*str) && ft_isascii(*str))
			c++;
		str++;
	}
	if (!str || sign > 1 || dot > 1 || c > 0)
		exit_with_str("input right number", EXIT_FAILURE);
}

double	ascii_to_double(char *str)
{
	int		index;
	int		sign;
	int		decimal_count;
	double	number;

	index = 0;
	decimal_count = 0;
	number = 0.0;
	is_double(str);
	sign = white_space_sign_check(str, &index);
	while (str[index] && ft_isdigit(str[index]))
	{
		number = 10.0 * number + (str[index] - '0');
		index++;
	}
	if (str[index] == '.')
		index++;
	while (str[index] && ft_isdigit(str[index]))
	{
		number = 10.0 * number + (str[index] - '0');
		index++;
		decimal_count++;
	}
	return (sign * number * pow(0.1, decimal_count));
}
