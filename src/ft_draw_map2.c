/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_map2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchissal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 08:41:40 by dchissal          #+#    #+#             */
/*   Updated: 2024/06/28 08:41:42 by dchissal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line_part(t_point *p1, t_line_params *params)
{
	if (params->err > -params->dx)
	{
		params->err -= params->dy;
		p1->x += params->sx;
	}
	if (params->err < params->dy)
	{
		params->err += params->dx;
		p1->y += params->sy;
	}
}

void	set_params(t_line_params *params, t_point p1, t_point p2)
{
	params->dx = abs(p2.x - p1.x);
	params->dy = abs(p2.y - p1.y);
	if (p1.x < p2.x)
		params->sx = 1;
	else
		params->sx = -1;
	if (p1.y < p2.y)
		params->sy = 1;
	else
		params->sy = -1;
	if (params->dx > params->dy)
		params->err = params->dx / 2;
	else
		params->err = -params->dy / 2;
}

int	max_int(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

void	draw_line(t_data *data, t_point p1, t_point p2, t_points pts)
{
	t_line_params	params;
	int				i;
	int				current_color;
	int				x;
	int				y;

	set_params(&params, p1, p2);
	i = 0;
	while (i <= max_int(abs(p2.x - p1.x), abs(p2.y - p1.y)))
	{
		current_color = get_color(pts,
				max_int(abs(p2.x - p1.x), abs(p2.y - p1.y)), i);
		x = p1.x + i * (p2.x - p1.x)
			/ max_int(abs(p2.x - p1.x), abs(p2.y - p1.y));
		y = p1.y + i * (p2.y - p1.y)
			/ max_int(abs(p2.x - p1.x), abs(p2.y - p1.y));
		my_mlx_pixel_put(data, x, y, current_color);
		i++;
	}
}
