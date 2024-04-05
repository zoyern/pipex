# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    src.mk                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/01 18:55:59 by marvin            #+#    #+#              #
#    Updated: 2024/04/01 18:55:59 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include $(CURDIR)/src/utils/utils.mk
include $(CURDIR)/src/memory/memory.mk
include $(CURDIR)/src/fork/fork.mk

SRC_DIR		= $(CURDIR)/src

DIR			= $(UTILS_DIR)
DIR			+= $(MEMORY_DIR)
DIR			+= $(FORK_DIR)

SRC_HEADER	= pipex.h type.h
SRC_HEADER	+= $(UTILS_HEAD)
SRC_HEADER	+= $(MEMORY_HEAD)
SRC_HEADER	+= $(FORK_HEAD)

SRC_FILES	= main.c
SRC_FILES	+= $(UTILS)
SRC_FILES	+= $(MEMORY)
SRC_FILES	+= $(FORK)

HEADERS		= $(addprefix $(SRC_DIR)/, $(SRC_HEADER))
SRC			= $(addprefix $(SRC_DIR)/, $(SRC_FILES))
FOLDERS		= $(addprefix $(SRC_DIR)/, $(DIR))
FOLDERS		+= $(SRC_DIR)