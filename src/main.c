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

void	texture_free(t_hit_array	array[])
{
	int i;

	i = 0;
	while (array[i].type)
	{
		if (array[i].flag == _texture)
		{
			free(array[i].texture.addr);
			free(array[i].bump_map.addr);
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_hit_array	array[OBJ_COUNT];

	data.scene.world = array;
	initialize(argc, argv, &data);
	color_window(&data.mlx, &data.scene);
	texture_free(array);
	set_hooks(&data.mlx);
	mlx_loop(data.mlx.mlx_ptr);
	return (0);
}
