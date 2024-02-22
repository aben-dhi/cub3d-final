/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htouil <htouil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 19:32:06 by htouil            #+#    #+#             */
/*   Updated: 2024/02/14 19:18:08 by htouil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int	associate_infos(char *line, t_map *map)
// {
// 	char	*tmp;

// 	tmp = skip_spaces(line);
// 	if (ft_strncmp(tmp, "NO", 2) == 0)
// 		map->no = ft_datacpy(tmp, 2);
// 	else if (ft_strncmp(tmp, "SO", 2) == 0)
// 		map->so = ft_datacpy(tmp, 2);
// 	else if (ft_strncmp(tmp, "WE", 2) == 0)
// 		map->we = ft_datacpy(tmp, 2);
// 	else if (ft_strncmp(tmp, "EA", 2) == 0)
// 		map->ea = ft_datacpy(tmp, 2);
// 	else if (ft_strncmp(tmp, "F", 1) == 0)
// 		map->f = ft_datacpy(tmp, 1);
// 	else if (ft_strncmp(tmp, "C", 1) == 0)
// 		map->c = ft_datacpy(tmp, 1);
// 	return (1);
// }

// int	get_map_matrix(int fd, char *line, t_map *map)
// {
// 	char	*map_str;
// 	char	*tmp_str;

// 	map_str = ft_calloc(1, 1);
// 	if (!map_str)
// 		return (1);
// 	while (1)
// 	{
// 		tmp_str = map_str;
// 		map_str = ft_strjoin(map_str, line);
// 		free(tmp_str);
// 		map->rows++;
// 		free(line);
// 		line = get_next_line(fd);
// 		if (!line)
// 			break ;
// 	}
// 	display_dnl_error(map_str);
// 	map->map = ft_split(map_str, '\n');
// 	if (check_empty_spaces(map->map[map->rows - 1]) == 0)
// 	{
// 		free(map->map[map->rows - 1]);
// 		map->rows--;
// 	}
// 	return (free(map_str), close(fd), 0);
// }

// void	read_map(int fd, t_map *map)
// {
// 	int		flag;
// 	char	*line;

// 	flag = 0;
// 	line = get_next_line(fd);
// 	if (!line)
// 	{
// 		ft_putstr_fd("Error\nFile is empty!\n", 2);
// 		exit(1);
// 	}
// 	while (1)
// 	{
// 		if (!line)
// 		{
// 			ft_putstr_fd("Error\nFile incomplet!\n", 2);
// 			free(line);
// 			free_data(map);
// 			exit(1);
// 		}
// 		if (flag == 6 && check_empty_spaces(line) == 1)
// 			break ;
// 		if (flag <= 6 && check_empty_spaces(line) == 1)
// 		{
// 			ft_putstr_fd("Error\nInvalid file content!\n", 2);
// 			free(line);
// 			free_data(map);
// 			exit(1);
// 		}
// 		if (check_empty_spaces(line) == 0)
// 		{
// 			free(line);
// 			line = get_next_line(fd);
// 			continue ;
// 		}
// 		flag += associate_infos(line, map);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	if (get_map_matrix(fd, line, map) == 1)
// 		exit (1);
// }

void	display_dnl_error(char *lmap)
{
	if (check_double_nl(lmap) == 1)
	{
		ft_putstr_fd("Error\nThe map is invalid!\n", 2);
		free(lmap);
		// system("leaks cub3D");
		exit(1);
	}
}

int	get_map_matrix(int fd, char *line, t_map *map)
{
	char	*map_str;
	char	*tmp_str;

	map_str = ft_calloc(1, 1);
	if (!map_str)
		return (1);
	while (1)
	{
		tmp_str = map_str;
		map_str = ft_strjoin(map_str, line);
		free(tmp_str);
		map->rows++;
		free(line);
		line = get_next_line(fd);
		if (!line)
			break ;
	}
	display_dnl_error(map_str);
	map->map = ft_split(map_str, '\n');
	if (check_empty_spaces(map->map[map->rows - 1]) == 0)
	{
		free(map->map[map->rows - 1]);
		map->rows--;
	}
	return (free(map_str), close(fd), 0);
}

int	helper(char **line, int *flag, int fd, t_map *map)
{
	if (!*line)
	{
		ft_putstr_fd("Error\nFile incomplet!\n", 2);
		free(*line);
		free_data(map);
		exit(1);
	}
	if (*flag == 6 && check_empty_spaces(*line) == 1)
		return (1);
	if (*flag <= 6 && check_empty_spaces(*line) == 1)
	{
		ft_putstr_fd("Error\nInvalid file content!\n", 2);
		free(*line);
		free_data(map);
		exit(1);
	}
	if (check_empty_spaces(*line) == 0)
	{
		free(*line);
		*line = get_next_line(fd);
		return (2);
	}
	return (0);
}

int	associate_infos(char *line, t_map *map)
{
	char	*tmp;

	tmp = skip_spaces(line);
	if (ft_strncmp(tmp, "NO", 2) == 0)
		map->no = ft_datacpy(tmp, 2);
	else if (ft_strncmp(tmp, "SO", 2) == 0)
		map->so = ft_datacpy(tmp, 2);
	else if (ft_strncmp(tmp, "WE", 2) == 0)
		map->we = ft_datacpy(tmp, 2);
	else if (ft_strncmp(tmp, "EA", 2) == 0)
		map->ea = ft_datacpy(tmp, 2);
	else if (ft_strncmp(tmp, "F", 1) == 0)
		map->f = ft_datacpy(tmp, 1);
	else if (ft_strncmp(tmp, "C", 1) == 0)
		map->c = ft_datacpy(tmp, 1);
	return (1);
}

void	read_map(int fd, t_map *map)
{
	int		flag;
	int		i;
	char	*line;

	flag = 0;
	line = get_next_line(fd);
	if (!line)
	{
		ft_putstr_fd("Error\nFile is empty!\n", 2);
		exit(1);
	}
	while (1)
	{
		i = helper(&line, &flag, fd, map);
		if (i == 1)
			break ;
		else if (i == 2)
			continue ;
		flag += associate_infos(line, map);
		free(line);
		line = get_next_line(fd);
	}
	if (get_map_matrix(fd, line, map) == 1)
		exit (1);
}
