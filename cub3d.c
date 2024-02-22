/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 18:42:06 by aben-dhi          #+#    #+#             */
/*   Updated: 2024/02/22 11:42:26 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//we're going to proceed with checking the map first
//then we'll proceed with the window
//the first thing we need to do is to check if the map is valid
//extension is .cub
//we'll do that by checking if the map is surrounded by walls
//
void	init_params(t_map *map)
{
	map->rows = 0;
	map->columns = 0;
	map->file = NULL;
	map->no = NULL;
	map->so = NULL;
	map->we = NULL;
	map->ea = NULL;
	map->f = NULL;
	map->c = NULL;
	map->map = NULL;
	map->tmp = NULL;
	map->max = 0; 
	map->n_chars = 0;
}

int	setup_game_data(char **av, t_map *map)
{
	int		fd;

	if (check_extension(av[1]) == 0)
	{
		free(map);
		return (ft_putstr_fd("Error\nInvalid file extension!\n", 2), 1);
	}
	init_params(map);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		free(map);
		return (ft_putstr_fd("Error\nInvalid file!\n", 2), 1);
	}
	read_map(fd, map);
	display_map_errors1(map);
	display_map_errors2(map);
	return (0);
}

int	main(int ac, char **av)
{
	t_map	*map;
	t_game	*game;

	if (ac == 2)
	{
		map = malloc(sizeof(t_map));
		game = malloc(sizeof(t_game));
		if (!map || !game)
			return (1);
		if (setup_game_data(av, map) == 1)
			return (1);
		game = alloc_game(map);
		init_game(game);
		mlx_loop(game->mlx);
		free(game);
		system("leaks cub3D");
	}
	else
		return (ft_error("Error\nInvalid number of arguments!\n", 2), 1);
	free_data(map);
	return (0);
}
