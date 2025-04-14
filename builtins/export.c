
#include "minishell.h"

static int	is_valid_argument(char *str)
{
	int	i;

	i = 0;
	if (!str || !ft_isalpha(str[0]) || str[0] == '_')
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!(ft_isalnum(str[i])) || str[i] == '_')
		{
			return (0);
		}
		i++;
	}
	return (1);
}

static void	treat_export_argument(t_mini *mini, t_cmd *cmd)
{
	int	i;

	(void)mini;
	i = 1;
	while (i <= cmd->arg_amount)
	{
		if (is_valid_argument(cmd->args[i]))
		{
			mini->last_return = 0;
		}
		else
		{
			print_error("Minishell: export: '%s': not a valid identifier\n", cmd->args[i], 2);
		}
		i++;
	}
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

static void	create_export(t_mini *mini, t_cmd *cmd)
{
	int		i;
	char	*tmp;

	if (mini->export)
    {
		free_string_array(&mini->export);
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
		treat_export_argument(mini, cmd);
	}
	return (mini->last_return);
}