#include "minishell.h"

void	lexer_skip_whitespace(t_lexer *lexer)
{
	while (ft_isspace(lexer->c))
		lexer_advance(lexer);
}

bool	is_special(char c)
{
	if (c == '"' || c == '\'' || c == '$' || c == '>' || c == '<'
		|| c== '|')
		return (true);
	return (false);
}

t_token	*lexer_parse_word(t_lexer *lexer)
{
	char	*value;

	value = ft_calloc(1, sizeof(char));
	while (!ft_isspace(lexer->c) && lexer->c != '\0' && !is_special(lexer->c))
	{
		value = ft_realloc(value, (ft_strlen(value) + 2)
				* sizeof(char));
		strcat(value, (char []){lexer->c, 0});
		lexer_advance(lexer);
	}
	return (init_token(value, TOKEN_WORD));
}

t_token	*lexer_parse_quoted(t_lexer *lexer, int quote)
{
	char		*value;
	t_etoken	type;
	bool		is_second_quote;
	int			counter;

	counter = 0;
	is_second_quote = false;
	value = ft_calloc(1, sizeof(char));
	while (!is_second_quote && lexer->c != '\0')
	{
		if (lexer->c == quote && counter > 0)
			is_second_quote = true;
		value = ft_realloc(value, (ft_strlen(value) + 2)
				* sizeof(char));
		strcat(value, (char []){lexer->c, 0});
		lexer_advance(lexer);
		counter++;
	}
	if (quote == '"')
		type = TOKEN_DOUBLE_QUOTES;
	else
		type = TOKEN_SINGLE_QUOTE;
	return (init_token(value, type));
}

t_token	*lexer_parse_variable(t_lexer *lexer)
{
	char	*value;

	value = ft_calloc(1, sizeof(char));
	while (ft_isspace(lexer->c) || lexer->c != '\0')
	{
		value = ft_realloc(value, (ft_strlen(value) + 2) * sizeof(char));
		strcat(value, (char []){lexer->c, 0});
		lexer_advance(lexer);
	}
	return (init_token(value, TOKEN_VARIABLE));
}

t_token	*lexer_advance_current(t_lexer *lexer, int type)
{
	char	*value;
	t_token	*token;

	value = ft_calloc(2, sizeof(char));
	value[0] = lexer->c;
	value[1] = '\0';
	token = init_token(value, type);
	lexer_advance(lexer);
	return (token);
}
