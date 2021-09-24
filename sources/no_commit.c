#include "minishell.h"

void	print_arr_cmd(t_cmd **arr_cmd)
{
	size_t	size;
	size_t	i;
	
	i = 0;
	size = ft_arrlen((void **)arr_cmd);
	while (i < size)
	{
		size_t	j = 0;
		size_t	k = 0;
		printf("cmd->cmd: %s\n", arr_cmd[i]->cmd);
		while(j < ft_arrlen((void **)arr_cmd[i]->tokens))
		{
			printf("cmd->tokens[%zu]: %s\n", j, arr_cmd[i]->tokens[j]);
			j++;
		}
		printf("cmd->has_pipe: %d\n", arr_cmd[i]->has_pipe);
		printf("cmd->has_cmd: %d\n", arr_cmd[i]->has_cmd);
		while (k < ft_arrlen((void **)arr_cmd[i]->redir_out))
		{
			// printf("size: %zu\n", ft_arrlen((void **)arr_cmd[i]->redir_out));
			printf("cmd->redir_out->filename: %s\n", arr_cmd[i]->redir_out[k]->filename);
			printf("cmd->redir_out->has_filename: %d\n", arr_cmd[i]->redir_out[k]->has_filename);
			printf("cmd->redir_out->type: %u\n", arr_cmd[i]->redir_out[k]->type);
			size_t b = 0;
			while (b < ft_arrlen((void **)arr_cmd[i]->redir_out[k]->args))
			{
				printf("cmd->redir_out->args[%zu]: %s\n", b, arr_cmd[i]->redir_out[k]->args[b]);
				b++;
			}
			k++;
		}
		k = 0;
		while (k < ft_arrlen((void **)arr_cmd[i]->redir_in))
		{
			// printf("size: %zu\n", ft_arrlen((void **)arr_cmd[i]->redir_out));
			printf("cmd->redir_in->filename: %s\n", arr_cmd[i]->redir_in[k]->filename);
			printf("cmd->redir_in->has_filename: %d\n", arr_cmd[i]->redir_in[k]->has_filename);
			printf("cmd->redir_in->type: %u\n", arr_cmd[i]->redir_in[k]->type);
			size_t b = 0;
			while (b < ft_arrlen((void **)arr_cmd[i]->redir_in[k]->args))
			{
				printf("cmd->redir_in->args[%zu]: %s\n", b, arr_cmd[i]->redir_in[k]->args[b]);
				b++;
			}
			k++;
		}
		// printf("cmd->", redir_in);
		i++;
		printf("\n");
	}
}
