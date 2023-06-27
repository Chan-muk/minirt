/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:27:51 by chajung           #+#    #+#             */
/*   Updated: 2023/06/21 18:27:52 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int argc, char **argv)
{
	// t_mlx		mlx;
	// t_scene		scene;
	t_data	data;

	initialize_bonus(argc, argv, &data);

	color_window(&data.mlx, &data.scene);
	set_hooks(&data.mlx);
	mlx_loop(data.mlx.mlx_ptr);
	return (0);
}
