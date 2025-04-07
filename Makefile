# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbellest <tbellest@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/31 16:25:43 by kyang             #+#    #+#              #
#    Updated: 2025/04/07 18:27:37 by tbellest         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

SRCDIR = src
OBJDIR = obj
INCDIR = include

SRC = main.c utils.c parsing/parse_map.c raycasting/raycasting.c graphic/handle_mlx.c \
		graphic/move_player.c graphic/rotate_player.c initialize.c parsing/parse_texture.c
SRCS = $(addprefix $(SRCDIR)/, $(SRC))

LIBFT = ./libft
MINILIBX = ./minilibx-linux

OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INCDIR) -g3

all: $(NAME)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

-include $(OBJS:.o=.d)

$(NAME): $(OBJS) $(LIBFT)
	make -C $(LIBFT)
	make -C $(MINILIBX)
	$(CC) $(CFLAGS) $(OBJS) -L$(MINILIBX) -L/usr/lib -I$(MINILIBX) -lXext -lX11 -lm -lz $(MINILIBX)/libmlx.a ./libft/libft.a -o $(NAME)

clean:
	rm -rf $(OBJDIR)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re
