# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/04 16:15:48 by amakinen          #+#    #+#              #
#    Updated: 2024/07/05 13:42:39 by amakinen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Output directories
OBJDIR = obj
LIBDIR = lib
BINDIR = bin

# Include module snippets that specify the targets, their dependencies, any
# target-specific variables and so on. Add targets to OBJS/LIBS/BINS to select
# a default recipe from this file.
include base.mk
include list.mk
include printf.mk
include testfw.mk
include base-test.mk
include printf-test.mk

# Default compiler flags that apply to all targets
def_CFLAGS = -Wall -Wextra -Werror
def_CPPFLAGS = -MMD -MP

# Add sanitizer flags if requested
ifneq (,$(strip $(SANITIZE)))
    def_CFLAGS += -g -fsanitize=$(SANITIZE)
    def_LDFLAGS += -g -fsanitize=$(SANITIZE)
endif

# Combine default def_FLAGS, target specific tgt_FLAGS and user-supplied FLAGS
# into one _FLAGS variable to be used in recipes
flagvars = CFLAGS CPPFLAGS LDFLAGS LDLIBS
$(foreach v,$(flagvars),$(eval _$v = $$(strip $$(def_$v) $$(tgt_$v) $$($v))))

# Generic utility targets
.DEFAULT_GOAL = all

.PHONY: all clean fclean re

all: $(LIBFT)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(BINDIR) $(LIBDIR)

re: fclean all

# Recipe command to ensure directory for target exists
mktargetdir = @mkdir -p $(@D)

# Default recipes for each type of target
$(OBJS): $(OBJDIR)/%.o: %.c
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

# Dependency files to handle #include dependencies
DEPS = $(OBJS:.o=.d)
-include $(DEPS)
