/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klucchin <klucchin@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 20:54:59 by klucchin          #+#    #+#             */
/*   Updated: 2025/12/11 15:59:56 by klucchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

	bytes = BUFFER_SIZE;
	while (!ft_strchr(stash, '\n') && bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes <= 0)
			return (free(stash), NULL);
		buffer[bytes] = '\0';
		stash = ft_strjoin(stash, buffer);
		if (!stash)
			return (NULL);
	}
	return (stash);
}

char	*get_next_line_bonus(int fd)
{
	static char	*stash[4096];
	char		*line;

	if (fd < 0 || fd >= 4096 || BUFFER_SIZE <= 0)
		return (NULL);
	stash[fd] = read_and_fill(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	line = extract_line(stash[fd]);
	stash[fd] = remove_first_line(stash[fd]);
	return (line);
}

// #include <stdio.h>

// int	main(void)
// {
// 	int fd = open("file1.txt", O_RDONLY);
// 	int fd2 = open ("file2.txt", O_RDONLY);

// 	while (1)
// 	{
// 		char *l = get_next_line_bonus(fd);
// 		printf("%s", l);
// 		char *l2 = get_next_line_bonus(fd2);
// 		printf("%s", l2);
// 		if (!l && !l2)
// 			break ;
// 	}
// 	// while (1)
// 	// {
// 	// 	char *l2 = get_next_line_bonus(fd2);
// 	// 	printf("%s", l2);
// 	// 	if (!l2)
// 	// 		break ;
// 	// }
// 	close(fd);
// 	close(fd2);
// 	return (0);
// }
