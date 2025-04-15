
#include "minishell.h"


void	create_export(t_mini *mini, t_cmd *cmd)
{
	int		i;
	char	**temp;

	if (mini->export)
    {
        i = 0;
        while (mini->export[i])
        {
            free(mini->export[i]);
			mini->export[i] = NULL;
            i++;
        }
        free(mini->export);
        mini->export = NULL;
    }
	i = 0;
	//DEBUG("BIG BIG BIG ENV print\n");
	//string_array_print(cmd, mini->envp);
	while (mini->envp[i])
		i++;
	temp = (char **)malloc(sizeof(char *) * (i + 1));
	if (!temp)
		exit_minishell(mini, mini->cmd);
	i = 0;
	while (mini->envp[i])
	{
		temp[i] = ft_strdup(mini->envp[i]);
		if (!temp[i])
		{
			exit_minishell(mini, cmd);
		}
		i++;
	}
	//DEBUG("BIG BIG BIG ENV print\n");
	temp[i] = NULL;
	//string_array_print(cmd, temp);
	mini->export = temp;
}