#include "minishell.h"

bool is_input_redir(char *str)
{
	if (ft_strlen(str) == 1 && ft_strncmp(str, "<", 1))
		return true;
	return false;
}

bool has_input_redir(char **tokens)
{
	int i;

	i = 0;
	while (tokens[i] != NULL)
	{
		if (is_input_redir(tokens[i]))
			return true;
	}
	return false;
}

bool is_output_redir(char *str)
{
	if (ft_strlen(str) == 1 && ft_strncmp(str, ">", 1))
		return true;
	return false;
}

bool has_output_redir(char **tokens)
{
	int i;

	i = 0;
	while (tokens[i] != NULL)
	{
		if (is_output_redir(tokens[i]))
			return true;
	}
	return false;
}
