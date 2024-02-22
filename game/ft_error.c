/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 20:52:22 by aben-dhi          #+#    #+#             */
/*   Updated: 2024/02/22 11:39:21 by aben-dhi         ###   ########.fr       */
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

// void	free_game(t_game *game)
// {
// 	free(game->map);
// 	free(game->chars[0]->ray);
// 	free(game->chars[0]);
// 	free(game->chars);
// 	free(game->textures);
// 	free(game->mlx);
// 	free(game);
// }
