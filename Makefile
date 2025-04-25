# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kyang <kyang@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/31 16:25:43 by kyang             #+#    #+#              #
#    Updated: 2025/04/25 12:10:23 by kyang            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRCDIR = src
OBJDIR = obj
INCDIR = include


SRC_MAIN = main.c
SRC_UTILS = utils.c utils_color.c
SRC_PARSING = parsing/parse_map.c parsing/parse_texture.c parsing/check_map.c
SRC_RAYCASTING = raycasting/init_pos_dir.c raycasting/calculations.c raycasting/draw.c
SRC_GRAPHIC = graphic/handle_mlx.c graphic/move_player.c graphic/rotate_player.c \
				graphic/mini_map.c graphic/door.c graphic/weapon.c graphic/render_loop.c
SRC_INITIALIZE = initialize.c
SRC = $(SRC_MAIN) $(SRC_UTILS) $(SRC_PARSING) $(SRC_RAYCASTING) $(SRC_GRAPHIC) $(SRC_INITIALIZE)
SRCS = $(addprefix $(SRCDIR)/, $(SRC))

LIBFT = ./libft
MINILIBX = ./minilibx-linux

OBJS = $(patsubst %.c, $(OBJDIR)/%.o, $(SRCS))

CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INCDIR) -g3

all: $(NAME)

$(OBJDIR):
	mkdir -p $(OBJDIR) || true

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

-include $(OBJS:.o=.d)

$(NAME): $(OBJS) $(LIBFT)
	make -C $(LIBFT)
	make -C $(MINILIBX)
	$(CC) $(CFLAGS) $(OBJS) -L$(MINILIBX) -L/usr/lib -I$(MINILIBX) -lmlx -lXext -lX11 -lm -lz ./libft/libft.a -o $(NAME)

clean:
	rm -rf $(OBJDIR)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re
