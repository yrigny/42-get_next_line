/* ************************************************************************** */
/*									      */
/*							  :::	   ::::::::   */
/*   get_next_line_utils.c				:+:	 :+:	:+:   */
/*						      +:+ +:+	      +:+     */
/*   By: yifanr <yifanr@student.42.fr>		    +#+  +:+	   +#+	      */
/*						  +#+#+#+#+#+	+#+	      */
/*   Created: 2023/12/02 01:53:11 by yifanr	       #+#    #+#	      */
/*   Updated: 2023/12/03 03:57:23 by yifanr	      ###   ########.fr       */
/*									      */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_memcpy(char *dest, char *src, size_t n)
{
	while (n-- > 0)
		*(char *)dest++ = *(char *)src++;
	*(char *)dest++ = '\0';
}

int	find_endl(t_list *stash)
{
	int	i;

	while (stash->next)
		stash = stash->next;
	i = 0;
	while (stash->content[i])
	{
		if (stash->content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int	count_line_len(t_list *stash)
{
	int	line_len;
	int	i;

	line_len = 0;
	while (stash)
	{
		i = 0;
		while (stash->content[i] && stash->content[i] != '\n')
			i++;
		if (stash->content[i] == '\n')
		{
			line_len += i + 1;
			return (line_len);
		}
		line_len += i;
		stash = stash->next;
	}
	return (line_len);
}

void	ft_lstdel_front(t_list **p_lst)
{
	t_list	*temp;

	if (!(*p_lst))
		return ;
	temp = (*p_lst)->next;
	free((*p_lst)->content);
	free(*p_lst);
	*p_lst = temp;
}

void	ft_lstadd_back(t_list **p_lst, t_list *new)
{
	t_list	*temp;

	temp = *p_lst;
	if (!(*p_lst))
		*p_lst = new;
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}
