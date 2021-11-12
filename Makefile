# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: belhatho <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/12 01:25:46 by belhatho          #+#    #+#              #
#    Updated: 2021/11/12 01:25:47 by belhatho         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

SRCS = srcs/main.c\
      srcs/parser.c\
      srcs/draw.c\
      srcs/raycasting.c\
      srcs/texture.c\
      srcs/events.c

OBJ = $(SRCS:.c=.o)

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
