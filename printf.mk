# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    printf.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/05 13:31:43 by amakinen          #+#    #+#              #
#    Updated: 2024/07/05 13:46:11 by amakinen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PRINTF_SRCS = $(addprefix printf/,\
	ft_printf.c \
	util.c \
	padding_util.c \
	specifier.c \
	format_char.c \
	format_string.c \
	format_pointer.c \
	format_integer.c \
)

PRINTF_OBJS = $(PRINTF_SRCS:%.c=$(OBJDIR)/%.o)
OBJS += $(PRINTF_OBJS)
$(PRINTF_OBJS): tgt_CPPFLAGS += -I libft

$(LIBFT): $(PRINTF_OBJS)
