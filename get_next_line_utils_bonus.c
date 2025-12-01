/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klucchin <klucchin@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 20:56:27 by klucchin          #+#    #+#             */
/*   Updated: 2025/12/01 15:45:27 by klucchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strchr(const char *s, int c)
{
	int i;

	if (!s)
		return (NULL);

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}

	if (c == '\0')
		return ((char *)&s[i]);

	return (NULL);
}

static char	*managelen(size_t *len, size_t s_len, unsigned int start)
{
	char	*sub;

	if (*len > s_len - start)
		*len = s_len - start;
	sub = (char *)malloc(sizeof(char) * (*len + 1));
	if (!sub)
		return (NULL);
	return (sub);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
	{
		sub = (char *)malloc(1);
		if (!sub)
			return (NULL);
		sub[0] = '\0';
		return (sub);
	}
	sub = managelen(&len, s_len, start);
	i = 0;
	while (i < len && s[start + i])
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

static char	*mallocing(size_t i, size_t j, char const *s1, char const *s2)
{
	char	*s3;

	i = 0;
	while (s1[i] != '\0')
		i++;
	j = 0;
	while (s2[j] != '\0')
		j++;
	s3 = malloc(i + j + 1);
	return (s3);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	size_t	i;
	size_t	k;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	s3 = mallocing(i, 0, s1, s2);
	k = 0;
	while (s1[k] != '\0')
	{
		s3[k] = s1[k];
		k++;
	}
	i = 0;
	while (s2[i] != '\0')
	{
		s3[k] = s2[i];
		k++;
		i++;
	}
	s3[k] = 0;
	return (s3);
}
