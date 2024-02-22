/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htouil <htouil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 22:02:45 by htouil            #+#    #+#             */
/*   Updated: 2024/01/13 22:40:24 by htouil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen1(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin1(char *str1, char *str2)
{
	int		i;
	int		j;
	char	*joined;

	if (!str1)
	{
		str1 = malloc(1 * sizeof(char));
		str1[0] = '\0';
	}
	joined = malloc((ft_strlen1(str1) + ft_strlen1(str2) + 1) * sizeof(char));
	if (!joined)
		return (NULL);
	i = -1;
	j = 0;
	while (str1[++i])
		joined[i] = str1[i];
	while (str2[j])
		joined[i++] = str2[j++];
	joined[i] = '\0';
	free (str1);
	return (joined);
}

int	ft_strchr1(char *searched)
{
	int	i;

	if (!searched)
		return (0);
	i = 0;
	while (searched[i] != '\0')
	{
		if (searched[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}
