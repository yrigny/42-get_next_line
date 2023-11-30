/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrigny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:19:19 by yrigny            #+#    #+#             */
/*   Updated: 2023/11/30 17:15:37 by yrigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

char	*get_next_line(int fd)
{
	char		buf[BUFFER_SIZE];
	ssize_t		bytes_read;
	char		*line;
	int		i;

	bytes_read = read(fd, buf, BUFFER_SIZE - 1);
	if (bytes_read > 0)
		buf[bytes_read] = '\0';
	printf("%zd bytes read\n", bytes_read);
	printf("buf: %s\n", buf);
	i = 0;
	while (buf[i] != '\n')
		i++;
	line = (char *)malloc(i + 2);
	line = strncpy(line, buf, i + 1);
	return (line);
}

int	main()
{
	int	fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("Error opening file");
		return (EXIT_FAILURE);
	}
	for (int i = 1; i < 3; i++)
	{
		line = get_next_line(fd);
		printf("%s\n", line);
		free(line);
	}
	close(fd);
	return (EXIT_SUCCESS);
}
