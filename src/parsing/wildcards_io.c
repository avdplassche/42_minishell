
#include "minishell.h"

void	init_wildcard_struct(t_wildcard *w)
{
	w->dirname = NULL;
	w->token = NULL;
	w->s_dir = NULL;
	w->prefix = NULL;
	w->suffix = NULL;
	w->current = false;
}

void	free_wildcards(char *temp, char *temp2, char **list, int file_amount)
{
	free(temp2);
	free(temp);
	if (file_amount > 1)
		free_string_array(list);
	else
		free(list);
}

