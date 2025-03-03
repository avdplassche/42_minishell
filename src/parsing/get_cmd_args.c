#include "../../includes/minishell.h"

/** Fill cmd arg tokens, a char** that will be used in execve
 * @param cmd_line the command line from the prompt
 * @param cmd_struct the command structure to fill
 * @return error ? not set yet
 *
 */
// int	get_cmd_args(t_mini *mini, t_cmd *cmd_struct)
// {
// 	int		i;
// 	int		j;
// 	char	*arg;

// 	j = 0;
// 	i = mini->cursor;
// 	while (is_space(mini->line[i]) || is_quote(mini->line[i]))
// 		i++;
// 	j = i;
// 	while (mini->line[i] && contain_char("|<>", mini->line[i]))
// 		i++;
// 	arg = malloc(sizeof(char) * (i - j + 1));
// 	//malloc

// 	/* NOT FINISHED*/

// 	return (0);
// }
