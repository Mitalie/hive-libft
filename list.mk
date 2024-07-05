# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    list.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/05 12:56:52 by amakinen          #+#    #+#              #
#    Updated: 2024/07/05 13:26:54 by amakinen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIST_SRCS = $(addprefix libft/,\
	ft_lstnew.c \
	ft_lstadd_front.c \
	ft_lstsize.c \
	ft_lstlast.c \
	ft_lstadd_back.c \
	ft_lstdelone.c \
	ft_lstclear.c \
	ft_lstiter.c \
	ft_lstmap.c \
)

LIST_OBJS = $(LIST_SRCS:%.c=$(OBJDIR)/%.o)
OBJS += $(LIST_OBJS)

$(LIBFT): $(LIST_OBJS)
