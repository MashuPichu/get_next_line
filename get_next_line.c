/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klucchin <klucchin@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 20:49:45 by klucchin          #+#    #+#             */
/*   Updated: 2025/12/12 22:33:29 by klucchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*extract_line(char *stash)
{
	char	*line;
	int		i;

	i = 0;
	if (!stash || !stash[0])
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*remove_first_line(char *stash)
{
	int		i;
	int		j;
	char	*new_stash;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] && stash[i] == '\n')
		i++;
	if (!stash[i])
		return (free(stash), NULL);
	new_stash = malloc(ft_strlen(stash) - i + 1);
	if (!new_stash)
		return (NULL);
	j = 0;
	while (stash[i + j])
	{
		new_stash[j] = stash[i + j];
		j++;
	}
	new_stash[j] = '\0';
	free(stash);
	return (new_stash);
}

static char	*read_and_fill(int fd, char *stash)
{
	char	buffer[BUFFER_SIZE + 1];
	int		bytes;
	char	*temp;

	bytes = BUFFER_SIZE;
	while (!ft_strchr(stash, '\n') && bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
			return (free(stash), NULL);
		if (bytes == 0)
			return (stash);
		buffer[bytes] = '\0';
		temp = ft_strjoin(stash, buffer);
		if (!temp)
			return (free(stash), NULL);
		stash = temp;
	}
	return (stash);
}

// char	*get_next_line(int fd)
// {
// 	static char	*stash;
// 	char		*line;

// 	if (fd < 0 || BUFFER_SIZE <= 0)
// 		return (NULL);
// 	stash = read_and_fill(fd, stash);
// 	if (!stash)
// 		return (NULL);
// 	line = extract_line(stash);
// 	stash = remove_first_line(stash);
// 	return (line);
// }

// #include <stdio.h>

// int	main(void)
// {
// 	int fd = open("file2.txt", O_RDONLY);
// 	char *l;

// 	while (1)
// 	{
// 		l = get_next_line(fd);
// 		if (!l)
// 		{
// 			free(l);
// 			break ;
// 		}
// 		printf("%s", l);
// 		free(l);
// 	}
// 	close(fd);
// 	return (0);
// }