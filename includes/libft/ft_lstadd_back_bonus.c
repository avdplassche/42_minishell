/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:06:42 by jrandet           #+#    #+#             */
/*   Updated: 2024/11/02 15:25:47 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (!(*lst))
	{
		(*lst) = new;
		return ;
	}
	temp = (*lst);
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
}

/*int main()
{
	t_list *lst;

	lst = NULL;
	for (int d = 0; d < 5; d++)
		ft_lstadd_back(&lst, ft_lstnew(NULL));
	printf("the size of the linked chain is %d\n", ft_lstsize(lst));

	return (0);
}*/
