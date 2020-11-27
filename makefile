.PHONY: all trash clean fclean re

# COLORS FOR OUTPUT
BLUE = "\e[38;5;69m"
EOC = "\e[0m"

# COMPILER SETTINGS
CC = clang
# CFLAGS = -Wall -Wextra -Werror -g

# LIB (LIBFT, GET_NEXT_LINE, PRINTF)
L_DIR = lib/
L_NAME = lib.a
L_RULE = $(addsuffix .lib, $(L_DIR))

# HEADER DIR
H_DIR = include/

# HEADER NAME
H_NAME = ft_ls ft_ls_flags ft_ls_err
H_NAME := $(addprefix $(H_DIR), $(addsuffix .h, $(H_NAME)))

# PROGRAM NAME
PROG_NAME = a.out

# PROGRAM DIR
PROG_DIR := src/

# PROGRAM SRCS
PROG_SRC = main \
			av_parse \
			parse \
			flags \
			extra \
			sort \
			format_out \
			format_out_attb
PROG_SRC := $(addsuffix .c, $(PROG_SRC))

# FILE PATH TO LIB, PROGRAM SRC/OBJ FILES
PROG_SRC := $(addprefix $(PROG_DIR), $(PROG_SRC))
L_NAME := $(addprefix $(L_DIR), $(L_NAME))

# colour:
				# @echo "\e[38;5;69m"
# %.lib:	colour

all: $(L_RULE) $(PROG_NAME)

%.lib:
	@$(MAKE) -sC $(L_DIR)

$(PROG_NAME) : $(PROG_SRC) $(H_NAME) $(L_NAME)
	@$(CC) $(CFLAGS) $(PROG_SRC) $(L_NAME) -I $(L_DIR)$(H_DIR) -o $(PROG_NAME) -I $(H_DIR)
	@echo $(BLUE)"FT_LS COMPILED"$(EOC)

trash:
	@rm -rf *.dSYM/

clean:
	@$(MAKE) -sC $(L_DIR) clean

fclean: clean trash
	@$(MAKE) -sC $(L_DIR) fclean
	@rm -f $(PROG_NAME)

re: fclean all