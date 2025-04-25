/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_io.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:40:05 by alvan-de          #+#    #+#             */
/*   Updated: 2025/04/25 21:19:07 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_wildcard_struct(t_wildcard *w)
{
	if (w->dirname)
		free_string_ptr(&w->dirname);
	if (w->wildcard)
		free_string_ptr(&w->wildcard);
	if (w->token)
		free_string_ptr(&w->token);
	if (w->prefix)
		free_string_ptr(&w->prefix);
	if (w->suffix)
		free_string_ptr(&w->suffix);
	if (w->temp)
		free_string_ptr(&w->temp);
	if (w->s_dir)
	{
		free(w->s_dir);
		w->s_dir = NULL;
	}
}

void	str_malloc_wildcard_check(t_mini *mini, t_wildcard *w, char *str)
{
	if (!str)
	{
		free_wildcard_struct(w);
		exit_minishell(mini);
	}
}

void	wildcard_file_list_malloc_check(t_mini *mini, t_wildcard *w)
{
	if (!w->file_list)
	{
		free_wildcard_struct(w);
		exit_minishell(mini);
	}
}

void	free_wildcard_double_pointer_first_part(t_mini *mini, t_wildcard*w)
{
	int	i;

	i = 0;
	while (w->file_list[i])
		i++;
	while (--i <= 0)
	{
		free(w->file_list[i]);
		w->file_list[i] = NULL;
	}
	free(w->file_list);
	w->file_list = NULL;
	wildcard_file_list_malloc_check(mini, w);
}

void	free_wildcards(char *line, t_wildcard *w)
{
	free(line);
	line = NULL;
	if (w->file_amount > 1)
		free_string_array(&w->file_list);
	else if (w->file_list)
	{
		free(w->file_list);
		w->file_list = NULL;
	}
	free_wildcard_struct(w);
}
