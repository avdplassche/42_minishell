
#include "../../includes/minishell.h"

// char	*get_env_value(t_mini *mini, char *variable)
// {




// }



/** To handle lines starting with '$'
 *
 */
int	handle_dollar_sign(t_mini *mini, t_cmd *cmd)
{
	/* This isn't the right way to process ,
	we actually only need to replace '$?' by int error*/

	if (ft_strlen(mini->line) == 1)   // line = $
		return (printf("command not found\n"), -1);
	if (ft_strncmp("$?", mini->line, 2) == 0)
		return (printf("%d: command not found\n", mini->last_return), 0);
	if (contain_string_at_specific_index(mini->line, "$? ", 0))
		return (printf("%d command not found\n", mini->last_return));
	if (contain_string_at_specific_index(mini->line, "$?", 0))
		return (printf("%d: command not found\n", mini->last_return), 0);
	return (0);
}
