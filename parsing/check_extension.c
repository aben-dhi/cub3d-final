/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_extension.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htouil <htouil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 20:01:23 by htouil            #+#    #+#             */
/*   Updated: 2024/02/14 18:48:04 by htouil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_extension(char *file)
{
	char	*ext;
	int		len;

	ext = ft_strrchr(file, '.');
	len = ft_strlen1(ext);
	if (!ext || len != 4 || ext[len - 1] != 'b' || ext[len - 2] != 'u'
		|| ext[len - 3] != 'c' || ext[len - 4] != '.')
		return (0);
	return (1);
}
