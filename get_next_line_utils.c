/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yifanr <yifanr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 01:53:11 by yifanr            #+#    #+#             */
/*   Updated: 2023/12/03 00:52:30 by yifanr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	find_endl(t_list *node)
{
	int		i;

	i = 0;
	while (node->content[i])
    {
		if (node->content[i] == '\n')
			return (1);
        i++;
    }
	return (0);
}

int	count_line_len(t_list *stash)
{
	int		line_len;
	int		i;

	line_len = 0;
	while (stash)
	{
		i = 0;
		while (stash->content[i])
        {
            if (stash->content[i] == '\n')
            {
                line_len += i + 1;
                return (line_len);
            }
            i++;
        }
        line_len += i;
		stash = stash->next;
	}
	return (line_len);
}

void    ft_lstdel_front(t_list **p_lst)
{
    t_list  *temp;

    if (!(*p_lst))
        return ;
    temp = (*p_lst)->next;;
    free((*p_lst)->content);
    free(*p_lst);
    *p_lst = temp;
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}