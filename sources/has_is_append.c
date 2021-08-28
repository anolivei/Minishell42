#include "minishell.h"

bool is_append(char *str)
{
	if (ft_strlen(str) == 2 && ft_strncmp(str, ">>", 1))
		return true;
	return false;
}

bool has_append(char **tokens)
{
	int i;

	i = 0;
	while (tokens[i] != NULL)
	{
		if (is_append(tokens[i]))
			return true;
	}
	return false;
}
