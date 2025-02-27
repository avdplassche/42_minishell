
#include "../../includes/minishell.h"


/** To handle lines starting with '$'
 *
 */
int	handle_dollar_sign(t_mini *mini, t_cmd *cmd)
{
	/* This isn't the right way to process */
	/* Actually, we only need to replace '$?' by int error*/

	if (ft_strlen(mini->current_line) == 1)   // line = $
		return (printf("command not found\n"), -1);
	if (ft_strncmp("$?", mini->current_line, 2) == 0)
		return (printf("%d: command not found\n", mini->last_return), 0);
	if (contain_string_at_specific_index(mini->current_line, "$? ", 0))
		return (printf("%d command not found\n", mini->last_return));
	if (contain_string_at_specific_index(mini->current_line, "$?", 0))
		return (printf("%d: command not found\n", mini->last_return), 0);
	return (0);
}
