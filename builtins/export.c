
#include "minishell.h"

static void	create_export(t_mini *mini, t_cmd *cmd)
{
	int		i;
	char	*tmp;

	if (mini->export)
    {
        i = 0;
        while (mini->export[i])
        {
            free(mini->export[i]);
            i++;
        }
        free(mini->export);
        mini->export = NULL;
    }
	i = 0;
	while (mini->envp[i])
		i++;
	mini->export = (char **)malloc(sizeof(char *) * (i + 1));
	if (!mini->export)
		exit_minishell(mini, mini->cmd);
	i = -1;
	while (mini->envp[++i])
	{
		tmp = mini->envp[i];
		mini->export[i] = ft_strdup(tmp);
		if (!mini->export[i])
		{
			exit_minishell(mini, cmd);
		}
	}
	mini->export[i] = NULL;
}

static void	sort_and_add_prefix(t_mini *mini, t_cmd *cmd)
{
	mini->export = add_export_prefix(mini->export);
	if (!mini->export)
	{
		mini->last_return = MALLOC_ERROR;
		exit_minishell(mini, cmd);
	}
	sort_ascii_array(mini->export, string_array_len(mini->export));
}

static void	modify_export_array(t_mini *mini, t_cmd *cmd)
{
	char	**temp_env;

	temp_env = string_array_push(mini->export, cmd->args[1]);
	if (!temp_env)
	{
		mini->last_return = MALLOC_ERROR;
		return ;
	}
	if (mini->export)
	{
		free(mini->export);
	}
	mini->export = temp_env;
	return ;
}

static int	is_already_in_envp(t_mini *mini, t_cmd *cmd)
{
	int i;
	int	j;

	i = 0;
	j = 1;
	while (mini->envp[i] && j <= cmd->arg_amount)
	{
		DEBUG("entered the is already in envp function\n");
		if (string_array_find_string(mini->export, cmd->args[j]) != NULL)
		{
			mini->last_return = CMD_NOT_FOUND;
			return (1);
		}
		i++;
		j++;
	}
	return (0);
}

static int	is_leading_int(t_mini *mini, t_cmd *cmd)
{
	int	i;
	
	i = 1;
	while (i <= cmd->arg_amount)
	{
		if (ft_isdigit(cmd->args[i][0]))
		{
			print_error("Minishell: '%s': not a valid identifier\n", cmd->args[i], 2);
			mini->last_return = CMD_NOT_FOUND;
			return (1);
		}
		i++;
	}
	return (0);
}

int	builtin_export(t_mini *mini, t_cmd *cmd)
{
	if (!mini->export)
		create_export(mini, cmd);
	if (cmd->arg_amount == 0)
	{
		sort_and_add_prefix(mini, cmd);
		string_array_print(cmd, mini->export);
	}
	if (cmd->arg_amount > 0)
	{
		if (is_leading_int(mini, cmd))
		{
			return (mini->last_return);
		}

		if (!is_already_in_envp(mini, cmd))
		{
			modify_export_array(mini, cmd);
		}
		sort_and_add_prefix(mini, cmd);
	}
	return (mini->last_return);
}
