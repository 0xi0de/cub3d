# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbetmall <lbetmall@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/05 07:50:44 by lbetmall          #+#    #+#              #
#    Updated: 2022/02/28 21:54:59 by lbetmall         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = frac

NAME_BON = frac_bonus

SRC = fractol.c color.c deal_key.c generate_float.c mouse_hook.c ft_atof.c \
check_str.c isdigit.c parsing.c complex.c ft_strcmp.c

SRC_BON = fractol_bonus.c color.c deal_key_bonus.c generate_float.c \
mouse_hook_bonus.c ft_atof.c check_str.c isdigit.c parsing.c complex.c \
ft_strcmp.c

OBJ = $(SRC:.c=.o)

OBJ_BON = $(SRC_BON:.c=.o)

FLAG = -Wall -Wextra -Werror

LIBX = -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJ) $(LIB)
		gcc $(FLAG) -L ./lib -lmlx $(OBJ) $(LIBX) -o $(NAME)

$(NAME_BON): $(OBJ_BON) $(LIB)
		gcc -Ofast $(FLAG) -L ./lib -lmlx $(OBJ_BON) $(LIBX) -o $(NAME_BON)


%.o: %.c fractol.h
		make -C ./lib/
		gcc $(FLAG) -o $@ -c $<

bonus: $(NAME_BON)

clean:
		make -C lib/ clean
			rm -rf $(OBJ) $(OBJ_BON)

fclean: clean
			rm -rf $(NAME) $(NAME_BON)

re: fclean all

re_bonus: fclean bonus

.PHONY: clean fclean re re_bonus bonus all
