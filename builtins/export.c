
#include "minishell.h"

static void add_empty_string_assignment(t_mini *mini, t_cmd *cmd, char *env_key)
{
	char	*formated_env_key;
	char	*empty_string = "\" \"";
	char	*new_env_entry;
	
	formated_env_key = ft_strjoin(env_key, "=");
	free(env_key);
	if (!formated_env_key)
	{
		mini->last_return = MALLOC_ERROR;
		return ;
	}
	empty_string = ft_strdup(" \"\" ");
	if (!empty_string)
	{
		mini->last_return = MALLOC_ERROR;
		return ;
	}
	new_env_entry = ft_strjoin(formated_env_key, empty_string);
	free(empty_string);
	if (!new_env_entry)
	{
		free(formated_env_key);
		mini->last_return = MALLOC_ERROR;
		return ;
	}
	set_env(mini, formated_env_key, new_env_entry);
	free(new_env_entry);
	// if (mini->export)
	// {
	// 	free_string_array(&mini->export);
	// 	create_export(mini, cmd);
	// }
	//printf("\n\n\n\nDEBUG EXPORT\n\n\n\n");
	//string_array_print(cmd, mini->export);
}

static int	is_valid_env_identifier(char *str)
{
	int	char_index;
	
	char_index = 0;
	if (!str || !(ft_isalpha(str[0])))
	return (0);
	while (str[char_index] && str[char_index] != '=')
	{
		if (!(ft_isalnum(str[char_index]) || str[char_index] == '_'))
		{
			return (0);
		}
		char_index++;
	}
	return (1);
}

static char	*extract_key(t_mini *mini, char *arg)
{
	char	*env_key;
	int		key_length;
	
	key_length = 0;
	while (arg[key_length] && arg[key_length] != '=')
		key_length++;
	env_key = (char *)malloc(sizeof(char) * (key_length + 1));
	if (!env_key)
		mini->last_return = MALLOC_ERROR;
	ft_strlcpy(env_key, arg, key_length + 1);
	return (env_key);
}

static void	add_to_export(t_mini *mini, char *arg)
{
	char	**new_export_array;
	
	if (string_array_find_string(mini->export, arg) != NULL)
		return ;
	new_export_array = string_array_push(mini->export, arg);
	if (!new_export_array)
	{
		mini->last_return = MALLOC_ERROR;
		return ;
	}
	if (mini->export)
		free_string_array(&mini->export);
	mini->export = new_export_array;
}

static void	process_assignment(t_mini *mini, t_cmd *cmd, char *arg, char *env_key)
{
	char	*env_entry;
	char	*formated_env_key;
	
	env_entry = ft_strdup(arg);
	if (!env_entry)
	{
		mini->last_return = MALLOC_ERROR;
		return ;
	}
	if (ft_strchr(env_entry, '=') && *(ft_strchr(env_entry, '=') + 1) == '\0')
	{
		free(env_entry);
		add_empty_string_assignment(mini, cmd, env_key);
	}
	else
	{
		formated_env_key = ft_strjoin(env_key, "=");
		if (!formated_env_key)
		{
			free(env_key);
			free(env_entry);
			mini->last_return = MALLOC_ERROR;
			return ;
		}
		free(env_key);
		set_env(mini, formated_env_key, env_entry);
		if (mini->export)
		{
			free_string_array(&mini->export);
			create_export(mini, cmd);
		}
	}
}

static void	process_export_args(t_mini *mini, t_cmd *cmd)
{
	int		arg_index;
	char	*env_key;

	arg_index = 0;
	while (++arg_index <= cmd->arg_amount)
	{
		env_key = extract_key(mini, cmd->args[arg_index]);
		if (!env_key)
			mini->last_return = MALLOC_ERROR;
		if (!is_valid_env_identifier(env_key))
		{
			print_error("Minishell: '%s': not a valid identifier\n", cmd->args[arg_index], 2);
			mini->last_return = CMD_NOT_FOUND;
			free(env_key);
			env_key = NULL;
		}
		if (ft_strchr(cmd->args[arg_index], '='))
			process_assignment(mini, cmd, cmd->args[arg_index], env_key);
		else
		{
			add_to_export(mini, cmd->args[arg_index]);
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