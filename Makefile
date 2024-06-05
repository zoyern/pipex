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

#❖═══Dependencies═══❖
dependencies: $(BUILD_INCLUDES)
	@mkdir -p $(LIBS_DIR)
	@for dep in $(DEPENDENCIES); do \
		name=$$(echo $$dep | cut -d ':' -f 1); \
		url=$$(echo $$dep | awk -F':' '{print substr($$0, index($$0, ":") + 1)}'); \
		if [ ! -d $(LIBS_DIR)/$$name ]; then \
			echo "Cloning $$name..."; \
			git clone $$url $(LIBS_DIR)/$$name; \
		else \
			echo "Pulling $$name..."; \
			(cd $(LIBS_DIR)/$$name && git pull -f); \
		fi; \
	done
	@$(eval LIBRARYS += $(foreach dep,$(DEPENDENCIES),$(LIBS_DIR)/$(firstword $(subst :, ,$(dep)))/$(BUILD_DIR)/$(firstword $(subst :, ,$(dep))).a))
	@$(eval LIBS_OBJ += $(foreach dep,$(DEPENDENCIES),$(LIBS_DIR)/$(firstword $(subst :, ,$(dep)))/$(BUILD_DIR)/obj))
	@$(eval LIBS_INCLUDES += $(foreach dep,$(DEPENDENCIES),$(LIBS_DIR)/$(firstword $(subst :, ,$(dep)))/$(BUILD_DIR)/includes))
	@$(eval LIBS_HEADER += $(foreach dep,$(DEPENDENCIES),$(LIBS_DIR)/$(firstword $(subst :, ,$(dep)))/$(BUILD_DIR)/includes/$(firstword $(subst :, ,$(dep))).h))
	@$(eval ALL_L_INCLUDES += $(foreach dep,$(DEPENDENCIES),$(LIBS_DIR)/$(firstword $(subst :, ,$(dep)))/$(BUILD_DIR)/includes/$(firstword $(subst :, ,$(dep)))))
	@cp $(LIBS_HEADER) $(BUILD_INCLUDES)
	@cp -r $(ALL_L_INCLUDES) $(BUILD_INCLUDES)

re: clean all clear 

.PHONY: all start clean fclean re val dependencies check