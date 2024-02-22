/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htouil <htouil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 18:55:14 by aben-dhi          #+#    #+#             */
/*   Updated: 2024/02/14 19:19:33 by htouil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*ft_datacpy(char *src, int n)
{
	char	*dst;
	char	*tmp;
	int		i;
	int		j;

	if (!src)
		return (NULL);
	i = n;
	while (src[i] == ' ' || src[i] == '\t')
		i++;
	tmp = malloc((ft_strlen1(src) - i + 1) * sizeof(char));
	if (!tmp)
		exit(1);
	j = 0;
	while (src[i] != '\0' && src[i] != '\n')
	{
		tmp[j] = src[i];
		i++;
		j++;
	}
	tmp[j] = '\0';
	dst = ft_strtrim(tmp, "\n ");
	free(tmp);
	return (dst);
}

char	*skip_spaces(char *str)
{
	while (*str && (*str == ' ' || *str == '\t'))
		str++;
	return (str);
}

int	avoid_spaces(char *str)
{
	int	pos;

	pos = 0;
	while (str[pos] && (str[pos] == ' ' || str[pos] == '\t'))
		pos++;
	return (pos);
}

int	reverse_avoid_spaces(char *str)
{
	int	pos;

	pos = ft_strlen1(str) - 1;
	while (str[pos] && (str[pos] == ' ' || str[pos] == '\t'))
		pos--;
	return (pos);
}

int	check_empty_spaces(char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[0] == '\0'
			|| (str[i] != ' ' && str[i] != '\t' && str[i] != '\n'))
		{
			tmp = str;
			tmp = skip_spaces(tmp);
			if (ft_strlcmp(tmp, "NO", 2) == 0 || ft_strlcmp(tmp, "SO", 2) == 0
				|| ft_strlcmp(tmp, "WE", 2) == 0
				|| ft_strlcmp(tmp, "EA", 2) == 0
				|| ft_strlcmp(tmp, "F", 1) == 0 || ft_strlcmp(tmp, "C", 1) == 0)
				return (2);
			return (1);
		}
		i++;
	}
	return (0);
}
