# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    std.Makefile                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aldubar <aldubar@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/04 18:20:46 by aldubar           #+#    #+#              #
#    Updated: 2021/11/02 10:17:17 by aldubar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= std_containers

TESTS		= $(addprefix tests/, main.cpp testVector.cpp testStack.cpp testMap.cpp)

HEADER_TEST	= $(addprefix tests/, testVector.hpp testStack.hpp testMap.hpp)

OBJ_DIR		= obj/std

OBJS		= $(addprefix $(OBJ_DIR)/, $(TESTS:.cpp=.o))

FLAGS		= -Wall -Wextra -Werror -std=c++98 -Iincludes -DSTL=1

CC			= @clang++

RM			= @rm -rf

OK			= "\r[ \033[0;32mok\033[0m ]"

$(OBJ_DIR)/%.o:%.cpp
		@mkdir -p $(dir $@)
		$(CC) $(FLAGS) $< -c -o $@
			
all:		$(NAME)

$(NAME):	$(OBJS) $(OBJ_DIR) $(HEADER_TEST)
		@echo "[....] Compiling $(NAME)\c"
		$(CC) $(FLAGS) $(OBJS) -o $@
		@echo $(OK)

clean:
		@echo "[....] Removing $(NAME) objects\c"
		$(RM) $(OBJS) $(OBJ_DIR)
		@echo $(OK)

fclean:		clean
		@echo "[....] Removing $(NAME)\c"
		$(RM) $(NAME)
		@echo $(OK)

re:			fclean all

.PHONY:	all clean fclean re
