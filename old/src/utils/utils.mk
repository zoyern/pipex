# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    utils.mk                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/01 21:30:53 by marvin            #+#    #+#              #
#    Updated: 2024/04/01 21:30:53 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

UTILS_DIR		= utils

UTILS_HEADER	= utils.h
UTILS_FILE		= utils.c solib.c ft_split.c ft_substr.c ft_strmcat.c

UTILS			= $(addprefix $(UTILS_DIR)/, $(UTILS_FILE))
UTILS_HEAD		= $(addprefix $(UTILS_DIR)/, $(UTILS_HEADER))