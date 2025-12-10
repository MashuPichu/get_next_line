/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klucchin <klucchin@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 20:54:59 by klucchin          #+#    #+#             */
/*   Updated: 2025/12/10 16:37:18 by klucchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_strlen(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return(i);
}
char	*extract_line(char *stash)
{
	char	*line;
	int		i = 0;

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
	int	i;
	int j;
	char *new_stash;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] && stash[i] != 'n')
		i++;
	if (!stash[i])
		return(free(stash), NULL);
	new_stash = malloc(ft_strlen(stash) - i + 1);
	if (!new_stash)
		return (NULL);
	i = 0;
	j = 0;
	while (stash[i])
	{
		new_stash[j] = stash[i];
		i++;
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

	while (!ft_strchr(stash, '\n') && bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes <= 0)
			return (free(stash), NULL);
		buffer[bytes] = '\0';
		stash = ft_strjoin(stash, buffer);
		if (!stash)
			return(NULL);
	}
	return (stash);
}

char	*get_next_line_bonus(int fd)
{
    static char *stash[4096];
    char        *line;

	if( fd < 0 || fd >= 4096 || BUFFER_SIZE <= 0)
		return (NULL);
	stash[fd] = read_and_fill(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	line = extract_line(stash[fd]);
	stash[fd] = remove_first_line(stash[fd]);
	return (line);
}
// #include <stdio.h>

// int main()
// {
//     int fd1 = open("file1.txt", O_RDONLY);
//     int fd2 = open("file2.txt", O_RDONLY);

//     char *l1, *l2;

//     for (int i = 0; i < 5; i++)
//     {
//         l1 = get_next_line_bonus(fd1);
//         l2 = get_next_line_bonus(fd2);
//         printf("F1: %s", l1);
//         printf("F2: %s", l2);
//         free(l1);
//         free(l2);
//     }
//     return 0;
// }