# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chlimous <chlimous@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/20 00:00:00 by chlimous          #+#    #+#              #
#    Updated: 2024/12/28 15:01:24 by chlimous         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_CLIENT = client
NAME_SERVER = server
SRCDIR = src
OBJDIR = obj
SRCS_CLIENT = src/client.c src/client_utils.c
SRCS_SERVER = src/server.c src/server_buffer.c
OBJS_CLIENT = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS_CLIENT))
OBJS_SERVER = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS_SERVER))
INCLUDE = include
INCLUDES = -I $(INCLUDE) -I $(LIBFT_DIR)/include
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
C_GREEN=\e[32m
C_END=\e[0m

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCLUDE)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

all: $(NAME_CLIENT) $(NAME_SERVER)

$(NAME_CLIENT): $(OBJS_CLIENT) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS_CLIENT) -L $(LIBFT_DIR) -l ft -o $(NAME_CLIENT)

$(NAME_SERVER): $(OBJS_SERVER) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS_SERVER) -L $(LIBFT_DIR) -l ft -o $(NAME_SERVER)

bonus: all

$(LIBFT): FORCE
	@echo "$(C_GREEN)Compiling libft...$(C_END)"
	@output="$$(make -C libft)"; \
	if echo "$$output" | grep -q 'is up to date'; then \
		echo "$(C_GREEN)libft is already up to date.$(C_END)"; \
	else \
		echo "$(C_GREEN)libft succesfully compiled.$(C_END)"; \
	fi

FORCE:

clean:
	rm -rf $(OBJDIR)
	@if [ -d "$(LIBFT_DIR)" ]; then \
		make clean -C $(LIBFT_DIR); \
	fi

fclean: clean
	rm -f $(NAME_CLIENT) $(NAME_SERVER)
	@if [ -d "$(LIBFT_DIR)" ]; then \
		make fclean -C $(LIBFT_DIR); \
	fi

re: fclean all

.PHONY: all FORCE clean fclean re
