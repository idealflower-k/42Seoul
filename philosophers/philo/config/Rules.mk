.DEFAULT_ON_ERROR:
.DEFAULT_GOAL = all

PROJECT_NAME = philo

ARFLAGS = rcs
CFLAGS = -Wall -Wextra -Werror -MMD -MP

# verbose
Q := $(if $(filter 1,$(V) $(VERBOSE)),,@)

CPPFLAGS = -I$(TOPDIR)/includes -I$(TOPDIR)/src/src_m/includes
LDFLAGS = 
LDLIBS =

# debug
ifdef DEBUG
	CFLAGS = -g3 -MMD -MP
	LDFLAGS += -g3
endif

# just compile
ifdef JUST
	CFLAGS = -MMD -MP
endif

# address
ifdef ADDR
	CFLAGS += -fsanitize=address
endif

ifdef RACE
	CFLAGS += -g -fsanitize=thread
	LDFLAGS += -g -fsanitize=thread
endif

link_files:: unlink_files
	$(Q)$(call color_printf,$(GRAY),includes,📁 make includes folder)
	mkdir -p $(dst_dir);
	$(Q)$(foreach file,$(files), $(call color_printf,$(CYAN),$(file),🔗 linking file\n) ln -sf $(src_dir)/$(file) $(dst_dir);)
	$(Q)$(foreach file,$(files), ln -sf $(src_dir)/$(file) $(dst_dir);)

unlink_files::
	$(Q)$(foreach file,$(files), $(call color_printf,$(GRAY),$(file),🚫 unlinking file\n) $(RM) $(dst_dir)/$(file);)
	$(Q)$(foreach file,$(files), $(RM) $(dst_dir)/$(file);)
