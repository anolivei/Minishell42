# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/25 15:06:33 by anolivei          #+#    #+#              #
#    Updated: 2021/09/23 09:25:30 by wbertoni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRC_DIR = sources
OBJ_DIR = .objs
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC =	$(SRC_DIR)/lexer/token.c \
		$(SRC_DIR)/lexer/ft_min_and_max.c \
		$(SRC_DIR)/lexer/lexer_utils_one.c \
		$(SRC_DIR)/lexer/lexer_utils_two.c \
		$(SRC_DIR)/lexer/lexer_utils_three.c \
		$(SRC_DIR)/lexer/get_token_list.c \
		$(SRC_DIR)/lexer/lexer_next_token.c \
		$(SRC_DIR)/main.c \
		$(SRC_DIR)/builtins.c \
		$(SRC_DIR)/ft_echo.c \
		$(SRC_DIR)/ft_cd.c \
		$(SRC_DIR)/ft_pwd.c \
		$(SRC_DIR)/ft_export.c \
		$(SRC_DIR)/ft_unset.c \
		$(SRC_DIR)/ft_env.c \
		$(SRC_DIR)/find_env.c \
		$(SRC_DIR)/init_path.c \
		$(SRC_DIR)/ft_exit.c \
		$(SRC_DIR)/split_cmd.c \
		$(SRC_DIR)/run_pipe.c \
		$(SRC_DIR)/minishell_utils.c \
		$(SRC_DIR)/signal.c \
		$(SRC_DIR)/arr_str_utils.c \
		$(SRC_DIR)/cmd_utils.c
		# $(SRC_DIR)/ft_execve.c

OBJ = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))

CC = clang
HEAD = -I./includes -I./$(LIBFT_DIR) -I/usr/local/Cellar/readline/8.1/include
CFLAGS = -Wall -Werror -Wextra -g -fsanitize=address
LFLAGS = -L ./$(LIBFT_DIR) -L/usr/local/Cellar/readline/8.1/lib -lft -lreadline
RM = /bin/rm -rf

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
		@$(CC) $(OBJ) $(HEAD) $(CFLAGS) $(LFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
		@mkdir -p $(OBJ_DIR)
		@mkdir -p $(OBJ_DIR)/lexer
		@$(CC) $(CFLAGS) $(HEAD) -c $< -o $@
		@echo "\033[1;32m[OK]\033[0m    \033[1;33mCompiling\033[0m $(<F)"

$(LIBFT):
		@make -C $(LIBFT_DIR)

debug_mac: $(OBJ) $(LIBFT)
		@gcc $(LFLAGS) $(HEAD) $(SRC) $(CFLAGS) -o "minishell_debug"

debug_linux: $(OBJ) $(LIBFT)
		@$(CC) $(LFLAGS) $(HEAD) $(SRC) $(CFLAGS) -o "minishell_debug"

clean:
		@make clean -C $(LIBFT_DIR)
		@$(RM) $(OBJ_DIR)

fclean: clean
		@make fclean -C $(LIBFT_DIR)
		@$(RM) $(NAME)
		@$(RM) minishell_debug
		@$(RM) minishell_debug.dSYM

re: fclean all

.PONY: all clean fclean re debug_mac debug_linux
