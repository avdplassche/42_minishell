#include "minishell.h"

void	free_cmd(t_mini *mini, t_cmd **cmd)
{
	int	i;

	i = -1;
	while (++i < mini->cmd_amount)
	{
		if ((*cmd)[i].command != NULL)
			free((*cmd)[i].command);
		if ((*cmd)[i].path != NULL)
			free((*cmd)[i].path);
		if ((*cmd)[i].args != NULL)
			free_double_pointer((*cmd)[i].args);
	}
	free((*cmd));
	*cmd = NULL;
}

/** Frees char ** variables
 */
void	free_string_array(char **str)
{
	int	i;

	if (!(str))
		return ;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

/** Frees t_mini mini, used when leaving minishell
 *maybe when signals exit the program
 */
void	free_mini(t_mini *mini)
{
	if (mini->envp)
		free_string_array(mini->envp);
	if (mini->builtins)
		free_string_array(mini->builtins);
	if (mini->paths)
		free_string_array(mini->paths);
	if (mini->fd_backup)
		free((mini)->fd_backup);
	if (mini->pipes)
		free(mini->pipes);
	
}

void	minishell_exit(t_mini *mini, t_cmd *cmd)
{
	free_cmd(mini, cmd);
	free_mini(mini);
}


//FOR THE MAIN FUNCTION 
/** Frees components of t_mini mini, used when the structure itself is stack-allocated
 */
void free_mini_components(t_mini *mini)
{
    if (mini->envp)
        free_string_array(mini->envp);
    if (mini->builtins)
        free_string_array(mini->builtins);
    if (mini->paths)
        free_string_array(mini->paths);
    if (mini->fd_backup)
    {
        free(mini->fd_backup);
        mini->fd_backup = NULL;
    }
    // Do NOT free mini itself since it's stack-allocated
}