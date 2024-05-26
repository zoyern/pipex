# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: almounib <almounib@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/19 16:01:12 by marvin            #+#    #+#              #
#    Updated: 2024/04/18 10:50:51 by almounib         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include build.mk

NAME		= pipex
CFLAG		= -Wall -Wextra -Werror -I./$(BUILD_INCLUDES) -g3 -gdwarf-4
CC			= cc
ARGV		= infile "ls -la" "grep -o almounib.*" "head -n 6" outfile
#ARGV		= infile "ls -la" outfile

all : $(NAME)

$(NAME): $(OBJ) 
	$(CC) $(OBJ) -o $(BUILD_DIR)/$(NAME) $(CFLAG)

start :
	@make re
	@make clear
	@./$(BUILD_DIR)/$(NAME) $(ARGV)

clear :
	@clear
	@echo "42Paris : $(NAME)"
	@echo ""

clean : clear
	@rm -rf build/
	@echo "Clean   : *.o in build !"

fclean : clean
	@rm -f $(NAME)
	@echo "Clean   : ./$(NAME)"


val :
	@make re
	@clear
	valgrind --leak-check=full --track-fds=yes --show-leak-kinds=all --trace-children=yes --track-origins=yes ./$(BUILD_DIR)/$(NAME) $(ARGV)
	@echo ""

check : 
	@make re
	@clear
	funcheck -o ./$(BUILD_DIR)/$(NAME) $(ARGV)
	@echo ""

re: fclean all clear 

.PHONY: all clean fclean re val