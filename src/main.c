/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchissal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 09:05:37 by dchissal          #+#    #+#             */
/*   Updated: 2024/06/28 09:05:39 by dchissal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*int	ft_check_est(char *s)
{
	int	i;
	int	j;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '.')
		{
			j = 0;
			while (".fdf"[j] != '\0' && ".fdf"[j] == s[i])
			{
				i++;
				j++;
			}
		}
		i++;
	}
	if (j == 4)
		return (0);
	handle_error("error... Extensão inválida!\n");
	return (-1);
}*/

void	free_map(char **map, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	handle_error(char *message)
{
	perror(message);
	//exit(EXIT_FAILURE);
	
}

int	close_program(int key, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (key == 65307)
	{
		free_map(data->map, data->height);
		mlx_destroy_image(data->mlx_ptr, data->img);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		exit(0);
	}
	return (0);
}

int	handle_key(int keycode, t_data *data)
{
	char	*argv[19] = {"./test_maps/angola.fdf", "./test_maps/elem2.fdf", "./test_maps/elem-fract.fdf", "./test_maps/julia.fdf", "./test_maps/pylone.fdf", "./test_maps/Africa.fdf", "./test_maps/pnp_flat.fdf", "./test_maps/pyramide.fdf", "./test_maps/pyra.fdf", "./test_maps/plat.fdf", "./test_maps/pentenegpos.fdf", "./test_maps/mars.fdf", "./test_maps/elem-col.fdf", "./test_maps/elem.fdf", "./test_maps/basictest.fdf", "./test_maps/42.fdf", "./test_maps/20-60.fdf", "./test_maps/10-70.fdf", "./test_maps/10-2.fdf"};
	int	num_maps = 19;

	if (keycode == 65363)
		data->current_map_index = (data->current_map_index + 1) % num_maps;
	else if (keycode == 65361)
		data->current_map_index = (data->current_map_index - 1 + num_maps) % num_maps;
	data->time += 10;
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	data->map = read_map(argv[data->current_map_index], data, &data->limits.min_z, &data->limits.max_z);
	fill_background(data, data->time);
	draw_iso_map(data);
	info(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, 180, 0);
	return (0);
}

int	main(void)
{
	char	*argv[19] = {"./test_maps/angola.fdf", "./test_maps/elem2.fdf", "./test_maps/elem-fract.fdf", "./test_maps/julia.fdf", "./test_maps/pylone.fdf", "./test_maps/Africa.fdf","./test_maps/pnp_flat.fdf", "./test_maps/pyramide.fdf", "./test_maps/pyra.fdf", "./test_maps/plat.fdf", "./test_maps/pentenegpos.fdf", "./test_maps/mars.fdf", "./test_maps/elem-col.fdf", "./test_maps/elem.fdf", "./test_maps/basictest.fdf", "./test_maps/42.fdf", "./test_maps/20-60.fdf", "./test_maps/10-70.fdf", "./test_maps/10-2.fdf"};
	t_data	data;

	data.mlx_ptr = mlx_init();
	data.win_ptr = mlx_new_window(data.mlx_ptr,
			LARGURA, ALTURA, "FdF by Optimus Prime");
	data.current_map_index = 0;
	data.time = 0;
	data.img = mlx_new_image(data.mlx_ptr,
			LARGURA - 180, ALTURA);
	data.addr = mlx_get_data_addr(data.img,
			&data.bits_per_pixel, &data.line_length, &data.endian);
	data.map = read_map(argv[data.current_map_index], &data, &data.limits.min_z, &data.limits.max_z);
	fill_background(&data, data.time);
	draw_iso_map(&data);
	info(&data);
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img, 180, 0);
	mlx_hook(data.win_ptr, 17, 0, ft_os_tres_idiotas, &data);
	mlx_key_hook(data.win_ptr, handle_key, &data);
	//mlx_key_hook(data.win_ptr, close_program, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}

/*int	main(void)
{
	t_data	data;

	//if (ft_check_est(argv[1]) == -1)
	//	return (-1);
	char	*argv[17] = {"./test_maps/elem2.fdf", "./test_maps/elem-fract.fdf", "./test_maps/julia.fdf", "./test_maps/pylone.fdf", "./test_maps/pnp_flat.fdf", "./test_maps/pyramide.fdf", "./test_maps/pyra.fdf", "./test_maps/plat.fdf", "./test_maps/pentenegpos.fdf", "./test_maps/mars.fdf", "./test_maps/elem-col.fdf", "./test_maps/elem.fdf", "./test_maps/basictest.fdf", "./test_maps/42.fdf", "./test_maps/20-60.fdf", "./test_maps/10-70.fdf", "./test_maps/10-2.fdf"};
	data.mlx_ptr = mlx_init();
	data.win_ptr = mlx_new_window(data.mlx_ptr,
			LARGURA, ALTURA, "FdF by Optimus Prime");
	data.map = read_map(argv[1], &data, &data.limits.min_z, &data.limits.max_z);
	data.img = mlx_new_image(data.mlx_ptr,
			LARGURA - 180, ALTURA);
	data.addr = mlx_get_data_addr(data.img,
			&data.bits_per_pixel, &data.line_length, &data.endian);
	fill_background(&data, 0x00336);
	draw_iso_map(&data);
	info(&data);
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img, 180, 0);
	mlx_hook(data.win_ptr, 17, 0, ft_os_tres_idiotas, &data);
	mlx_key_hook(data.win_ptr, close_program, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}*/

