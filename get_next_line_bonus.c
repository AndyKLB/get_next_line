/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 12:48:44 by ankammer          #+#    #+#             */
/*   Updated: 2024/01/22 14:41:19 by ankammer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*keep_stash(char *stash)
{
	size_t	i;
	char	*new_stash;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	new_stash = ft_substr(stash, i + 1, ft_strlen(stash) - i);
	free(stash);
	return (new_stash);
}

char	*get_ret_line(char *stash)
{
	size_t	i;
	char	*line;

	i = 0;
	if (!stash)
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	line = ft_substr(stash, 0, i);
	return (line);
}

char	*ft_read_fd(int fd, char *stash)
{
	ssize_t	read_bytes;
	char	*buff;

	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	read_bytes = 1;
	while (read_bytes != 0)
	{
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if (read_bytes == -1)
			return (free(buff), NULL);
		if (read_bytes == 0 && (!stash || *stash == '\0'))
			break ;
		buff[read_bytes] = '\0';
		if (!stash)
			stash = ft_strdup("");
		stash = ft_strjoin(stash, buff);
		if (ft_strchr(stash, '\n'))
			break ;
	}
	free(buff);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash[4096];
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash[fd] = ft_read_fd(fd, stash[fd]);
	if (!stash[fd] || stash[fd][0] == '\0')
	{
		free(stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	line = get_ret_line(stash[fd]);
	if (!line || *line == '\0')
		return (free(line), free(stash[fd]), NULL);
	stash[fd] = keep_stash(stash[fd]);
	if (stash[fd] && stash[fd][0] == '\0')
	{
		free(stash[fd]);
		stash[fd] = NULL;
	}
	return (line);
}

/*#include <stdio.h>
#include <fcntl.h>

int	main(int ac, char **av) {
	int fd = open(av[1], O_RDONLY);
	char *str;
	(void)ac;

	while ((str = get_next_line(fd))) {
		printf("%s", str);
		free(str);
	}
	free(str);
}
*/