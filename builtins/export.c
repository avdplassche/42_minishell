
#include "minishell.h"

static char	*extract_identifier(t_mini *mini, char *src)
{
	int		char_index;
	char	*identifier;

	char_index = 0;
	while (src[char_index] && src[char_index] != '=')
		char_index++;
	identifier = (char *)malloc(sizeof(char) * (char_index + 1));
	if (!identifier)
		mini->last_return = MALLOC_ERROR;
	ft_strlcpy(identifier, src, char_index + 1);
	return (identifier);
}

static int	is_valid_env_identifier(char *str)
{
	int	char_index;
	
	char_index = 0;
	if (!str || (!(ft_isalpha(str[0])) && (str[0] != '_')))
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

void	process_export_args(t_mini *mini, t_cmd *cmd)
{
	int		arg_index;
	char	*identifier;
	char	*env_key;
	char	*env_entry;

	arg_index = 0;
	while (++arg_index <= cmd->arg_amount)
	{
		
		identifier = extract_identifier(mini, cmd->args[arg_index]);
		if (!identifier)
		{
			mini->last_return = MALLOC_ERROR;
			return ;
		}
		if (!is_valid_env_identifier(cmd->args[arg_index]))
		{
			free_string_ptr(&identifier);
			print_error("Minishell: '%s': not a valid identifier\n", cmd->args[arg_index], 2);
			mini->last_return = CMD_NOT_FOUND;
		}
		if (ft_strchr(cmd->args[arg_index], '='))
		{
			env_key = ft_strjoin(identifier, "=");
			env_entry = ft_strdup(cmd->args[arg_index]);
			free_string_ptr(&identifier);
		}
		else
		{
			env_key = ft_strjoin(identifier, "=");
			env_entry = ft_strdup(identifier);
			free_string_ptr(&identifier);
		}
		if (env_key && env_entry)
		{
			set_env(mini, env_key, env_entry);
			free_string_ptr(&env_key);
			free_string_ptr(&env_entry);
		}
		else
		{
			free_string_ptr(&env_key);
			free_string_ptr(&env_entry);
			mini->last_return = MALLOC_ERROR;
			return ;
		}
	}

}

int	builtin_export(t_mini *mini, t_cmd *cmd)
{
	if (cmd->arg_amount == 0)
	{
		sort_ascii_array(mini->envp, string_array_len(mini->envp));
		string_array_print(cmd, mini->envp);
	}
	else if (cmd->arg_amount > 0)
	{
		process_export_args(mini, cmd);
	}
	return (mini->last_return);
}