/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbayra <malbayra@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 03:55:28 by malbayra          #+#    #+#             */
/*   Updated: 2024/10/26 03:59:56 by malbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (lst == NULL || *lst == NULL)
		return ;
	while (*lst)
	{
		if (del != NULL && (*lst)->content != NULL)
			del((*lst)->content);
		temp = *lst;
		*lst = temp->next;
		free(temp);
	}
	*lst = NULL;
}
