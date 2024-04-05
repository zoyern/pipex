# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/19 16:01:12 by marvin            #+#    #+#              #
#    Updated: 2024/04/05 03:23:52 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include build.mk

NAME		= pipex
CFLAG		= -Wall -Wextra -Werror -I./$(BUILD_INCLUDES) -g3 -gdwarf-4
CC			= cc

all : $(NAME)

$(NAME): $(OBJ) 
	$(CC) $(OBJ) -o $(BUILD_DIR)/$(NAME) $(CFLAG)

start :
	make re
	./$(BUILD_DIR)/$(NAME)

clear :
	@echo "42Paris : $(NAME)"
	@echo ""

clean : clear
	@rm -rf build/
	@echo "Clean   : *.o in build !"

fclean : clean
	@rm -f $(NAME)
	@echo "Clean   : ./$(NAME)"


val :
	@clear
	valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes --track-origins=yes ./$(BUILD_DIR)/$(NAME)
	@echo ""


re: fclean all clear 

.PHONY: all clean fclean re val