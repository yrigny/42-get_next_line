/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrigny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:37:12 by yrigny            #+#    #+#             */
/*   Updated: 2023/12/05 14:37:20 by yrigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}			t_list;

char	*get_next_line(int fd);
int		read_n_stash(int fd, ssize_t *p_bytes_read, t_list **p_stash);
int		count_line_len(t_list *stash);
int		find_endl(t_list *stash);
int		copy_line(t_list *stash, char **p_line);
void	clean_stash(t_list **p_stash, int line_len);
void	ft_lstdel_front(t_list **p_lst);
void	ft_lstadd_back(t_list **p_lst, t_list *new);
void	ft_memcpy(char *dest, char *src, size_t n);
void	free_stash(t_list **p_stash);

#endif
