#include "minishell.h"

bool is_output_append(char *str, int index)
{
	if (str == NULL)
		return (false);
	if (ft_strlen(str) > 2 && str[index] == '>' && str[index + 1] == '>')
		return true;
	return false;
}

bool is_input_append(char *str, int index)
{
	if (str == NULL)
		return (false);
	if (ft_strlen(str) > 2 && str[index] == '<' && str[index + 1] == '<')
		return true;
	return false;
}
