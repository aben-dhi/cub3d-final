/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htouil <htouil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 15:21:00 by aben-dhi          #+#    #+#             */
/*   Updated: 2024/01/06 22:34:29 by htouil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	char	*dst;

	if (s1 == NULL || set == NULL)
		return (NULL);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	len = ft_strlen(s1);
	while (len && ft_strchr(set, s1[len]))
		len--;
	dst = ft_substr((char *)s1, 0, len + 1);
	return (dst);
}
// #include <stdio.h>
// #include <unistd.h>
// int	main()
// {
// 	char	*tmp;
// 	char	*dst;

// 	tmp = " textures/1.xpm\n";
// 	dst = ft_strtrim(tmp, " \n");
// 	printf("trimmed: (%s)", dst);
// 	// sleep(10);
// 	system("leaks salam");
// 	return (0);
// }
