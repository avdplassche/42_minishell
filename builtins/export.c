
#include "minishell.h"

static void	add_to_export(t_mini *mini, char *arg)
{
	char	**temp_env;
	
	if (string_array_find_string(mini->export, arg) != NULL)
		return ;
	temp_env = string_array_push(mini->export, arg);
	if (!temp_env)
	{
		mini->last_return = MALLOC_ERROR;
		return ;
	}
	if (mini->export)
	{
		free_string_array(&mini->export);
	}
	mini->export = temp_env;
}

static void	process_assignment(t_mini *mini, t_cmd *cmd, char *arg, char *env_key)
{
	char	*env_row;
	char	*env_key_with_equal;

	
	env_row = ft_strdup(arg);
	if (!env_row)
	{
		mini->last_return = MALLOC_ERROR;
		return ;
	}
	env_key_with_equal = ft_strjoin(env_key, "=");
	if (!env_key_with_equal)
	{
		free(env_key);
		free(env_row);
		mini->last_return = MALLOC_ERROR;
		return ;
	}
	free(env_key);
	set_env(mini, env_key_with_equal, env_row);
	if (mini->export)
	{
		free_string_array(&mini->export);
		create_export(mini, cmd);
	}
}

static int	is_valid_argument(char *str)
{
	int	i;

	i = 0;
	if (!str || !(ft_isalpha(str[0])))
		return (0);
	while (str[i] && str[i] != '=')
	{
		if ((!(ft_isalnum(str[i])) || str[i] == '_'))
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
	DEBUG("env_key ius worth %s\n", env_key);
	return (env_key);
}

static void	process_export_args(t_mini *mini, t_cmd *cmd)
{
	int		i;
	char	*env_key;

	i = 0;
	while (++i <= cmd->arg_amount)
	{
		env_key = extract_key(mini, cmd->args[i]);
		if (!env_key)
		{
			mini->last_return = MALLOC_ERROR;
		}
		printf("env_key is worht %s\n", env_key);
		if (!is_valid_argument(env_key))
		{
			print_error("Minishell: '%s': not a valid identifier\n", cmd->args[i], 2);
			mini->last_return = CMD_NOT_FOUND;
			free(env_key);
			env_key = NULL;
		}
		if (ft_strchr(cmd->args[i], '='))
			process_assignment(mini, cmd, cmd->args[i], env_key);
		else
		{
			add_to_export(mini, cmd->args[i]);
			free(env_key);
			env_key = NULL;
		}
	}
}

int	builtin_export(t_mini *mini, t_cmd *cmd)
{
	if (!mini->export)
		create_export(mini, cmd);
	if (cmd->arg_amount == 0)
	{
		sort_ascii_array(mini->export, string_array_len(mini->export));
		string_array_print(cmd, mini->export);
	}
	if (cmd->arg_amount > 0)
	{
		process_export_args(mini, cmd);
	}
	sort_ascii_array(mini->export, string_array_len(mini->export));
	return (mini->last_return);
}