/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htouil <htouil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 18:29:13 by htouil            #+#    #+#             */
/*   Updated: 2024/02/14 19:19:43 by htouil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	*ft_realloc(void *ptr, int size)
{
	void	*res;

	res = malloc(size);
	if (res == NULL)
		return (NULL);
	ft_memcpy(res, ptr, size);
	free(ptr);
	return (res);
}

int	ft_strlcmp(char *s1, char *s2, int n)
{
	if (ft_strncmp(s1, s2, n) == 0)
		return (0);
	return (1);
}

int	check_double_nl(char *lmap)
{
	int		i;

	i = 0;
	while (lmap[i] != '\0')
	{
		if (lmap[i] == '\n')
		{
			i++;
			while (lmap[i] != '\0' && (lmap[i] == ' ' || lmap[i] == '\t'))
				i++;
			if (lmap[i] == '\0')
				return (0);
			else if (lmap[i] == '\n')
			{
				i++;
				while (lmap[i] != '\0' && (lmap[i] == ' ' || lmap[i] == '\t'))
					i++;
				if (lmap[i] == '\0' || lmap[i] == '\n')
					return (1);
			}
		}
		i++;
	}
	return (0);
}

void	free_data(t_map *map)
{
	int	j;

	j = -1;
	while (++j < map->rows)
	{
		if (map->map[j])
			free(map->map[j]);
	}
	if (map->map)
		free(map->map);
	if (map->no)
		free(map->no);
	if (map->so)
		free(map->so);
	if (map->we)
		free(map->we);
	if (map->ea)
		free(map->ea);
	if (map->f)
		free(map->f);
	if (map->c)
		free(map->c);
	if (map->columns)
		free(map->columns);
	free(map);
}

void	free_tmp(char **str)
{
	int	j;

	j = 0;
	while (str[j])
	{
		if (str[j])
			free(str[j]);
		j++;
	}
	free(str);
}
