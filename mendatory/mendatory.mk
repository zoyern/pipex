# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    mendatory.mk                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: almounib <almounib@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/01 18:55:59 by marvin            #+#    #+#              #
#    Updated: 2024/05/30 11:09:26 by almounib         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MENDATORY_DIR		= $(CURDIR)/mendatory

MENDATORY_FILES	= main.c

SRC_MENDATORY	= $(addprefix $(MENDATORY_DIR)/, $(MENDATORY_FILES))
