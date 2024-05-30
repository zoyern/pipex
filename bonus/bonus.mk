# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    bonus.mk                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: almounib <almounib@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/01 18:55:59 by marvin            #+#    #+#              #
#    Updated: 2024/05/30 11:10:30 by almounib         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BONUS_DIR		= $(CURDIR)/bonus

BONUS_FILES	= main.c

SRC_BONUS	= $(addprefix $(BONUS_DIR)/, $(BONUS_FILES))
