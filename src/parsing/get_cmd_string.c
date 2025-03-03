

#include "../../includes/minishell.h"

char	*translate_dollar_sign(char *str)
{
	



	return (NULL);
}
/** Do the string needs a dollar sign translation ?
 * @param str the string to scan
 * @return 1 yes
 * @return 0 no
*/
int	need_dollar_translation(char *str)
{
	int		i;
	int		s_quote;
	int		d_quote;

	s_quote = 0;
	d_quote = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '$' && s_quote == 0)
			return (1);
		else if (str[i] == 34 && d_quote == 0)
			d_quote = 1;
		else if (str[i] == 34 && d_quote == 1)
			d_quote = 0;
		else if (str[i] == 39 && s_quote == 0)
			s_quote = 1;
		else if (str[i] == 39 && s_quote == 1)
			s_quote = 0;
	}
	return (0);
}

int	strlen_quote_cleaned_command(char *str)
{
	int	i;
	int	j;
	int	first_quote;

	i = -1;
	j = 0;
	while (str[++i])
	{
		while (str[i] && !(is_quote(str[i])))
		{
			j++;
			i++;
		}
		if (is_quote(str[i]))
			first_quote = str[i];
		while (str[++i] && str[i] != first_quote)
			j++;
	}
	return (j);
}

/** Fill command structure (for 1 command of the command line)
 * @param mini t_mini structure, containing current line to work with
 * @param cmd_s an empty structure that the function will fill
 * @return not set yet, errors
*/
int	clean_command_quotes(t_cmd *cmd, char *str)
{
	int		first_quote;
	int		last_quote;
	int		i;
	int		j;

	j = strlen_quote_cleaned_command(str);
	cmd->command = malloc(sizeof(char) * (j + 1));
		//malloc protection
	i = -1;
	j = 0;
	while (str[++i])
	{
		while (str[i] && !(is_quote(str[i])))
		{
			cmd->command[j] = str[i];
			j++;
			i++;
		}
		if (is_quote(str[i]))
			first_quote = str[i];
		while (str[++i] && str[i] != first_quote)
		{
			cmd->command[j] = str[i];
			j++;
		}
	}
	cmd->command [j] = '\0';
	return (0);
}

/** Get the command's last index, use it to substring
 * @param mini t_mini structure, containing current line to work with
 * @return i : last index of the command
*/
int	get_last_index(t_mini *mini)
{
	int	i;
	int	s_quote;
	int	d_quote;
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
	char	*temp;
	int		len;

	i = 0;
	len = get_last_index(mini);
	mini->cursor = len;
	temp = ft_substr(mini->line, i, len);
	printf("Substring before cleaning quotes : %s$\n\n", temp);
	if (contain_char(temp, '$') && need_dollar_translation(temp))
	{
		translate_dollar_sign(temp);
	}
	if (!contain_quotes(temp))
	{
		cmd->command = ft_strdup(temp);
		free(temp);
		return (0);
	}
	clean_command_quotes(cmd, temp);
	printf("Substring after cleaning quotes : %s$\n\n", cmd->command);
	free(temp);
	return (0);
}

