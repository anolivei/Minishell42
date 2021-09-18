#include "minishell.h"

void	free_lst_token(void *token)
{
	if (token == NULL)
		return ;
	if (((t_token *)token)->value != NULL)
		free(((t_token *)token)->value);
}

t_list	*tac_compile(char *src, t_list *lst)
{
	t_lexer	*lexer;
	t_token	*token ;
	t_list	*lst_tk;
	t_list	*new_lst;

	lexer = init_lexer(src);
	token = lexer_next_token(lexer);
	if (token->type == TOKEN_EOF)
	{
		free(lst);
		lst = NULL;
		return (lst);
	}
	while (token->type != TOKEN_EOF)
	{
		lst_tk = ft_lstnew(token);
		ft_lstadd_back(&lst, lst_tk);
		token = lexer_next_token(lexer);
	}
	if (lst != NULL)
	{
		new_lst = lst->next;
		ft_lstdelone(lst, &free_lst_token);
		return (new_lst);
	}
	return (lst);
}
