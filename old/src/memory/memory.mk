# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    memory.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/05 02:15:59 by marvin            #+#    #+#              #
#    Updated: 2024/04/05 02:15:59 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MEMORY_DIR		= memory

MEMORY_HEADER	= memory.h
MEMORY_FILE		= solib_memory.c solib_free.c solib_malloc.c \
				solib_memory_add.c solib_memory_clear.c solib_memory_free.c \
				solib_memory_show.c

MEMORY			= $(addprefix $(MEMORY_DIR)/, $(MEMORY_FILE))
MEMORY_HEAD		= $(addprefix $(MEMORY_DIR)/, $(MEMORY_HEADER))