/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_matriz2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchissal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 08:31:17 by dchissal          #+#    #+#             */
/*   Updated: 2024/06/28 08:31:19 by dchissal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	count_words_in_line(char *line)
{
	int	i;
	int	current_width;

	current_width = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && (i == 0 || line[i - 1] == ' '))
			current_width++;
		i++;
	}
	return (current_width);
}

void	check_line_width(int current_width, int width)
{
	if (current_width != width)
		handle_error("Erro: o mapa tem coluna a mais em uma das linhas!");
}

int	open_file(char *file_name)
{
	int	file;

	file = open(file_name, O_RDONLY);
	if (!file)
		handle_error("Erro: Não conseguimos abrir o arquivo!");
	return (file);
}

int	get_width(char *file_name)
{
	int		file;
	char	*line;
	ssize_t	read;
	int		width;

	file = open_file(file_name);
	line = NULL;
	read = read_line(file, &line);
	if (read == -1)
		handle_error("Erro: Não conseguimos abrir o arquivo!");
	width = count_words_in_line(line);
	free(line);
	read = read_line(file, &line);
	while (read != -1)
	{
		check_line_width(count_words_in_line(line), width);
		free(line);
		read = read_line(file, &line);
	}
	close(file);
	return (width);
}

int	get_height(char *file_name)
{
	int		file;
	char	*line;
	ssize_t	read;
	int		height;

	line = NULL;
	height = 0;
	file = open(file_name, O_RDONLY);
	read = read_line(file, &line);
	if (!file)
		handle_error("Erro: Não conseguimos abrir o arquivo");
	while (read != -1)
	{
		height++;
		free(line);
		read = read_line(file, &line);
	}
	close(file);
	return (height);
}
