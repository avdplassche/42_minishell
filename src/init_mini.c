
#include "../includes/minishell.h"

/** Count command amount in command line, that will be used for pipes.
 * @param mini t_mini containing the command line
 * @return number of commands
 * @note proceed by countint pipe char '|'
 */
int	count_cmd(t_mini *mini)
{
	int		i;
	int		count;
	t_quote	q;

	count = 1;
	i = -1;
	q.dbl = 0;
	q.sgl = 0;
	while (mini->line[++i])
	{
		quote_enclosure_handle(mini->line[i], &q);
		if (mini->line[i] == '|' && !q.sgl && !q.dbl)
			count++;
	}
	return (count);
}

/** Function for env to be used everywhere and to iterate on its values
 * @param mini an empty t_mini_structure
 * @param envp the terminal env variable
 * @note this is for minishell to have it's own env variable
 */
int	dup_env(t_mini *mini, char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
		i++;
	mini->envp = (char **)malloc(sizeof(char *) * (i + 1));
		//malloc protection
	i = -1;
	while (envp[++i])
	{
		mini->envp[i] = ft_strdup(envp[i]);
		//double malloc protection
	}
	mini->envp[i] = NULL;
	return (0);
}

/** Fill t_mini mini's variable
 * @param mini an empty t_mini_structure
 * @param envp the terminal env variable
 */
int	init_mini(t_mini *mini, char **envp)
{
	mini->builtins = ft_split(BUILTINS_STRING, ',');
		//malloc protection
	mini->last_return = 0;
	dup_env(mini, envp);
	mini->paths = ft_split(getenv("PATH"), ':');
		//malloc protection
	// mini->cursor = 0;
	mini->fd_backup = (t_fd_backup *)malloc(sizeof(t_fd_backup));
	if (!mini->fd_backup)
		return (MALLOC_ERROR);
	mini->fd_backup->stdin_backup = -1;
	mini->fd_backup->stdout_backup = -1;
	mini->fd_backup->stderr_backup = -1;

	return (0);
}


