/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_matriz1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchissal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 08:26:41 by dchissal          #+#    #+#             */
/*   Updated: 2024/06/28 08:26:43 by dchissal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	process_line(char **map, char *line, int i, t_data *data)
{
	int		j;
	int		z;
	char	*num;

	j = 0;
	num = ft_strtok(line, " \n");
	while (num)
	{
		z = ft_atoi(num);
		map[i][j] = (char)z;
		if (z < data->limits.min_z)
			data->limits.min_z = z;
		if (z > data->limits.max_z)
			data->limits.max_z = z;
		num = ft_strtok(NULL, " \n");
		j++;
	}
}

void	fill_matrix(char **map, char *file_name, t_data *data)
{
	int		file;
	char	*line;
	ssize_t	read;
	int		i;

	line = NULL;
	i = 0;
	file = open(file_name, O_RDONLY);
	if (!file)
		handle_error("Erro: Não conseguimos abrir o arquivo");
	read = read_line(file, &line);
	data->limits.min_z = INT_MAX;
	data->limits.max_z = INT_MIN;
	while (read != -1)
	{
		process_line(map, line, i, data);
		i++;
		free(line);
		read = read_line(file, &line);
	}
	close(file);
}

char	**allocate_map(int width, int height)
{
	char	**map;
	int		i;

	map = (char **)malloc(sizeof(char *) * height);
	if (!map)
		handle_error("Erro: alocação de memória falhou!");
	i = 0;
	while (i < height)
	{
		map[i] = (char *)malloc(sizeof(char) * width);
		if (!map[i])
		{
			while (i > 0)
				free(map[--i]);
			free(map);
			handle_error("Erro: alocação de memória falhou!");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (map);
}

char	**read_map(char *file_name, t_data *data, int *min_z, int *max_z)
{
	char	**map;

	(void)min_z;
	(void)max_z;
	data->height = get_height(file_name);
	data->width = get_width(file_name);
	if (data->width <= 0 || data->height <= 0)
		handle_error("Dimensões inválidas");
	map = allocate_map(data->width, data->height);
	fill_matrix(map, file_name, data);
	return (map);
}
