/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yifanr <yifanr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 05:12:06 by yifanr            #+#    #+#             */
/*   Updated: 2023/12/03 05:12:22 by yifanr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H

# define GET_NEXT_LINE_BONUS_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50
# endif

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}			t_list;

typedef struct s_info
{
	int				fd;
	t_list			*stash;
	struct s_info	*next;
}				t_info;

char	*get_next_line(int fd);
int		read_n_stash(int fd, ssize_t *p_bytes_read, t_info *fdinfo);
int		count_line_len(t_list *stash);
int		find_endl(t_list *stash);
void	copy_line(t_list *stash, char **p_line);
void	clean_stash(t_list **p_stash, int line_len);
void	ft_lstdel_front(t_list **p_lst);
void	ft_lstadd_back(t_list **p_lst, t_list *new);
void	ft_memcpy(char *dest, char *src, size_t n);
t_info	*find_stash(int fd, t_info **p_fdbook);

#endif