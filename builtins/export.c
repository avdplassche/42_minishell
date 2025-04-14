
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

static char	*extract_key(t_mini *mini, char *arg)
{
	char	*env_key;
	int		len;

	len = 0;
	while (arg[len] && arg[len] != '=')
		len++;
	env_key = (char *)malloc(sizeof(char) * (len + 1));
	if (!env_key)
		mini->last_return = MALLOC_ERROR;
	ft_strlcpy(env_key, arg, len + 1);
	return (env_key);
}


static void	check_if_valid_arg(t_mini *mini, t_cmd *cmd, int is_declaration)
{
	int		i;
	char	*env_key;

	i = 0;
	while (++i <= cmd->arg_amount)
	{
		if (ft_strchr(cmd->args[i], '='))
		{
			env_key = extract_key(mini, cmd->args[i]);
			is_declaration = 1;
		}
		else
			env_key = cmd->args[i];
		if (!(is_valid_argument(env_key)))
		{
			if (is_declaration)
				free(env_key);
			print_error("Minishell: '%s': not a valid identifier", cmd->args[i], 2);
			mini->last_return = CMD_NOT_FOUND;
		}
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
	int	is_declaration;

	is_declaration = 0;	
	if (!mini->export)
		create_export(mini, cmd);
	if (cmd->arg_amount == 0)
	{
		sort_and_add_prefix(mini, cmd);
		string_array_print(cmd, mini->export);
	}
	if (cmd->arg_amount > 0)
	{
		check_if_valid_arg(mini, cmd, is_declaration);
	}
	return (mini->last_return);
}
