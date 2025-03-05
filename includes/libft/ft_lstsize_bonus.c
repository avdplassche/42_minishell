/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:56:32 by jrandet           #+#    #+#             */
/*   Updated: 2024/11/02 15:57:43 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	size_t	list_len;

	list_len = 0;
	if (!lst)
		return (0);
	while (lst != NULL)
	{
		lst = lst->next;
		list_len++;
	}
	return (list_len);
}

/*int main()
{

}*/