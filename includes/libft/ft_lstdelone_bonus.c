/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:09:11 by jrandet           #+#    #+#             */
/*   Updated: 2024/11/02 15:34:58 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	del(lst->content);
	free(lst);
}

/*int main()
{
	t_list *lst;
	t_list *el;

	lst = NULL;
	for (int i = 0; i < 3; i++)
		ft_lstadd_back(&lst, ft_lstnew(malloc(42)));
	printf("the length of the chained list is %d\n", ft_lstsize(lst));

	el = lst->next;
	lst->next = el->next;
	ft_lstdelone(el, &free);
	printf("the length of the chained list is %d\n", ft_lstsize(lst));

	return (0);
}*/
