#include "minishell.h"

void	free_token(t_token *token)
{
	if (token->value != NULL)
	{
		free(token->value);
		token->value = NULL;
		free(token);
		token = NULL;
	}
}

void	free_arr_token(t_token **arr)
{
	int	i;

	i = 0;
	if (arr == NULL)
		return ;
	while (arr[i] != NULL)
	{
		free_token(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
}

t_token	**init_arr_token(size_t size)
{
	t_token	**arr_token;
	size_t	i;

	i = 0;
	arr_token = (t_token **)ft_calloc(size + 2, sizeof(t_token *));
	return (arr_token);
}

t_token	**push_token(t_token **arr, t_token *token)
{
	size_t	i;
	size_t	size;
	t_token	**new_token;

	size = ft_arrlen((void **)arr);
	new_token = init_arr_token(size);
	i = 0;
	while (i < size)
	{
		new_token[i] = arr[i];
		i++;
	}
	new_token[i] = token;
	free(arr);
	arr = NULL;
	return (new_token);
}

t_token	**get_token_list(t_mini *mini)
{
	t_token	**arr;
	t_lexer	*lexer;
	t_token	*token ;

	lexer = init_lexer(mini->line_read);
	token = lexer_next_token(lexer);
	arr = init_arr_token(0);
	if (token->type == TOKEN_EOF)
		return (arr);
	while (token->type != TOKEN_EOF)
	{
		arr = push_token(arr, token);
		token = lexer_next_token(lexer);
	}
	if (token->type == TOKEN_EOF)
	{
		arr = push_token(arr, token);
		token = lexer_next_token(lexer);
	}
	free(lexer);
	free_token(token);
	return (arr);
}
