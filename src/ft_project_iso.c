/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_project_iso.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchissal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 09:10:39 by dchissal          #+#    #+#             */
/*   Updated: 2024/06/28 09:10:41 by dchissal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	project_iso(t_point p, int scale, int z_scale)
{
	t_point	iso_point;

	iso_point.x = (p.x - p.y) * scale;
	iso_point.y = ((p.x + p.y) * scale) / 3 - p.z * z_scale;
	iso_point.z = p.z;
	return (iso_point);
}

int	ft_os_tres_idiotas(t_data *data)
{
	free_map(data->map, data->height);
	data->map = NULL;
	mlx_destroy_image(data->mlx_ptr, data->img);
	data->img = NULL;
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	data->win_ptr = NULL;
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(0);
}
