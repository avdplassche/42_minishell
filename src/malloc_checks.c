/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 00:49:58 by jrandet           #+#    #+#             */
/*   Updated: 2025/04/26 00:50:01 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	str_malloc_check(t_mini *mini, char *str)
{
	if (!str)
		exit_minishell(mini);
}

void	dbl_str_malloc_check(t_mini *mini, char **str)
{
	if (!str)
		exit_minishell(mini);
}
