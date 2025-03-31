
#include "minishell.h"

char	*join_three_strings(char *s1, char *s2, char *s3)
{
	char	*temp1;
	char	*temp2;

	temp1 = NULL;
	temp2 = NULL;
	if (!s1 && !s2 && !s3)
		return (NULL);
	if (!s1 && !s2)
		return (ft_strdup(s3));
	else if (!s1 && !s3)
		return (ft_strdup(s2));
	else if (!s2 && !s3)
		return (ft_strdup(s1));
	else if (!s1)
		return (ft_strjoin(s2, s3));
	else if (!s2)
		return (ft_strjoin(s1, s3));
	else if (!s3)
		return (ft_strjoin(s1, s2));
	else
	{
		temp1 = ft_strjoin(s1, s2);
		temp2 = ft_strjoin(temp1, s3);
		free(temp1);
		return (temp2);
	}
}