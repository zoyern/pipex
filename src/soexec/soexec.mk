# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    fork.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/07 20:23:13 by marvin            #+#    #+#              #
#    Updated: 2024/04/07 20:23:13 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SOEXEC_DIR		=	soexec

SOEXEC_HEADER	=	soexec.h
SOEXEC_FILE		=	soexec.c soexec2.c

SOEXEC			=	$(addprefix $(SOEXEC_DIR)/, $(SOEXEC_FILE))
SOEXEC_HEAD		=	$(addprefix $(SOEXEC_DIR)/, $(SOEXEC_HEADER))