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

void	color_each_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->data_addr + (x * img->bits_per_pixel / 8) + ((WIN_HEIGHT - y) * img->size_line);
	*(unsigned int *)dst = color;
}

int	_get_color(t_vector vec)
{
	return (((int)(255.999 * vec.x) << 16) + ((int)(255.999 * vec.y) << 8) + (int)(255.999 * vec.z));
}
