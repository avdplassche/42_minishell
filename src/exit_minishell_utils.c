
#include "minishell.h"

/** Frees char ** variables
 */
void	free_string_array(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_wildcard_struct(t_wildcard *w)
{
	if (w->dirname)
	{
		free(w->dirname);
		w->dirname = NULL;
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
}

void	free_pathnames(t_cmd cmd)
{
	int	i;

	i = 0;
	// DEBUG("Redir Amount : %d\n\n", cmd->redir_amount);
	while (i < cmd.redir_amount)
	{
		free(cmd.redir[i].name);
		i++;
	}
	free(cmd.redir);
}
