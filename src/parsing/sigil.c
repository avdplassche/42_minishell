
#include "../../includes/minishell.h"

int	get_envp_index(t_mini *mini, char *variable)
{
	int	i;
	int	j;
	int	k;
	int	len;

	i = 0;
	len = ft_strlen(variable);
	while (mini->envp[i])
	{
		j = 0;
		k = 0;
		while (variable[k])
			if (mini->envp[i][j++] != variable[k++])
				break ;
		if (k == len)
			return (i);
		i++;
	}
	return (-1);
}

/** Used to change every sigil sign to elements of env variable
 * @param mini t_mini struct where envp is stored
 * @param str the string to change sigil sign if needed
 * @return errors
*/
int	translate_sigil_sign(t_mini *mini, char *temp)
{
	int		i;
	int		j;
	t_quote	quote;
	char	*variable_name;

	j = 0;
	quote.sgl = 0;
	quote.dbl = 0;
	i = -1;
	while (temp[++i] && temp[i] != '$' && quote.sgl == 0)
		quote_enclosure_handle(temp[i], &quote);
	while (temp[++i] && (temp[i] != ' ') && temp[i] != 34)
		j++;
	variable_name = ft_substr(temp, i - j, j + 1);
	variable_name[j] = '=';
	variable_name[j + 1] = '\0';
	printf("name : %s$\n", variable_name);
	int	k = get_envp_index(mini, variable_name);
	printf("Index : %d -> %s\n", k, mini->envp[k]);

	// print_char_table(mini->envp, "envp");
	printf("\n\n");
	return (0);
}

/** Do the string needs a sigil sign sub ?
 * @param str the string to scan
 * @return 1 yes
 * @return 0 no
*/
int	need_sigil_sub(char *str)
{
	int		i;
	t_quote	quote;

	if (!(contain_char(str, '$')))
		return (0);
	quote.sgl = 0;
	quote.dbl = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '$' && quote.sgl == 0)
			return (1);
		quote_enclosure_handle(str[i], &quote);
	}
	return (0);
}

/** To handle lines starting with '$'
 *
 */
int	handle_sigil_sign(t_mini *mini, t_cmd *cmd)
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
