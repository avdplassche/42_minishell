
#include "minishell.h"

/**
 * To create the key format of the variable in the env array
 * @param variable is the name of the variable like "PATH"
 * @param variablelen is the length (int) of the variable
 * @return - the new string with the equal sign "PATH=""
 *
 * @return - NULL if malloc error 
 * @note mainly used in execution 
 */
char *string_array_create_key(char *variable, int variable_len)
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
