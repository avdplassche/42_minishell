
#include "minishell.h"

char *create_env_key_format(char *variable, int variable_len)
{
	char	*key_format_variable;
	int		i;
	//char	*current;
	
	i = 0;
	key_format_variable = (char *)malloc(sizeof(char) * (variable_len + 2));
	if (!key_format_variable)
		return (NULL);
	while (variable[i])
	{
		key_format_variable[i] = variable[i];
		i++;
	}
	key_format_variable[i] = '=';
	i++;
	key_format_variable[i] = '\0';
	return (key_format_variable);
}
