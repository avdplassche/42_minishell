/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 10:39:24 by jrandet           #+#    #+#             */
/*   Updated: 2024/11/02 15:57:21 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

t_list	*ft_newnode_start(void *new_content)
{
	t_list	*new_node;

	new_node = ft_lstnew(new_content);
	if (!new_node)
	{
		free(new_content);
		return (NULL);
	}
	return (new_node);
}

t_list	*ft_newnode(t_list **head, t_list **new_head, void *(*f)(void *), \
					void (*del)(void *))
{
	void	*new_content;
	t_list	*new_node;

	new_content = f((*head)->content);
	if (!new_content)
	{
		ft_lstclear(new_head, del);
		return (NULL);
	}
	new_node = ft_lstnew(new_content);
	if (!new_node)
	{
		del(new_content);
		ft_lstclear(new_head, del);
		return (NULL);
	}
	return (new_node);
}

t_list	*ft_lstmap(t_list *head, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_head;
	t_list	*new_node;
	t_list	*current;

	if (!head || !f || !del)
		return (NULL);
	new_node = ft_newnode_start(f(head->content));
	if (!new_node)
		return (NULL);
	new_head = new_node;
	current = new_head;
	head = head->next;
	while (head)
	{
		new_node = ft_newnode(&head, &new_head, f, del);
		if (!new_node)
			return (ft_lstclear(&new_head, del), NULL);
		current->next = new_node;
		current = current->next;
		head = head->next;
	}
	return (new_head);
}

/*void *triple_int(void *content)
{
	int *result;

	result = malloc(sizeof(int));
	if (result == NULL)
		return (NULL);
	*result = (*(int *)content) * 3;
	return (result);
}

int main()
{
	t_list	*head = NULL;
	t_list	*mapped_head;
	t_list	*current;
	int *n;

	for (int i = 0; i < 3; i++)
	{
		n = malloc(sizeof(int));
		*n = i + 2;
		ft_lstadd_front(&head, ft_lstnew(n));
	}
	current = head;
	while (current)
	{
		printf("the content of the node is %d\n", *(int *)current->content);
		current = current->next;
	}
	mapped_head = ft_lstmap(head, triple_int, free);
	current = mapped_head;
	while (current)
	{
		printf("the content of the node is %d\n", *(int *)current->content);
		current = current->next;
	}
	ft_lstclear(&head, free);
	ft_lstclear(&mapped_head, free);
	
	return (0);
}*/