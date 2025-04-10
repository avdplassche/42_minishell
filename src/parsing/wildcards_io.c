
#include "minishell.h"

void	init_wildcard_struct(t_wildcard *w)
{
	w->wildcard = NULL;
	w->dirname = NULL;
	w->token = NULL;
	w->s_dir = NULL;
	w->prefix = NULL;
	w->suffix = NULL;
	w->temp = NULL;
	w->file_list = NULL;
	w->current = false;
}

void	str_safe_free(char **str)
{
	free(*str);
	*str = NULL;
}

void	free_wildcard_struct(t_wildcard *w)
{
	if (w->dirname)
	{
		free(w->dirname);
		w->dirname = NULL;
	}
	if (w->wildcard)
	{
		free(w->wildcard);
		w->wildcard = NULL;
	}
	if (w->token)
	{
		free(w->token);
		w->token = NULL;
	}
	if (w->s_dir)
	{
		free(w->s_dir);
		w->s_dir = NULL;
	}
	if (w->prefix)
	{
		free(w->prefix);
		w->prefix = NULL;
	}
	if (w->suffix)
	{
		free(w->suffix);
		w->suffix = NULL;
	}
	if (w->temp)
	{
		free(w->temp);
		w->temp = NULL;
	}
	// if (w->file_list)
	// 	free_string_array(w->file_list);

}

void	str_malloc_wildcard_check(t_mini *mini, t_wildcard *w, char *str)
{
	if (!str)
	{
		free_wildcard_struct(w);
		exit_minishell(mini, mini->cmd);
	}
}
void	wildcard_file_list_malloc_check(t_mini *mini, t_wildcard *w)
{
	if (!w->file_list)
	{
		free_wildcard_struct(w);
		exit_minishell(mini, mini->cmd);
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
