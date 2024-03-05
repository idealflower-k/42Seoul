$(DIRS):
	@$(MAKE) -C $@ $(J)

all bonus :
	@$(MAKE) $(DIRS)
	@$(call color_printf,$(YELLOW),$(NAME),🎯 Start compiling)
	@$(MAKE) $(NAME)
	@$(call color_printf,$(GREEN),$(NAME),✨ compiled!)

$(NAME): $(OBJS) $(LIBS)
	$(LINK.cc) $^ $(LOADLIBES) $(LDLIBS) -o $@
	$(MAKE) files="$(NAME)" src_dir=`pwd` dst_dir=$(TOPDIR) link_files

clean:
	@$(foreach dir, $(DIRS), $(MAKE) TOPDIR=$(TOPDIR) -C $(dir) $(J) $@;)
	$(RM) $(DEPS) $(OBJS)

fclean: clean
	@$(foreach dir, $(DIRS), $(MAKE) TOPDIR=$(TOPDIR) -C $(dir) $(J) $@;)
	$(MAKE) files="$(NAME)" src_dir=`pwd` dst_dir=$(TOPDIR) unlink_files
	$(RM) $(NAME)

re: fclean
	@$(foreach dir, $(DIRS), $(MAKE) TOPDIR=$(TOPDIR) -C $(dir) $(J) $@;)
	$(MAKE)

check : $(OBJS)
	@$(MAKE) $(DIRS)

.PHONY: all bonus clean fclean re $(DIRS) check