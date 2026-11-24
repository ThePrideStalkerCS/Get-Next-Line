/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maratana <maratana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/24 17:28:55 by maratana          #+#    #+#             */
/*   Updated: 2026/11/24 20:30:09 by maratana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*join_free(char *storage, char *buffer)
{
	char	*temp;

	temp = ft_strjoin(storage, buffer);
	free(storage);
	return (temp);
}

char	*read_first_line(int fd, char *storage)
{
	char	*buffer;
	int		bytes_read;

	if (!storage)
		storage = ft_calloc(1, 1);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(storage);
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = 0;
		storage = join_free(storage, buffer);
		if (ft_strchr(storage, '\n'))
			break ;
	}
	free(buffer);
	return (storage);
}

char	*get_line(char *str)
{
	int		i;
	char	*line;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] && str[i] == '\n')
		line[i++] = '\n';
	return (line);
}

char	*remove_line(char *storage)
{
	char	*leftover;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (storage[i] && storage[i] != '\n')
		i++;
	if (!storage[i])
	{
		free(storage);
		return (NULL);
	}
	leftover = malloc(ft_strlen(storage) - i + 1);
	if (!leftover)
		return (NULL);
	while (storage[++i])
		leftover[j++] = storage[i];
	leftover[j] = '\0';
	free(storage);
	return (leftover);
}

char	*get_next_line(int fd)
{
	char		*output;
	static char	*storage;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	storage = read_first_line(fd, storage);
	if (!storage)
		return (NULL);
	output = get_line(storage);
	storage = remove_line(storage);
	return (output);
}

//  int main()
// {
// 	int fd = open("test.txt", O_RDONLY);
// 	char *a;

// 	while ((a = get_next_line(fd)))
// 	{
// 		printf("%s", a);
// 	}

// 	// printf("%s", get_next_line(fd));

// 	return (0);
// }