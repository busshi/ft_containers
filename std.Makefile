# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    std.Makefile                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aldubar <aldubar@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/04 18:20:46 by aldubar           #+#    #+#              #
#    Updated: 2021/10/25 13:44:51 by aldubar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= std_containers

SRCS		= $(addprefix srcs/, main.cpp vector.cpp stack.cpp map.cpp)

OBJ_DIR		= obj/std

OBJS		= $(addprefix $(OBJ_DIR)/, $(SRCS:.cpp=.o))

FLAGS		= -Wall -Wextra -Werror -std=c++98 -Iincludes -DSTL=1

CC			= @clang++

RM			= @rm -rf

OK			= "\r[ \033[0;32mok\033[0m ]"

$(OBJ_DIR)/%.o:%.cpp
		@mkdir -p $(dir $@)
		$(CC) $(FLAGS) $< -c -o $@
			
all:		$(NAME)

$(NAME):	$(OBJS) $(OBJ_DIR)
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
