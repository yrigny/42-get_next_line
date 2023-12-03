/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yifanr <yifanr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:19:19 by yrigny            #+#    #+#             */
/*   Updated: 2023/12/03 00:37:57 by yifanr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	clean_stash(t_list **p_stash, int line_len)
{
	int		i;
	int		j;

	j = 0;
	while (*p_stash && j < line_len)
	{
		i = 0;
		while ((*p_stash)->content[i] && j + i < line_len)
			i++;
		if (j + i <= line_len && !(*p_stash)->content[i])
		{
			ft_lstdel_front(p_stash);
			j += i;
		}
		else // j + i == line_len && content[i]
		{
			j = i;
			while ((*p_stash)->content[i])
			{
				(*p_stash)->content[i - j] = (*p_stash)->content[i];
				i++;
			}
			(*p_stash)->content[i - j] = '\0';
			return ;
		}
	}
}

int	copy_line(t_list *stash, char **p_line)
{
	char	*line;
	int		line_len;
	int		i;
	int		j;

	line_len = count_line_len(stash);
	printf("%d\n", line_len);
	line = malloc(line_len + 1);
	if (!line)
		return (0);
	j = 0;
	while (stash && j < line_len)
	{
		i = 0;
		while (stash->content[i] && j + i < line_len)
		{
			line[j + i] = stash->content[i];
			i++;
		}
		j += i;
		stash = stash->next;
	}
	line[j] = '\0';
	*p_line = line;
	return (line_len);
}

int	read_n_stash(int fd, ssize_t *p_bytes_read, t_list **p_stash)
{
	char	*buf;
	int		i;
	t_list	*new;

	buf = malloc(BUFFER_SIZE + 1);
	*p_bytes_read = read(fd, buf, BUFFER_SIZE);
	if (*p_bytes_read <= 0)
		return (0);
	buf[*p_bytes_read] = '\0';
	new = malloc(sizeof(t_list));
	if (!new)
		return (0);
	new->content = malloc(BUFFER_SIZE + 1);
	if (!new->content)
		return (0);
	i = 0;
	while (i < *p_bytes_read)
	{
		new->content[i] = buf[i];
		i++;
	}
	free(buf);
	new->content[i] = '\0';
	new->next = NULL;
	if (!(*p_stash))
		*p_stash = new;
	else
		ft_lstlast(*p_stash)->next = new;
	return (1);
}

char	*get_next_line(int fd)
{
	static t_list	*stash;
	char			*line;
	ssize_t			bytes_read;
	int				line_len;

	line = NULL;
	bytes_read = 1;
	line_len = 0;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
		return (line);
	while (bytes_read > 0 && (!stash || !find_endl(ft_lstlast(stash))))
		read_n_stash(fd, &bytes_read, &stash);
	if (stash && (find_endl(ft_lstlast(stash)) || bytes_read < BUFFER_SIZE))
		line_len = copy_line(stash, &line);
	if (line_len > 0)
		clean_stash(&stash, line_len);
	return (line);
}

int	main()
{
	int	fd;
	char	*line;

//	fd = open("test.txt", O_RDONLY);
	fd = 0;
	if (fd == -1)
	{
		printf("Error opening file");
		return (EXIT_FAILURE);
	}
	for (int i = 1; i < 6; i++)
	{
		line = get_next_line(fd);
		printf("%s\n", line);
		free(line);
	}
	close(fd);
	return (EXIT_SUCCESS);
}
