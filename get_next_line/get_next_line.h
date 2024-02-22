/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htouil <htouil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 22:03:04 by htouil            #+#    #+#             */
/*   Updated: 2024/02/14 19:02:43 by htouil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 15
# endif

char	*get_next_line(int fd);
char	*ft_read(int fd, char *cell);
char	*get_one_line(char *cell);
char	*get_new_line(char *cell);
char	*ft_strjoin1(char *str1, char *str2);
int		ft_strlen1(char *str);
int		ft_strchr1(char *searched);

#endif
