#include "minishell.h"

t_token	*init_token(char *value, int type)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	token->value = value;
	token->type = type;
	return (token);
}

const char	*token_type_to_str(int type)
{
    switch (type)
    {
        case TOKEN_WORD: return "TOKEN_WORD"; 
        case TOKEN_DOUBLE_QUOTES: return "TOKEN_DOUBLE_QUOTES"; 
        case TOKEN_SINGLE_QUOTE: return "TOKEN_SINGLE_QUOTE"; 
        case TOKEN_VARIABLE: return "TOKEN_VARIABLE"; 
        case TOKEN_PIPE: return "TOKEN_PIPE"; 
        case TOKEN_RED_OUT: return "TOKEN_RED_OUT"; 
        case TOKEN_RED_IN: return "TOKEN_RED_IN"; 
        case TOKEN_APPEND_OUT: return "TOKEN_APPEND_OUT"; 
        case TOKEN_APPEND_IN: return "TOKEN_APPEND_IN"; 
        case TOKEN_EOF: return "TOKEN_EOF"; 
    }

    return "token_stringable";
}

char	*token_to_str(t_token *token)
{
	const char	*type_str = token_type_to_str(token->type);
	const char	*template = "<type=`%s`, int_type=`%d`, value=`%s`>\n";

	char *str = ft_calloc(ft_strlen(type_str) + ft_strlen(template) + ft_strlen(token->value) + 8, sizeof(char));
	sprintf(str, template, type_str, token->type, token->value);
	return str;
}
