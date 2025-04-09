
#include "minishell.h"

char	**string_array_copy(t_mini *mini, t_cmd *cmd, char **src)
{
	char	**dest;
	char	**cursor;
	
	if (src == NULL)
		return (NULL);
	dest = (char **)malloc(sizeof(char *) * string_array_len(mini->envp));
	if (!dest)
	{
		mini->last_return = MALLOC_ERROR;
		exit_minishell(mini, cmd);
	}
	cursor = dest;
	while (*src)
	{
		*cursor = *src;
		cursor++;
		src++;
	}
	*cursor = NULL;
	return (dest);
}
