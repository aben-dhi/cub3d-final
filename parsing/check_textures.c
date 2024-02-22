/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htouil <htouil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 00:28:53 by htouil            #+#    #+#             */
/*   Updated: 2024/02/14 18:49:14 by htouil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_no(t_map *map)
{
	char	*ext;
	int		len;
	int		fd;

	ext = ft_strrchr(map->no, '.');
	len = ft_strlen1(ext);
	if (!ext || len != 4 || ext[len - 1] != 'g' || ext[len - 2] != 'n'
		|| ext[len - 3] != 'p' || ext[len - 4] != '.')
		return (0);
	fd = open(map->no, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

int	check_so(t_map *map)
{
	char	*ext;
	int		len;
	int		fd;

	ext = ft_strrchr(map->so, '.');
	len = ft_strlen1(ext);
	if (!ext || len != 4 || ext[len - 1] != 'g' || ext[len - 2] != 'n'
		|| ext[len - 3] != 'p' || ext[len - 4] != '.')
		return (0);
	fd = open(map->so, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

int	check_we(t_map *map)
{
	char	*ext;
	int		len;
	int		fd;

	ext = ft_strrchr(map->we, '.');
	len = ft_strlen1(ext);
	if (!ext || len != 4 || ext[len - 1] != 'g' || ext[len - 2] != 'n'
		|| ext[len - 3] != 'p' || ext[len - 4] != '.')
		return (0);
	fd = open(map->we, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

int	check_ea(t_map *map)
{
	char	*ext;
	int		len;
	int		fd;

	ext = ft_strrchr(map->ea, '.');
	len = ft_strlen1(ext);
	if (!ext || len != 4 || ext[len - 1] != 'g' || ext[len - 2] != 'n'
		|| ext[len - 3] != 'p' || ext[len - 4] != '.')
		return (0);
	fd = open(map->ea, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

int	check_textures(t_map *map)
{
	if (!map->no || !map->so || !map->we || !map->ea)
		return (0);
	if (map->no[0] == '\0' || map->so[0] == '\0'
		|| map->we[0] == '\0' || map->ea[0] == '\0')
		return (0);
	if (check_no(map) == 0 || check_so(map) == 0
		|| check_we(map) == 0 || check_ea(map) == 0)
		return (0);
	return (1);
}
