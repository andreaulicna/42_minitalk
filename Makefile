# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/31 18:27:47 by aulicna           #+#    #+#              #
#    Updated: 2023/11/06 23:30:41 by aulicna          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER = server
CLIENT = client
SERVER_B = server_bonus
CLIENT_B = client_bonus

S_SRC = server.c
C_SRC = client.c
S_SRC_B = server_bonus.c
C_SRC_B = client_bonus.c
HEADER = minitalk.h

S_OBJ = $(S_SRC:.c=.o)
C_OBJ = $(C_SRC:.c=.o)
S_OBJ_B = $(S_SRC_B:.c=.o)
C_OBJ_B = $(C_SRC_B:.c=.o)

LIBFTPRINTF = libftprintf
LIBFT = libftprintf/libft

CFLAGS = -Wall -Werror -Wextra

GCC = gcc

all: libs $(SERVER) $(CLIENT)

bonus: libs $(SERVER_B) $(CLIENT_B) 

.c.o:
	$(GCC) $(CFLAGS) -c $< -o $@

libs:
	@make -C $(LIBFTPRINTF)
	@echo "libprintf library ready ✅"

$(SERVER): $(S_OBJ) $(HEADER)
	$(GCC) $(CFLAGS) -L $(LIBFTPRINTF) -o $@ $^ -lftprintf

$(SERVER_B): $(S_OBJ_B) $(HEADER)
	$(GCC) $(CFLAGS) -L $(LIBFTPRINTF) -o $@ $^ -lftprintf

$(CLIENT): $(C_OBJ) $(HEADER)
	$(GCC) $(CFLAGS) -L $(LIBFTPRINTF) -o $@ $^ -lftprintf

$(CLIENT_B): $(C_OBJ_B) $(HEADER)
	$(GCC) $(CFLAGS) -L $(LIBFTPRINTF) -o $@ $^ -lftprintf

clean:
	@rm -f $(S_OBJ) $(C_OBJ)
	@rm -f $(S_OBJ_B) $(C_OBJ_B)
	@make clean -C $(LIBFTPRINTF)

fclean:
	@rm -f $(S_OBJ) $(C_OBJ)
	@rm -f $(SERVER) $(CLIENT)
	@rm -f $(S_OBJ_B) $(C_OBJ_B)
	@rm -f $(SERVER_B) $(CLIENT_B)
	@make fclean -C $(LIBFTPRINTF)

re: fclean all

re_bonus: fclean bonus

.PHONY: all bonus libs clean fclean re re_bonus