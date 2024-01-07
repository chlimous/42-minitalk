# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chlimous <chlimous@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/28 21:44:04 by chlimous          #+#    #+#              #
#    Updated: 2024/01/06 21:58:38 by chlimous         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_CLIENT = client
NAME_SERVER = server

SRCS_CLIENT = src/client.c
SRCS_SERVER = src/server.c src/server_utils.c

OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)
OBJS_SERVER = $(SRCS_SERVER:.c=.o)

INCLUDE = include

LIB = $(addprefix $(LIB_PATH), libft.a)

LIB_PATH = libft/

LIB_INCLUDE = libft/include

CC = cc

CFLAGS = -Wall -Wextra -Werror

src/%.o: src/%.c $(INCLUDE)
	$(CC) $(CFLAGS) -I $(INCLUDE) -I $(LIB_INCLUDE) -c $< -o $(<:.c=.o)

all: $(NAME_CLIENT) $(NAME_SERVER)

$(NAME_CLIENT) : $(OBJS_CLIENT) $(LIB)
	$(CC) $(CFLAGS) $(OBJS_CLIENT) -L $(LIB_PATH) -l ft -o $(NAME_CLIENT)

$(NAME_SERVER) : $(OBJS_SERVER) $(LIB)
	$(CC) $(CFLAGS) $(OBJS_SERVER) -L $(LIB_PATH) -l ft -o $(NAME_SERVER)

$(LIB):
	@make -C $(LIB_PATH)

bonus: all

clean :
	make clean -C libft
	rm -f $(OBJS_CLIENT) $(OBJS_SERVER)

fclean : clean
	make fclean -C libft
	rm -f $(NAME_CLIENT) $(NAME_SERVER)

re : fclean all

.PHONY : libft all clean fclean re
