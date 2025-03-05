/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:57:08 by jrandet           #+#    #+#             */
/*   Updated: 2024/11/02 15:51:11 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

/*int main()
{
	t_list *lst;

	lst = NULL;
	for (int i = 0; i < 3; i++)
		ft_lstadd_back(&lst, ft_lstnew(NULL));
	printf("the current adress in lst is %p\n", lst);
	printf("the list is complete, the last node's add is %p\n", ft_lstlast(lst));

	return (0);
}*/