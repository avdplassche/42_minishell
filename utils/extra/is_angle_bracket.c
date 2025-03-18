
#include "../includes/minishell.h"

int	is_angle_bracket(char c)
{
	if (c == '>' || c == '<')
		return (1);
	return (0);
}
