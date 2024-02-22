/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_components.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htouil <htouil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 19:46:21 by htouil            #+#    #+#             */
/*   Updated: 2024/01/03 17:55:40 by htouil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_map_content(t_map *map)
{
	int	i;
	int	j;

	j = 0;
	while (j < map->rows)
	{
		i = 0;
		while (map->map[j][i])
		{
			if (map->map[j][i] != ' ' && map->map[j][i] != '0'
				&& map->map[j][i] != '1' && map->map[j][i] != 'N'
				&& map->map[j][i] != 'S' && map->map[j][i] != 'E'
				&& map->map[j][i] != 'W')
				return (0);
			i++;
		}
		j++;
	}
	return (1);
}

int	check_map_player(t_map *map)
{
	int	i;
	int	j;
	int	k;

	map->columns = malloc((map->rows + 1) * sizeof(int));
	if (!map->columns)
		exit(1);
	k = 0;
	j = 0;
	while (j < map->rows)
	{
		map->columns[j] = ft_strlen1(map->map[j]);
		i = 0;
		while (map->map[j][i])
		{
			if (map->map[j][i] == 'N' || map->map[j][i] == 'S'
				|| map->map[j][i] == 'E' || map->map[j][i] == 'W')
				k++;
			i++;
		}
		j++;
	}
	if (k == 1)
		return (1);
	return (0);
}

int	check_map_frame0(t_map *map)
{
	int	i;

	i = 0;
	while (map->map[0][i])
	{
		if (map->map[0][i] != ' ' && map->map[0][i] != '1')
			return (0);
		i++;
	}
	i = 0;
	while (map->map[map->rows - 1][i])
	{
		if (map->map[map->rows - 1][i] != ' '
		&& map->map[map->rows - 1][i] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	check_map_frame1(t_map *map)
{
	int	j;
	int	pos;

	j = 0;
	while (j < map->rows)
	{
		pos = avoid_spaces(map->map[j]);
		if (map->map[j][pos] != '1')
			return (0);
		pos = reverse_avoid_spaces(map->map[j]);
		if (map->map[j][pos] != '1')
			return (0);
		j++;
	}
	return (1);
}

int	check_map_frame2(t_map *map)
{
	int	i;
	int	j;

	j = -1;
	while (++j < map->rows)
	{
		i = 0;
		while (map->map[j][i])
		{
			if (map->map[j][i] == '0')
			{
				if ((map->map[j][i + 1] && map->map[j][i + 1] == ' ')
				|| (map->map[j][i - 1] && map->map[j][i - 1] == ' ')
				|| (map->map[j + 1][i] && map->map[j + 1][i] == ' ')
				|| (map->map[j - 1][i] && map->map[j - 1][i] == ' ')
				|| (map->map[j + 1][i + 1] && map->map[j + 1][i + 1] == ' ')
				|| (map->map[j - 1][i + 1] && map->map[j - 1][i + 1] == ' ')
				|| (map->map[j + 1][i - 1] && map->map[j + 1][i - 1] == ' ')
				|| (map->map[j - 1][i - 1] && map->map[j - 1][i - 1] == ' '))
					return (0);
			}
			i++;
		}
	}
	return (1);
}
