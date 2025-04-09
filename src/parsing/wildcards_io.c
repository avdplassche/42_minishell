
#include "minishell.h"

void	init_wildcard_struct(t_wildcard *w)
{
	w->wildcard = NULL;
	w->dirname = NULL;
	w->token = NULL;
	w->s_dir = NULL;
	w->prefix = NULL;
	w->suffix = NULL;
	w->current = false;
}

void	free_wildcard_struct(t_wildcard *w)
{
	if (w->dirname)
		free_string_ptr(w->dirname);
	if (w->wildcard)
		free_string_ptr(w->dirname);
	if (w->token)
		free_string_ptr(w->token);
	if (w->s_dir)
	{
		free(w->s_dir);
		w->s_dir = NULL;
	}
	if (w->prefix)
		free_string_ptr(w->prefix);
	if (w->suffix)
		free_string_ptr(w->suffix);
}

void	str_malloc_wildcard_check(t_mini *mini, t_wildcard *w, char *str)
{
	if (!str)
	{
		free_wildcard_struct(w);
		exit_minishell(mini, mini->cmd);
	}
}

void	free_wildcards(char *temp, char *temp2, char **list, t_wildcard *w)
{
	free(temp2);
	free(temp);
	if (w->file_amount > 1)
		free_string_array(list);
	else
		free(list);
	free_wildcard_struct(w);
}
