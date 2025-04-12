#include "minishell.h"

int	need_tilde_expand(t_mini *mini)
{
	int		i;
	t_quote	q;

	init_quotes(&q);
	i = -1;
	while (mini->line[++i])
	{
		quote_enclosure_handle(mini->line[i], &q);
		if ((!q.dbl || !q.sgl) && mini->line[i] == '~')
		{
			if (i == 0 && (mini->line[1] == ' ' || !mini->line[i + 1]))
				return (0);
			if (i > 0 && (mini->line[i - 1] == ' '
					&& (!mini->line[i + 1] || mini->line[i + 1])))
				return (i);
		}
	}
	return (-1);
}

void	sub_tilde(t_mini *mini, int i)
{
	char	*env;
	char	*prefix;
	char	*suffix;

	if (i == 0)
	{
		prefix = ft_get_env(mini, "HOME");
		if (!prefix)
			exit_minishell(mini, mini->cmd);
		suffix = ft_substr(mini->line, 1, ft_strlen(mini->line) - 1);
		free(mini->line);
		if (!suffix)
			return (free(suffix), exit_minishell(mini, mini->cmd));
		mini->line = ft_strjoin(prefix, suffix);
		if (!mini->line)
			return (free(suffix), free(prefix), exit_minishell(mini, mini->cmd));
	}
	else
	{
		env = ft_get_env(mini, "HOME");
		if (!env)
			exit_minishell(mini, mini->cmd);
		prefix = ft_substr(mini->line, 0, i);
		if (!prefix)
			return (free(env), exit_minishell(mini, mini->cmd));
		suffix = ft_substr(mini->line, i + 1, ft_strlen(mini->line) - 1 - i);
		if (!suffix)
			return (free(env), free(prefix), exit_minishell(mini, mini->cmd));
		free(mini->line);
		mini->line = join_three_strings(prefix, env, suffix);
		free(env);
	}
	free(prefix);
	free(suffix);
}

void	expand_tildes(t_mini *mini)
{
	int		i;

	if (!contain_char(mini->line, '~'))
		return ;
	i = need_tilde_expand(mini);
	while (i != -1)
	{
		sub_tilde (mini, i);
		i = need_tilde_expand(mini);
	}
}