# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    gnl.mk                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/05 14:43:35 by amakinen          #+#    #+#              #
#    Updated: 2024/07/08 14:01:43 by amakinen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GNL_SRCS = $(addprefix src/gnl/,\
	get_next_line.c \
)

GNL_OBJS = $(GNL_SRCS:%.c=$(OBJDIR)/%.o)
OBJS += $(GNL_OBJS)

$(LIBFT): $(GNL_OBJS)
