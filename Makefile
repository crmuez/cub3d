# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/30 14:49:39 by crmunoz-          #+#    #+#              #
#    Updated: 2025/02/05 20:36:59 by crmunoz-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= cub3d
CFLAGS	:= -Wextra -Wall -Werror
MLX_DIR	= ./MLX42
MLX	:= $(MLX_DIR)/libmlx42.a
HEADERS	:= -I$(MLX)
MLX_FLAGS	:= -ldl -pthread -lm
SRCS	:= cub3d.c utils/get_next_line.c utils/get_next_line_utils.c utils/frees.c read_map.c
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