

#include "../../includes/minishell.h"

/** Fill command structure (for 1 command of the command line)
 * @param mini t_mini structure, containing current line to work with
 * @param cmd_s an empty structure that the function will fill
 * @return not set yet, errors
*/
char	*clean_command_quotes(t_cmd *cmd, char *str)
{
	int		first_quote;
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (!(is_quote(str[++i])))
		j++;
	first_quote = str[i];
	while (str[++i])
		if (str[i] != first_quote)
			j++;
	i = -1;
	cmd->command = malloc(sizeof(char) * (j + 1));
		//malloc protection
	j = 0;
	while (str[++i])
		if (str[i] != first_quote)
			cmd->command [j++] = str[i];
	cmd->command [j] = '\0';
	return (0);
}

int	get_last_index(t_mini *mini)
{
	int	i;
	int	d_quote;
	int	s_quote;
	char charset[4] = " <>|";

	i = 0;
	d_quote = 0;
	s_quote = 0;
	while (mini->line[i])
	{
		if (contain_char(charset, mini->line[i]))
			if (!s_quote && !d_quote && i)
				return (i);
		if (mini->line[i] == 34 && d_quote == 0)
			d_quote = 1;
		else if (mini->line[i] == 34 && d_quote == 1)
			d_quote = 0;
		else if (mini->line[i] == 39 && s_quote == 0)
			s_quote = 1;
		else if (mini->line[i] == 39 && s_quote == 1)
			s_quote = 0;
		i++;
	}
	return (i);
}

int	get_cmd_string(t_mini *mini, t_cmd *cmd)
{
	int	i;
	int	s_quote;
	int	d_quote;
	char	*temp;
	int		len;

	i = 0;
	len = get_last_index(mini);
	temp = ft_substr(mini->line, i, len);
	printf("substring before clean quotes : %s$\n\n", temp);
	if (!contain_quotes(temp))
	{
		cmd->command = ft_strdup(temp);
		free(temp);
		return (0);
	}
	clean_command_quotes(cmd, temp);
	printf("substring after clean quotes : %s$\n\n", cmd->command);
	free(temp);
	return (0);
}

