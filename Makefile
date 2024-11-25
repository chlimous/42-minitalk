# **************************************************************************** #
#									       #
#							  :::	   ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#						      +:+ +:+	      +:+      #
#    By: chlimous <chlimous@student.42.fr>	    +#+  +:+	   +#+	       #
#						  +#+#+#+#+#+	+#+	       #
#    Created: 2023/10/28 21:44:04 by chlimous	       #+#    #+#	       #
#    Updated: 2024/04/29 03:27:16 by chlimous         ###   ########.fr        #
#									       #
# **************************************************************************** #

NAME_CLIENT = client
NAME_SERVER = server

SRCS_CLIENT = src/client.c src/client_utils.c
SRCS_SERVER = src/server.c src/buffer.c

OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)
OBJS_SERVER = $(SRCS_SERVER:.c=.o)

INCLUDE = include

INCLUDES = -I $(INCLUDE) -I $(LIBFT_DIR)/include

LIBFT_DIR = libft

LIBFT = $(LIBFT_DIR)/libft.a

CC = cc

CFLAGS = -Wall -Wextra -Werror

%.o: %.c $(INCLUDE)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $(<:.c=.o)

all: $(NAME_CLIENT) $(NAME_SERVER)

$(NAME_CLIENT) : $(OBJS_CLIENT) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS_CLIENT) -L $(LIBFT_DIR) -l ft -o $(NAME_CLIENT)

$(NAME_SERVER) : $(OBJS_SERVER) $(LIBFT)
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

clean :
	rm -f $(OBJS_CLIENT) $(OBJS_SERVER)
	@if [ -d "$(LIBFT_DIR)" ]; then \
		make clean -C $(LIBFT_DIR); \
	fi

fclean : clean
	rm -f $(NAME_CLIENT) $(NAME_SERVER)
	@if [ -d "$(LIBFT_DIR)" ]; then \
		make fclean -C $(LIBFT_DIR); \
	fi

re : fclean all

.PHONY : all FORCE clean fclean re
