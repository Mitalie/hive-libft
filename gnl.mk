# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    gnl.mk                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/05 14:43:35 by amakinen          #+#    #+#              #
#    Updated: 2024/07/05 17:58:32 by amakinen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GNL_SRCS = $(addprefix src/gnl/,\
	get_next_line.c \
	get_next_line_utils.c \
)

GNL_OBJS = $(GNL_SRCS:%.c=$(OBJDIR)/%.o)
OBJS += $(GNL_OBJS)

$(LIBFT): $(GNL_OBJS)
