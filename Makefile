# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dysotoma <dysotoma@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/24 16:20:33 by dysotoma          #+#    #+#              #
#    Updated: 2019/05/05 22:26:11 by dysotoma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_select

FLAGS = -g -Wall -Wextra -Werror

SRC = main.c signal_handle.c input.c list_and_check.c\
print_and_resize_utils.c print.c

OBJ = $(patsubst %.c, %.o, $(SRC))

LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(SRC) $(LIBFT)
	@gcc $(FLAGS) $(SRC) $(LIBFT) -o $(NAME) -ltermcap

$(LIBFT): libft/*.c
	make -C libft/

clean:
	/bin/rm -f $(OBJ)
	make clean -C libft/

fclean: clean
	/bin/rm -f $(NAME)
	make fclean -C libft/

re: fclean all