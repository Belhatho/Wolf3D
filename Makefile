# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbouchak <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/21 16:55:03 by hbouchak          #+#    #+#              #
#    Updated: 2020/01/22 14:36:17 by ibel-kha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

SRCS = srcs/main.c\
      srcs/parser.c\
      srcs/draw.c\
      srcs/raycasting.c\
      srcs/texture.c\
      srcs/events.c

OBJ = srcs/main.o\
      srcs/parser.o\
      srcs/draw.o\
      srcs/raycasting.o\
      srcs/texture.o\
      srcs/events.o

LIBFT = -L libft -lft

CFLAGS = -Wall -Wextra -Werror

CC = gcc $(CFLAGS)

MLX = -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft libft.a
	@$(CC) -o wolf3d $(OBJ) $(LIBFT) $(MLX)

%.o: %.c
	$(CC) -c $< -o $@ 

clean:
	@make clean -C libft/
	@rm -f $(OBJ)

fclean: clean
	@make fclean -C libft/
	@rm -f $(NAME)

re: fclean all
