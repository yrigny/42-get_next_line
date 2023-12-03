/* ************************************************************************** */
/*									      */
/*							  :::	   ::::::::   */
/*   get_next_line.c					:+:	 :+:	:+:   */
/*						      +:+ +:+	      +:+     */
/*   By: yifanr <yifanr@student.42.fr>		    +#+  +:+	   +#+	      */
/*						  +#+#+#+#+#+	+#+	      */
/*   Created: 2023/11/30 16:19:19 by yrigny	       #+#    #+#	      */
/*   Updated: 2023/12/03 04:30:30 by yifanr	      ###   ########.fr       */
/*									      */
/* ************************************************************************** */

#include "get_next_line.h"

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
			ft_memcpy((*p_stash)->content, (*p_stash)->content + j, i - j);
			return ;
		}
	}
}

void	copy_line(t_list *stash, char **p_line, int *p_line_len)
{
	char	*line;
	int		i;
	int		j;

	*p_line_len = count_line_len(stash);
	line = malloc(*p_line_len + 1);
	if (!line)
		return ;
	j = 0;
	while (stash && j < *p_line_len)
	{
		i = 0;
		while (stash->content[i] && j + i < *p_line_len)
		{
			line[j + i] = stash->content[i];
			i++;
		}
		j += i;
		stash = stash->next;
	}
	line[j] = '\0';
	*p_line = line;
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
		return (0);
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
	static t_list	*stash;
	char			*line;
	ssize_t			bytes_read;
	int				line_len;

	line = NULL;
	bytes_read = 1;
	line_len = 0;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
		return (line);
	while (bytes_read > 0 && (!stash || !find_endl(stash)))
		read_n_stash(fd, &bytes_read, &stash);
	if (stash && (find_endl(stash) || bytes_read < BUFFER_SIZE))
		copy_line(stash, &line, &line_len);
	if (line_len > 0)
		clean_stash(&stash, line_len);
	return (line);
}
