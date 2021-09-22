#ifndef LEXER_H
# define LEXER_H

# include <string.h>  
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include "token.h"

typedef struct s_lexer
{
	char			*src;
	size_t			src_size;
	char			c;
	unsigned int	i;
	bool			double_quoted;
	bool			single_quoted;
}	t_lexer;

t_lexer	*init_lexer(char *src);
t_token	*lexer_next_token(t_lexer *lexer);
t_token	*lexer_parse_word(t_lexer *lexer);
t_token	*lexer_advance_with(t_lexer *lexer, t_token *token);
t_token	*lexer_advance_current(t_lexer *lexer, int type);
t_token	*lexer_advance_twice_with(t_lexer *lexer, t_token *token);
t_token	*lexer_parse_quoted(t_lexer *lexer, int quote);
t_token	*lexer_parse_variable(t_lexer *lexer);
void	lexer_advance(t_lexer *lexer);
void	lexer_skip_whitespace(t_lexer *lexer);
char	lexer_peek(t_lexer *lexer, int offset);
int		ft_max(int a, int b);
int		ft_min(int a, int b);


#endif
