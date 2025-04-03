# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/30 14:49:39 by crmunoz-          #+#    #+#              #
#    Updated: 2025/02/24 15:56:53 by crmunoz-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= cub3d
CFLAGS	:= -Wextra -Wall -Werror #-g -fsanitize=address
MLX_DIR	= ./MLX42
MLX	:= $(MLX_DIR)/libmlx42.a
HEADERS	:= -I$(MLX)
MLX_FLAGS	:= -g -ldl -pthread -lm
SRCS	:= cub3d.c utils/raycasting.c utils/rayutils.c utils/checker.c utils/game.c utils/read_map.c utils/check_error.c utils/save_textures.c utils/get_next_line.c utils/get_next_line_utils.c utils/utils1.c utils/utils2.c utils/utils3.c utils/ft_split.c utils/direction.c utils/camera.c utils/movement.c
OBJS	:= ${SRCS:.c=.o}
CC	:= clang
all: $(NAME)
libmlx:
	@make -C $(MLX_DIR)
%.o: %.c
	@$(CC) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

$(NAME): $(OBJS) libmlx
	@$(CC) $(OBJS) $(MLX) $(HEADERS) -ldl -lglfw -pthread -lm -o $(NAME)

clean:
	@rm -rf $(OBJS)
	@make -C $(MLX_DIR) fclean
fclean: clean
	@rm -rf $(NAME)
re: clean all
.PHONY: all, clean, fclean, re, libmlx