ifndef TOPDIR
		TOPDIR = $(abspath ../../../)
endif

include $(TOPDIR)/make_config/com/ColorRules.mk
include $(TOPDIR)/make_config/com/Funcs.mk
include $(TOPDIR)/make_config/src/Rules.mk
include $(TOPDIR)/make_config/com/Flags.mk

SRCS :=	parser.c \
		ft_split_whitespace.c \
		parser_ambient.c \
		parser_camera.c \
		parser_lights.c \
		parser_sphere.c \
		parser_plane.c \
		parser_cylinder.c \
		parser_point_vec.c \
		parser_atod.c \
		parser_utils.c \
		parser_utils2.c \
		parser_print.c \
		parser_print_objs.c

NAME := parser.a

OBJS := $(SRCS:.c=.o)
DEPS := $(SRCS:.c=.d)
-include $(DEPS)

include $(TOPDIR)/make_config/src/SubLibsRecipes.mk
