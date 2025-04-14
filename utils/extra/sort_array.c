/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:59:26 by alvan-de          #+#    #+#             */
/*   Updated: 2025/04/14 14:59:27 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_array(char **filename, int len)
{
	int		i;
	int		j;
	char	*temp;

	if (len <= 1)
		return ;
	while (len > 0)
	{
		i = 0;
		j = 1;
		while (j < len)
		{
			if (ft_strcmp_alpha(filename[i], filename[j]) > 0)
			{
				temp = filename[i];
				filename[i] = filename[j];
				filename[j] = temp;
			}
			i++;
			j++;
		}
		len --;
	}
}
