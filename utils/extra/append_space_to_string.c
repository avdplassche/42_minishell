#include "minishell.h"

void	append_space_to_string(char **str)
{
	char	*temp; 

	temp = ft_strdup(*str);
	free(*str);
	*str = NULL;
	*str = ft_strjoin(temp, " ");
	free(temp);
	temp = NULL;
}
