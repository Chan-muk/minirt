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
	t_bmpheader		header;
	const int		bmp_fd = open(path, O_RDONLY);

	if (bmp_fd == -1)
		exit_with_str("Error\nBMP: Error opening file.", EXIT_FAILURE);
	size = read(bmp_fd, &header, sizeof(t_bmpheader));
	if (size != sizeof(t_bmpheader))
		exit_with_str("Error\nBMP: Error reading header.", EXIT_FAILURE);
	if (header.data_size != 0)
		size = header.data_size;
	else
		size = header.file_size - header.data_offset;
	img->addr = (uint8_t *)malloc(size);
	img->w = header.width;
	img->h = header.height;
	tmp = read(bmp_fd, img->addr, size);
	if (size != tmp)
		exit_with_str("Error\nBMP: Error reading image data.", EXIT_FAILURE);
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
	return (\
	new_color(addr[i + 2] / 255.0, addr[i + 1] / 255.0, addr[i] / 255.0));
}

t_color	shpere_texture(t_vector p, t_hit_array *sp, t_hit_record *rec)
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
