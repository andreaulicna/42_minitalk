# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/31 18:27:47 by aulicna           #+#    #+#              #
#    Updated: 2023/11/01 12:55:44 by aulicna          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER = server
CLIENT = client

S_SRC = server.c
C_SRC = client.c

S_OBJ = $(S_SRC:.c=.o)
C_OBJ = $(C_SRC:.c=.o)

LIBFTPRINTF = libftprintf
LIBFT = libftprintf/libft

CFLAGS = -Wall -Werror -Wextra

GCC = gcc

all: libs $(SERVER) $(CLIENT)

libs:
	@make -C $(LIBFTPRINTF)
	@echo "libprintf library ready ✅"

$(SERVER): $(S_OBJ)
	$(GCC) $(CFLAGS) -L $(LIBFTPRINTF) -o $@ $^ -lftprintf

$(CLIENT): $(C_OBJ)
	$(GCC) $(CFLAGS) -L $(LIBFTPRINTF) -o $@ $^ -lftprintf

clean:
	@rm -f $(S_OBJ) $(C_OBJ)
	@make clean -C $(LIBFTPRINTF)

fclean:
	@rm -f $(S_OBJ) $(C_OBJ)
	@rm -f $(SERVER) $(CLIENT)
	@make fclean -C $(LIBFTPRINTF)
	
re:	fclean
	@make all
	
.PHONY: all clean fclean re

