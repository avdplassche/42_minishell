/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:59:09 by alvan-de          #+#    #+#             */
/*   Updated: 2025/04/14 14:59:10 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** Is c a quote charactere ?
 * @param c a character
 * @return 1 for yes, 0 for no
 * @note 34 =  "
 * @note 39 =  '
 */
int	is_quote(char c)
{
	if (c == 34 || c == 39)
		return (1);
	return (0);
}
