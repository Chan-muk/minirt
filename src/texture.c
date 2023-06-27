/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 11:27:10 by chajung           #+#    #+#             */
/*   Updated: 2023/06/19 11:27:11 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	get_bmp_addr(char *path, t_images *img)
{
	ssize_t			size;
	ssize_t			tmp;
	const int		bmp_fd = open(path, O_RDONLY);
	char			header[54];

	if (bmp_fd == -1)
		exit_with_str("Error\nBMP: Error opening file.", EXIT_FAILURE);
	size = read(bmp_fd, &header, 54);
	if (size != 54)
		exit_with_str("Error\nBMP: Error reading header.", EXIT_FAILURE);
	if (*(unsigned int *)(header + 34) != 0)
		size = *(unsigned int *)(header + 34);
	else
		size = *(unsigned int *)(header + 2) - *(unsigned int *)(header + 10);
	img->addr = (uint8_t *)malloc(size);
	img->w = *(int *)(header + 18);
	img->h = *(int *)(header + 22);
	tmp = read(bmp_fd, img->addr, size);
	if (size != tmp)
		exit_with_str("Error\nBMP: Error reading imagedata.", EXIT_FAILURE);
	close(bmp_fd);
}

t_color	plane_texture(t_vector p, t_hit_array *pl)
{
	double			u;
	double			v;
	int				i;
	unsigned char	*addr;

	u = fract(p.x * 0.2);
	v = fract(p.y * 0.2);
	i = \
	((int)(pl->texture.w * u) + (int)(pl->texture.h * v) * pl->texture.w) * 3;
	addr = pl->texture.addr;
	return \
	(new_color(addr[i + 2] / 255.0, addr[i + 1] / 255.0, addr[i] / 255.0));
}

t_color	shpere_texture(t_vector p, t_hit_array *sp)
{
	double			u;
	double			v;
	int				i;
	unsigned char	*addr;

	u = \
	1 - (atan((p.z - sp->center.z) / (p.x - sp->center.x)) / (2 * M_PI) + 0.5);
	v = 1 - (acos((p.y - sp->center.y) / sp->radius) / M_PI);
	i = \
	((int)(sp->texture.w * u) + (int)(sp->texture.h * v) * sp->texture.w) * 3;
	addr = sp->texture.addr;
	return (\
	new_color(addr[i + 2] / 255.0, addr[i + 1] / 255.0, addr[i] / 255.0));
}

t_color	cylinder_texture_side(t_vector p, t_hit_array *cy)
{
	t_uvbox	o;

	if (vec_len(vec_prod(cy->norm, new_vec(0, 1, 0))) == 0.0)
		o.stdvec1 = new_vec(0, 0, 1);
	else
		o.stdvec1 = unit_vec(vec_prod(cy->norm, new_vec(0, 1, 0)));
	o.stdvec2 = unit_vec(vec_prod(cy->norm, o.stdvec1));
	o.v = (vec_dot(vec_sub(p, cy->center), cy->norm));
	o.vec_u = unit_vec(vec_sub(p, vec_add(cy->center, vec_mul(cy->norm, o.v))));
	o.u = -atan2(vec_dot(o.vec_u, o.stdvec1), \
	vec_dot(o.vec_u, o.stdvec2)) / (M_PI * 2);
	o.v /= cy->height;
	o.i = ((int)(cy->texture.w * o.u) + (int)((cy->texture.h * o.v) * cy->texture.w)) * 3;
	// o.i = (int)(((cy->texture.w * o.u) + (cy->texture.h * o.v) * cy->texture.w) * 3);
	o.addr = cy->texture.addr;
	printf("u: %f,\tv: %f,\ti: %d\n", o.u, o.v, o.i);
	printf("w: %d,\th: %d\n", cy->texture.w, cy->texture.h);
	printf("x: %d,\ty: %d\n", (int)(cy->texture.w * o.u), (int)(cy->texture.h * o.v));
	if(o.i < 0)
		return (new_color(1, 1, 1));
	return (new_color(o.addr[o.i + 2] / \
	255.0, o.addr[o.i + 1] / 255.0, o.addr[o.i] / 255.0));
}
/*
	cylinder
	theta = atan2(p.x, p.z);
	u = 1 - ((theta / (2 * M_PI)) + 0.5);
	v = fmod(p.y, 1);

	u = 1 - ((atan2(p.x, p.z) / (2 * M_PI)) + 0.5);
	v = fmod(p.y, 1);

	cone
	theta = atan2(p.x, p.z);
	rad = p.x * p.x + p.z * p.z;
	u = 1 - ((theta / (2 * M_PI)) + 0.5);
	v = fmod(sqrt(rad), 1);
*/
t_color	cylinder_texture_cap(t_vector p, t_hit_array *cy)
{
	t_uvbox	o;

	if (vec_len(vec_prod(cy->norm, new_vec(0, 1, 0))) == 0.0)
		o.stdvec1 = new_vec(0, 0, 1);
	else
		o.stdvec1 = unit_vec(vec_prod(cy->norm, new_vec(0, 1, 0)));
	o.stdvec2 = unit_vec(vec_prod(cy->norm, o.stdvec1));
	o.v = (vec_dot(vec_sub(p, cy->center), cy->norm));
	o.vec_u = unit_vec(vec_sub(p, vec_add(cy->center, vec_mul(cy->norm, o.v))));
	// o.u = atan(fabs(vec_dot(o.vec_u, o.stdvec1) / vec_dot(o.vec_u, o.stdvec2))) / (2 * M_PI);
	o.u = 1 - ((atan2(p.x, p.z) / (2 * M_PI)) + 0.5);
	// o.u = atan2(vec_dot(o.vec_u, o.stdvec1), vec_dot(o.vec_u, o.stdvec2)) / (M_PI * 2);
	// o.u = fabs(o.u);
	o.v /= cy->height;
	if (o.v < 0.5)
		o.i = ((int)(cy->texture.w * o.u) + 1 * cy->texture.w) * 3;
	else
		o.i = ((int)(cy->texture.w * o.u) + \
		(cy->texture.h - 1) * cy->texture.w) * 3;
	o.addr = cy->texture.addr;
	return \
	(new_color(o.addr[o.i + 2] / 255.0, o.addr[o.i + 1] / 255.0, o.addr[o.i] / 255.0));
}
