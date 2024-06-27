# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/16 17:07:39 by amakinen          #+#    #+#              #
#    Updated: 2024/06/27 15:26:24 by amakinen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Output directories
BINDIR = bin
BUILDDIR = build
LIBDIR = lib

# Module snippets that specify the target names and dependencies
include libft.mk
include test.mk

# Default compiler flags that apply to all targets
def_CFLAGS = -Wall -Wextra -Werror
def_CPPFLAGS = -MMD -MP -I include

# Combine default def_FLAGS, target specific tgt_FLAGS and user-supplied FLAGS
# into one _FLAGS variable to be used in recipes
flagvars = CFLAGS CPPFLAGS LDFLAGS LDLIBS
$(foreach v,$(flagvars),$(eval _$v = $$(strip $$(def_$v) $$(tgt_$v) $$($v))))

# Generic utility targets
.DEFAULT_GOAL = all

.PHONY: all clean fclean re

all: $(LIBFT)

clean:
	rm -rf $(BUILDDIR)

fclean: clean
	rm -rf $(BINDIR) $(LIBDIR)

re: fclean all

# Helper recipe command to ensure directory for target exists
mktargetdir = @mkdir -p $(@D)

# Recipes for each type of target
$(OBJS):
	$(mktargetdir)
	$(CC) $(_CPPFLAGS) $(_CFLAGS) -c $< -o $@

$(LIBS):
	$(mktargetdir)
	$(AR) -crs $@ $?

$(BINS):
	$(mktargetdir)
	$(CC) $(_LDFLAGS) $^ $(_LDLIBS) -o $@

# Inform make that object files don't need to be remade if the requested
# targets are up to date with respect to the source files.
.SECONDARY: $(OBJS)

# Dependency files to handle header dependencies
DEPS = $(OBJS:.o=.d)
-include $(DEPS)
