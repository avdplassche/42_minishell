#include "minishell.h"

void	str_malloc_check(t_mini *mini, char *str)
{
	if (!str)
		exit_minishell(mini, mini->cmd);
}

void	dbl_str_malloc_check(t_mini *mini, char **str)
{
	if (!str)
		exit_minishell(mini, mini->cmd);
}
