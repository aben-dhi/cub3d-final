/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 20:52:22 by aben-dhi          #+#    #+#             */
/*   Updated: 2024/04/01 22:53:49 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_error(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
		write(fd, &s[i++], 1);
	return (1);
}

void	free_arrs(t_game *game)
{
	int	i;

	i = 0;
	mlx_delete_image(game->mlx, game->chars[0]->ray->img);
	free(game->chars[0]->ray);
	while (i < game->map->n_chars)
	{
		mlx_delete_image(game->mlx, game->chars[i]->img);
		free(game->chars[i]);
		i++;
	}
	free(game->chars);
}

void	free_exit(t_game *game)
{
	free_arrs(game);
	mlx_delete_image(game->mlx, game->map->floor);
	mlx_delete_image(game->mlx, game->map->wall);
	mlx_delete_image(game->mlx, game->map->out);
	mlx_delete_image(game->mlx, game->game_img);
	mlx_terminate(game->mlx);
	free(game->textures->wall);
	free(game->textures->floor);
	free(game->textures);
	free(game->settings);
	free(game);
}
