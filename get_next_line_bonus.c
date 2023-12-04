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

#include "get_next_line_bonus.h"

void	clean_stash(t_list **p_stash, int line_len)
{
	int	i;
	int	j;
printf("test\n");
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

void	copy_line(t_list *stash, char **p_line)
{
	int		line_len;
	char	*line;
	int		i;
	int		j;

	line_len = count_line_len(stash);
	line = malloc(line_len + 1);
	if (!line)
		return ;
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
	if (line_len > 0)
		clean_stash(&stash, line_len);
}

int	read_n_stash(int fd, ssize_t *p_bytes_read, t_info *fdinfo)
{
	char	*buf;
	t_list	*new;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (0);
	*p_bytes_read = read(fd, buf, BUFFER_SIZE);
	if (*p_bytes_read <= 0 && !(fdinfo->next))
	{
		free(fdinfo);
		return (0);
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
	ft_lstadd_back(&(fdinfo->stash), new);
	return (1);
}

t_info	*find_stash(int fd, t_info **p_fdbook)
{
	t_info	*newfd;
	t_info	*temp;

	newfd = NULL;
	temp = *p_fdbook;
	while (temp && temp->fd != fd)
		temp = temp->next;
	if (temp && temp->fd == fd)
		return (temp);
	newfd = malloc(sizeof(t_info));
	if (!newfd)
		return (NULL);
	newfd->fd = fd;
	newfd->stash = NULL;
	newfd->next = NULL;
	if (!(*p_fdbook))
		*p_fdbook = newfd;
	else
		temp = newfd;
	return (newfd);
}

char	*get_next_line(int fd)
{
	static t_info	*fdbook;
	t_info			*fdinfo;
	t_info			*temp;
	char			*line;
	ssize_t			bytes_read;

	temp = NULL;
	fdinfo = NULL;
	line = NULL;
	bytes_read = 1;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
		return (line);
	fdinfo = find_stash(fd, &fdbook);
	while (bytes_read > 0 && (!fdinfo->stash || !find_endl(fdinfo->stash)))
		read_n_stash(fd, &bytes_read, fdinfo);
	if (bytes_read <= 0 && fdinfo && fdinfo->next)
	{
		temp = fdinfo->next;
		fdinfo->fd = temp->fd;
		fdinfo->stash = temp->stash;
		fdinfo->next = temp->next;
		free(temp);
	}
	if (fdinfo->stash && (find_endl(fdinfo->stash) || bytes_read < BUFFER_SIZE))
		copy_line(fdinfo->stash, &line);
printf("%s\n", fdinfo->stash->content);
	return (line);
}
