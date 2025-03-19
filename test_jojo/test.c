
#include "../includes/minishell.h"

char *replace_in_double_array(t_mini *mini, t_cmd *cmd, char *variable)
{
	char *full_path;

	full_path = ft_get_env(mini, variable);
	printf("%s\n", full_path);
	return (full_path);
}

int main(int argc, char **argv, char **env)
{
	t_mini	mini;
	t_cmd	cmd;
	char	*s;
	//char	**test;
	(void)argc;
	(void)argv;

	mini.envp = env;
	s = replace_in_double_array(&mini, &cmd, "USER");
	if (!s)
	{
		return (1);
	}
	printf("%s\n", s);
	//test = ft_split(s, ':');
	//string_array_print(test);
	return (0);
}
