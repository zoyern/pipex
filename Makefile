# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: almounib <almounib@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/19 16:01:12 by marvin            #+#    #+#              #
#    Updated: 2024/05/12 22:30:14 by almounib         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include build.mk

#❖═════Commandes══════❖
all : $(NAME)

start :
	@make re
	@make clear
	@echo "------------------------------------"
	@./$(NAME) in "grep $(filter-out $@, $(MAKECMDGOALS))" "cat" out
	@echo "------------------------------------"

%:
	@true

clear :
	@clear
	@echo "42Paris : $(NAME)"
	@echo ""

clean : clear
	@rm -rf build/
	@echo "Clean   : *.o in build !"

fclean : clean
	@rm -f $(NAME)
	@rm -rf libs
	@echo "Clean   : ./$(NAME)"


val :
	@make re
	@clear
	@echo "------------------------------------"
	valgrind --leak-check=full --track-fds=yes --show-leak-kinds=all --track-origins=yes --track-fds=yes ./$(NAME) in "grep $(filter-out $@, $(MAKECMDGOALS))" "cat" out
	@echo "------------------------------------"
#valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --trace-children=yes --suppressions=supp.supp ./pipex infile cat ls outfile
check : 
	@make re
	@clear
	@echo "------------------------------------"
	funcheck -o ./$(NAME) $(filter-out $@, $(MAKECMDGOALS))
	@echo "------------------------------------"

re: fclean all clear 

.PHONY: all start clean fclean re val dependencies check