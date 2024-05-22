# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    src.mk                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: almounib <almounib@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/01 18:55:59 by marvin            #+#    #+#              #
#    Updated: 2024/05/20 17:05:51 by almounib         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR		=	$(CURDIR)/src

LIB_HEADER	=	$(addprefix $(SRC_DIR)/, pipex.h)
SRC_HEADER	=	types.h all.h
SRC_FILES	=	pipex.c

DIR			+= $(PSWP_DIR)

SRC_HEADER	+= $(PSWP_HEAD)

SRC_FILES	+= $(PSWP)

HEADERS		=	$(addprefix $(SRC_DIR)/, $(SRC_HEADER))
SRC			=	$(addprefix $(SRC_DIR)/, $(SRC_FILES))
FOLDERS		=	$(addprefix $(SRC_DIR)/, $(DIR))
FOLDERS		+=	$(SRC_DIR)
