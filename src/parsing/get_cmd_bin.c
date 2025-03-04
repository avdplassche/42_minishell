

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
		{
			if (mini->envp[i][j++] != variable[k++])
				break ;
		}
		if (k == len)
			return (i);
		i++;
	}
	return (-1);
}



/** Used to change every dollar sign to elements of env variable
 * @param mini t_mini struct where envp is stored
 * @param str the string to change dollar sign if needed
 * @return errors
*/
int	translate_dollar_sign(t_mini *mini, char *str)
{
	int		i;
	int		j;
	t_quote	quote;
	char	*variable_name;

	j = 0;
	quote.sgl = 0;
	quote.dbl = 0;
	i = -1;
	while (str[++i] && str[i] != '$' && quote.sgl == 0)
		quote_enclosure_handle(str[i], &quote);
	printf("i = %d\n", i);
	while (str[++i] && (str[i] != ' ') && str[i] != 34)
		j++;
	// variable_name = malloc(sizeof(char) * (j + 2));
	variable_name = ft_substr(str, i - j, j + 1);
	variable_name[j] = '=';
	variable_name[j + 1] = '\0';
	printf("name : %s$\n", variable_name);
	printf("Index : %d\n", get_envp_index(mini, variable_name));
	print_char_table(mini->envp, "envp");
	printf("\n\n");
	return (0);
}

/** Do the string needs a dollar sign sub ?
 * @param str the string to scan
 * @return 1 yes
 * @return 0 no
*/
int	need_dollar_sub(char *str)
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

/** This function calculate the necessary lenght of the new string after deleting the quotes
 * @param str the string to delete the quote from
 * @return a total amount of char, to be used for malloc
*/
int	strlen_quote_cleaned_command(char *str)
{
	int	i;
	int	j;
	int	first_quote;

	i = -1;
	j = 0;
	while (str[++i])
	{
		while (str[i++] && !(is_quote(str[i])))
			j++;
		if (is_quote(str[i]))
			first_quote = str[i];
		while (str[++i] && str[i] != first_quote)
			j++;
	}
	return (j);
}

/** Fill command structure (for 1 command of the command line)
 * @param cmd the cmd structure containing cmd->commandto fill
 * @param str the string used to epure from (will be freed after the function)
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
			cmd->command[j++] = str[i++];
		if (is_quote(str[i]))
			first_quote = str[i];
		while (str[++i] && str[i] != first_quote)
			cmd->command[j++] = str[i];
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
	int		i;
	t_quote	quote;
	char	charset[4] = " <>|";

	i = 0;
	quote.dbl = 0;
	quote.sgl = 0;
	while (mini->line[i])
	{
		if (contain_char(charset, mini->line[i]))
			if (!quote.sgl && !quote.dbl && i)
				return (i);
		quote_enclosure_handle(mini->line[i], &quote);
		i++;
	}
	return (i);
}

int	get_cmd_bin(t_mini *mini, t_cmd *cmd)
{
	int		i;
	char	*temp;
	int		len;

	i = 0;
	len = get_last_index(mini);
	mini->cursor = len;
	temp = ft_substr(mini->line, i, len);
	printf("Substring before cleaning quotes : %s$\n\n", temp);
	if (need_dollar_sub(temp))
	{
		printf("Need $ translation\n\n");
		translate_dollar_sign(mini, temp);
	}
	if (!contain_quotes(temp))
	{
		cmd->command = ft_strdup(temp);
		return (free(temp), 0);
	}
	clean_command_quotes(cmd, temp);
	return (free(temp), 0);
}

