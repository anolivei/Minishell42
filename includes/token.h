#ifndef TOKEN_H
# define TOKEN_H

typedef enum e_token
{
	TOKEN_WORD,
	TOKEN_DOUBLE_QUOTES,
	TOKEN_SINGLE_QUOTE,
	TOKEN_VARIABLE,
	TOKEN_PIPE,
	TOKEN_RED_OUT,
	TOKEN_RED_IN,
	TOKEN_APPEND_OUT,
	TOKEN_APPEND_IN,
	TOKEN_EOF,
}	t_etoken;

typedef struct s_token
{
	char		*value;
	t_etoken	type;
}	t_token;

t_token		*init_token(char *value, int type);
char		*token_to_str(t_token *token);
const char	*token_type_to_str(int type);

#endif
