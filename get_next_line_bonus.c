/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrigny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:41:41 by yrigny            #+#    #+#             */
/*   Updated: 2023/12/05 14:42:14 by yrigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	free_stash(t_list **p_stash)
{
	t_list	*temp;

	if (!(*p_stash))
		return ;
	while (*p_stash)
	{
		temp = (*p_stash)->next;
		free((*p_stash)->content);
		free(*p_stash);
		*p_stash = temp;
	}
}

void	clean_stash(t_list **p_stash, int line_len)
{
	int	i;
	int	j;

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
		else
		{
			j = i;
			while ((*p_stash)->content[i])
				i++;
			ft_memcpy((*p_stash)->content, (*p_stash)->content + j,
					i - j);
			return ;
		}
	}
}

int	copy_line(t_list *stash, char **p_line)
{
	int		line_len;
	char	*line;
	int		i;
	int		j;

	line_len = count_line_len(stash);
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
	t_list	*new;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (0);
	*p_bytes_read = read(fd, buf, BUFFER_SIZE);
	if (*p_bytes_read <= 0)
	{
		free(buf);
		return (*p_bytes_read == 0);
	}
	buf[*p_bytes_read] = '\0';
	new = malloc(sizeof(t_list));
	if (!new)
		return (0);
	new->content = malloc(*p_bytes_read + 1);
	if (!new->content)
		return (0);
	ft_memcpy(new->content, buf, *p_bytes_read);
	free(buf);
	new->next = NULL;
	ft_lstadd_back(p_stash, new);
	return (1);
}

char	*get_next_line(int fd)
{
	static t_list	*stashes[MAX_FDS];
	char			*line;
	ssize_t			bytes_read;
	int				line_len;
	int				malloc_ok;

	line = NULL;
	bytes_read = 1;
	line_len = 0;
	malloc_ok = 1;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
		return (line);
	while (bytes_read > 0 && (!stashes[fd] || !find_endl(stashes[fd])))
	{
		malloc_ok = read_n_stash(fd, &bytes_read, &stashes[fd]);
		if (!malloc_ok && stashes[fd])
			free_stash(&stashes[fd]);
	}
	if (stashes[fd] && (find_endl(stashes[fd]) || bytes_read < BUFFER_SIZE))
		line_len = copy_line(stashes[fd], &line);
	if (line_len > 0)
		clean_stash(&stashes[fd], line_len);
	return (line);
}
