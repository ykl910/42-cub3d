# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kyang <kyang@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/31 16:25:43 by kyang             #+#    #+#              #
#    Updated: 2025/03/31 14:12:41 by kyang            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

CC = cc

SRC_PATH = src/
SRC 	= main.c

SRCS	= $(addprefix $(SRC_PATH), $(SRC))

LIBFT = ./libft

CFLAGS = -Wall -Wextra -Werror 

OBJS = $(SRCS:.c=.o)

all: $(NAME)

bonus: $(NAME_BONUS)

$(NAME): $(OBJS) $(LIBFT)
	make all bonus -C libft
	make -C minilibx-linux
	$(CC) $(CFLAGS) $(OBJS) -Lminilibx-linux -lmlx_Linux -L/usr/lib -Iminilibx-linux -lXext -lX11 -lm -lz ./libft/libft.a -o $(NAME)
	
%.o: %.c
	$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -I $(LIBFT) -O3 -c $< -o $@

clean:
	rm -f $(OBJS)
	rm -f $(OBJS_BONUS)
	make -C $(LIBFT) clean

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME_BONUS)
	make -C $(LIBFT) fclean
	
re: fclean all

.PHONY: all clean fclean re bonus