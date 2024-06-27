# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    libft.mk                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/27 13:32:55 by amakinen          #+#    #+#              #
#    Updated: 2024/06/27 15:05:14 by amakinen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BASE_SRCS = $(addprefix src/base/,\
	ft_isalpha.c \
	ft_isdigit.c \
	ft_isalnum.c \
	ft_isascii.c \
	ft_isprint.c \
	ft_strlen.c \
	ft_memset.c \
	ft_bzero.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_strlcpy.c \
	ft_strlcat.c \
	ft_toupper.c \
	ft_tolower.c \
	ft_strchr.c \
	ft_strrchr.c \
	ft_strncmp.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_strnstr.c \
	ft_atoi.c \
	ft_calloc.c \
	ft_strdup.c \
	ft_substr.c \
	ft_strjoin.c \
	ft_strtrim.c \
	ft_split.c \
	ft_itoa.c \
	ft_strmapi.c \
	ft_striteri.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
)

LIST_SRCS = $(addprefix src/list/,\
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

LIBFT_SRCS = $(BASE_SRCS) $(LIST_SRCS)
LIBFT_OBJS = $(LIBFT_SRCS:src/%.c=$(BUILDDIR)/%.o)
OBJS += $(LIBFT_OBJS)
$(LIBFT_OBJS): $(BUILDDIR)/%.o: src/%.c

LIBFT = $(LIBDIR)/libft.a
LIBS += $(LIBFT)
$(LIBFT): $(LIBFT_OBJS)
