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

unsigned char	*get_bmp_addr(char *path, int *w, int *h)
{
	ssize_t			size;
	BMPHeader		header;
	unsigned char	*imageaddr;
	const int		bmp_fd = open(path, O_RDONLY);

	if (bmp_fd == -1)
		exit_with_str("Error\nBMP: Error opening file.", EXIT_FAILURE);
	size = read(bmp_fd, &header, sizeof(BMPHeader));
	if (size != sizeof(BMPHeader))
		exit_with_str("Error\nBMP: Error reading header.", EXIT_FAILURE);
	if (header.data_size != 0)
		size = header.data_size;
	else
		size = header.file_size - header.data_offset;
	imageaddr = (uint8_t *)malloc(size);
	*w = header.width;
	*h = header.height;
	size = read(bmp_fd, imageaddr, size);
	if (size != sizeof(BMPHeader))
		exit_with_str("Error\nBMP: Error reading imagedata.", EXIT_FAILURE);
	close(bmp_fd);
	return (imageaddr);
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
	((int)(pl->texture_w * u) + (int)(pl->texture_h * v) * pl->texture_w) * 3;
	addr = pl->texture_addr;
	return (\
	new_color(addr[i + 2] / 255.0, addr[i + 1] / 255.0, addr[i] / 255.0));
}

t_color	shpere_texture(t_vector p, t_hit_array *sp, t_hit_record *rec)
{
	double			u;
	double			v;
	int				i;
	unsigned char	*addr;

	u = (rec->normal.x + 1) * 0.5;
	v = (rec->normal.y + 1) * 0.5;
	i = \
	((int)(sp->texture_w * u) + (int)(sp->texture_h * v) * sp->texture_w) * 3;
	addr = sp->texture_addr;
	return (\
	new_color(addr[i + 2] / 255.0, addr[i + 1] / 255.0, addr[i] / 255.0));
}
