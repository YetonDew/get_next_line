/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeffers <ajeffers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 14:17:09 by ajeffers          #+#    #+#             */
/*   Updated: 2025/10/28 14:56:08 by ajeffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*_set_line(char *line_buffer)
{
	char	*remainer;
	ssize_t	i;

	if (!line_buffer || !*line_buffer)
		return (NULL);
	i = 0;
	while (line_buffer[i] != '\n' && line_buffer[i] != '\0')
		i++;
	if(line_buffer[i] == '\n')
		remainer = ft_substr(line_buffer, 0, i + 1);
	else
		remainer = ft_substr(line_buffer, 0, i);
	return (remainer);
}
char	*new_remainer(char *line_buffer)
{
	char	*remainer;
	ssize_t	i;

	if (!line_buffer)
		return (NULL);
	i = 0;
	while (line_buffer[i] != '\n' && line_buffer[i] != '\0')
		i++;
	if (line_buffer[i] == '\0')
	{
		free(line_buffer);
		return (NULL);
	}
	remainer = ft_strdup(line_buffer + i + 1);
	free(line_buffer);
	return (remainer);
}

char	*_fill_line_buffer(int fd, char *remainer)
{
	ssize_t	bytes_read;
	char	*temp;
	char		*buffer;

	buffer = malloc((BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(remainer, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(buffer),NULL);
		buffer[bytes_read] = '\0';
		if (!remainer)
			temp = ft_strdup(buffer);
		else
			temp = ft_strjoin(remainer, buffer);
		free(remainer);
		remainer = temp;
		if (!remainer)
			return (free(buffer), NULL);
	}
	free(buffer);
	return (remainer);
}

char	*get_next_line(int fd)
{
	static char	*remainer[FD_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	remainer[fd] = _fill_line_buffer(fd, remainer[fd]);
	if (!remainer[fd])
		return (NULL);
	line = _set_line(remainer[fd]);
	remainer[fd] = new_remainer(remainer[fd]);
	return (line);
}
