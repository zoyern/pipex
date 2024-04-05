# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    fork.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/05 02:43:46 by marvin            #+#    #+#              #
#    Updated: 2024/04/05 02:43:46 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FORK_DIR		= fork

FORK_HEADER		= fork.h
FORK_FILE		= fork.c

FORK			= $(addprefix $(FORK_DIR)/, $(FORK_FILE))
FORK_HEAD		= $(addprefix $(FORK_DIR)/, $(FORK_HEADER))