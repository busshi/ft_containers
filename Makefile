# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aldubar <aldubar@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/04 18:20:46 by aldubar           #+#    #+#              #
#    Updated: 2021/10/29 11:30:13 by aldubar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= ft_containers

SRCS		= $(addprefix srcs/, main.cpp vector.cpp stack.cpp map.cpp)

HEADER		= $(addprefix includes/, vector.hpp iterator.hpp reverse_iterator.hpp type_traits.hpp comparison.hpp stack.hpp map.hpp)

OBJ_DIR		= obj/ft

OBJS		= $(addprefix $(OBJ_DIR)/, $(SRCS:.cpp=.o))

FLAGS		= -Wall -Wextra -Werror -std=c++98 -Iincludes -DSTL=0

CC			= @clang++

RM			= @rm -rf

OK			= "\r[ \033[0;32mok\033[0m ]"

$(OBJ_DIR)/%.o:%.cpp
		@mkdir -p $(dir $@)
		$(CC) $(FLAGS) -c $< -o $@

all:		$(NAME)

$(NAME):	$(OBJS) $(OBJ_DIR)
		@echo "[....] Compiling $(NAME)\c"
		$(CC) $(FLAGS) $(OBJS) -o $@
		@echo $(OK)
		@make -s -f std.Makefile

clean:
		@echo "[....] Removing $(NAME) objects\c"
		$(RM) $(OBJS) obj
		@echo $(OK)
		@make clean -s -f std.Makefile

fclean:
		@echo "[....] Removing $(NAME) objects\c"
		$(RM) $(OBJS) obj
		@echo $(OK)
		@echo "[....] Removing $(NAME)\c"
		$(RM) $(NAME)
		@echo $(OK)
		@make fclean -s -f std.Makefile

re:			fclean all

defense:	re
		@/bin/bash defense.sh

check:		fclean
		@if [ ! -d ft_containers_checker ]; then git clone https://github.com/busshi/ft_containers_checker.git; fi
		@cd ft_containers_checker && /bin/bash grademe.sh --no-leak

.PHONY:	all clean fclean re defense check
