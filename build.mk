# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    build.mk                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: almounib <almounib@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/02 23:07:18 by marvin            #+#    #+#              #
#    Updated: 2024/05/16 14:30:56 by almounib         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include src/src.mk
include exemple/exemple.mk

#❖═══Setup══════════❖
NAME		= pipex

#❖═══Compilation════❖
CC			= cc
CFLAG		= -Wall -Wextra -Werror -I./$(BUILD_INCLUDES) -g3 -gdwarf-4
AR			= ar rc
LIB			= ranlib

#❖═══Build══════════❖
BUILD_DIR		= build
LIBRARY			= $(BUILD_DIR)/$(NAME).a
BUILD_OBJ		= $(BUILD_DIR)/obj
BUILD_INCLUDES	= $(BUILD_DIR)/includes
ALL_B_INCLUDES	= $(BUILD_INCLUDES)/$(NAME)

#❖═══Libs═══════════❖
LIBS_DIR			=	libs
DEPENDENCIES		=	sotypes:https://github.com/zoyern/sotypes.git \
						solibft:https://github.com/zoyern/solibft.git
LIBRARYS			= 
LIBS_OBJ			= 
LIBS_INCLUDES		= 
LIBS_HEADER			=
ALL_L_INCLUDES		=
ifdef DEPENDENCIES
	DEPENDENCIES_RULES = dependencies
else
	DEPENDENCIES_RULES = 
endif

#❖═══Dependencies═══❖
dependencies:
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

#❖═══Objet══════════❖
OBJ = $(patsubst $(SRC_DIR)/%.c,$(BUILD_OBJ)/%.o, $(SRC))

#❖═══Folders════════❖

$(BUILD_DIR): 
	mkdir -p $(dir $@)

$(BUILD_OBJ)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAG) -c $< -o $@

$(BUILD_INCLUDES):
	@mkdir -p $(BUILD_INCLUDES)
	@mkdir -p $(ALL_B_INCLUDES)
	@cp $(LIB_HEADER) $(BUILD_INCLUDES)
	@cp $(HEADERS) $(ALL_B_INCLUDES)

#❖═════Creat═════❖
$(NAME): $(BUILD_INCLUDES) $(DEPENDENCIES_RULES) $(OBJ)
	@${AR} $(LIBRARY) ${OBJ}
	@${LIB} $(LIBRARY)
	@$(CC) $(SRC_EXEMPLE) $(OBJ) -o $(NAME) $(CFLAG) $(LIBRARYS) $(LIBRARY)
