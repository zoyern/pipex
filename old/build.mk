# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    build.mk                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/02 23:07:18 by marvin            #+#    #+#              #
#    Updated: 2024/04/02 23:07:18 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include src/src.mk

BUILD_DIR		= build
BUILD_OBJ		= $(BUILD_DIR)/obj
BUILD_INCLUDES	= $(BUILD_DIR)/includes

OBJ = $(patsubst $(SRC_DIR)/%.c,$(BUILD_OBJ)/%.o, $(SRC))

$(OBJ): | $(BUILD_INCLUDES) 

$(BUILD_DIR): 
	mkdir -p $(dir $@)

$(BUILD_OBJ)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAG) -c $< -o $@

$(BUILD_INCLUDES):
	@mkdir -p $(BUILD_INCLUDES)
	@cp $(HEADERS) $(BUILD_INCLUDES)

