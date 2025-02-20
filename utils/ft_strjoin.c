/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:14:22 by alvan-de          #+#    #+#             */
/*   Updated: 2025/02/20 02:11:21 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*dest;

	i = 0;
	j = 0;
	while (s1[i])
		i++;
	while (s2[j])
		j++;
	dest = malloc(sizeof(char) * (i + j + 1));
	if (!dest)
		return (NULL);
	j = -1;
	i = -1;
	while (s1[++i])
		dest[i] = s1[i];
	while (s2[++j])
		dest[i++] = s2[j];
	dest[i] = '\0';
	return (dest);
}
/*
int main (void)
{
	char *s1 = "aaaaa";
	char *s2 = "bbbb";
	printf("%s", ft_strjoin(s1, s2));
	return (0);
}
*/
