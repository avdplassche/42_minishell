
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
	char	*env_key;
	int		i;
	
	i = 0;
	env_key = (char *)malloc(sizeof(char) * (variable_len + 2));
	if (!env_key)
		return (NULL);
	while (variable[i])
	{
		env_key[i] = variable[i];
		i++;
	}
	env_key[i] = '=';
	i++;
	env_key[i] = '\0';
	return (env_key);
}
