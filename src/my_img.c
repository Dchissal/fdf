/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_img.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchissal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 08:24:57 by dchissal          #+#    #+#             */
/*   Updated: 2024/10/11 08:25:01 by dchissal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *system, int x, int y, int color)
{
	char	*pixel;
	int		index;

	if (x >= 0 && x < LARGURA - 180 && y >= 0 && y < ALTURA)
	{
		index = (y * system->line_length) + (x * (system->bits_per_pixel / 8));
		pixel = system->addr + index;
		*(unsigned int *)pixel = color;
	}
}

void	fill_background(t_data *img, int time)
{
	int	x;
	int	y;
	int r, g, b;
	float ratio;
	int start_color;
	int end_color;

	start_color = (0x00336 + time) & 0xFFFFFF;
	end_color = (0xFF5733 + time) & 0xFFFFFF;

	y = 0;
	while (y < ALTURA)
	{
		ratio = (float)y / ALTURA;
		r = ((1 - ratio) * ((start_color >> 16) & 0xFF)) + (ratio * ((end_color >> 16) & 0xFF));
		g = ((1 - ratio) * ((start_color >> 8) & 0xFF)) + (ratio * ((end_color >> 8) & 0xFF));
		b = ((1 - ratio) * (start_color & 0xFF)) + (ratio * (end_color & 0xFF));
		int color = (r << 16) | (g << 8) | b;

		x = 0;
		while (x < LARGURA - 180)
		{
			my_mlx_pixel_put(img, x, y, color);
			x++;
		}
		y++;
	}
}


void	info(t_data *data)
{
	int	color;

	color = 0xFFFFFF;
	mlx_string_put(data->mlx_ptr, data->win_ptr,
		10, 15, color, "Informacoes do projecto!");
	mlx_string_put(data->mlx_ptr, data->win_ptr,
		10, 35, 0x00f027, "O que e FDF?");
	mlx_string_put(data->mlx_ptr, data->win_ptr,
		10, 55, color, "projeto FdF, abreviacao de <Fil de Fer>");
	mlx_string_put(data->mlx_ptr, data->win_ptr,
		10, 75, color, "O principal objetivo do FdF e");
	mlx_string_put(data->mlx_ptr, data->win_ptr,
		10, 95, color, "desenvolver uma visualizacao 3D simples");
	mlx_string_put(data->mlx_ptr, data->win_ptr,
		10, 115, color, "de mapas de elevacao ");
	mlx_string_put(data->mlx_ptr, data->win_ptr,
		10, 135, color, "em um plano isometrico, onde a profundidade");
	mlx_string_put(data->mlx_ptr, data->win_ptr,
		10, 155, color, "e representada de forma a dar");
	mlx_string_put(data->mlx_ptr, data->win_ptr,
		10, 175, color, "uma nocao de perspectiva.");
	mlx_string_put(data->mlx_ptr, data->win_ptr,
		10, 195, color, "Fdf feito por Daniel Chissali");
}

int	read_line(int fd, char **line)
{
	*line = get_next_line(fd);
	if (*line == NULL)
		return (-1);
	return (1);
}
