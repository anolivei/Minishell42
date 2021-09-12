#include "minishell.h"


bool is_any_redir(char c)
{
	if (c == '>' || c == '<')
		return true;
	return false;
}

bool is_input_redir(char c)
{
	if (c == '<')
		return (true);
	return (false);
}

bool is_output_redir(char c)
{
	if (c == '>')
		return (true);
	return (false);
}
