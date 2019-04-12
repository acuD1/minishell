define MSG
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile for minishell                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/14 19:23:44 by arsciand          #+#    #+#              #
#                                                     ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
endef

# Progress bar

ifneq ($(words $(MAKECMDGOALS)),1)
.DEFAULT_GOAL = make
%:
	  @$(MAKE) $@ --no-print-directory -rRf $(firstword $(MAKEFILE_LIST))
else
ifndef ECHO
T := $(shell $(MAKE) $(MAKECMDGOALS) --no-print-directory \
	  -nrRf $(firstword $(MAKEFILE_LIST)) \
	  ECHO="OutputPrintable" | grep -c "OutputPrintable")
N := x
C = $(words $N)$(eval N := x $N)
V = "`expr "   [\`expr $C '*' 100 / $T\`" : '.*\(....\)$$'`%]"
ECHO = printf "\e[1A\r%s %s %s                        \n" $V
endif

# Color

RESET_C = \033[m
B_C = \033[0;34m
Y_C = \033[0;33m
G_C = \033[0;32m
R_C = \033[0;31m
M_C = \033[0;35m
C_C = \033[0;36m

# Programms names

NAME = minishell
HNAME = minishell.h
LNAME = libft.a
#TNAME =

# Version

BUILD_NUMBER_FILE = .build-number
BUILD_DATE = $$(date +'%Y%m%d')
BUILD_BRANCH = $$(git symbolic-ref HEAD 2>/dev/null | cut -d"/" -f 3)
BUILD_VERSION = $$(cat .version)
BUILD_NUMBER = $$(cat $(BUILD_NUMBER_FILE))

# Dir/Files Path

S_PATH = srcs/
H_PATH = includes/
B_PATH = build/
O_PATH = build/objs/
L_PATH = libft/

DB_PATH = build/objs/db/
CR_PATH = build/objs/core/
MS_PATH = build/objs/misc/

PATHS = $(B_PATH) $(O_PATH) $(DB_PATH) $(CR_PATH) $(MS_PATH)

OBJP = "$(O_PATH){core,db,misc}*.o"

# Files

SRC += $(S_PATH)core/minishell.c
SRC += $(S_PATH)core/set_env.c
SRC += $(S_PATH)core/free_list.c
SRC += $(S_PATH)core/get_opt.c

SRC += $(S_PATH)misc/build.c
SRC += $(S_PATH)misc/helper.c
SRC += $(S_PATH)misc/exit_status.c

SRC += $(S_PATH)dev.c

# Objects and Headers

OBJ = $(patsubst $(S_PATH)%.c, $(O_PATH)%.o, $(SRC))
HDR = $(H_PATH)$(HNAME)
LIB = $(L_PATH)$(LNAME)

# Variables

C_GCC = gcc $(CFLAG)
CMPLC = $(C_GCC) -c -I$(H_PATH)
CMPLO = $(C_GCC) -o
BUILD = $(PATHS)
AR_RC = ar rc
RANLI = ranlib
CFLAG = -Wall -Wextra -Werror
RM_RF = /bin/rm -rf
MKDIR = mkdir -p
NORME = norminette
SLEEP = sleep 0.01
GCFIL = "	- >	  Compiling		-"
GCLAR = "	- }	  Archiving		-"
GCLIN = "	- =	  Linking		-"
GCIND = "	- *	  Indexing		-"
RMSHW = "	- -	  Removing		-"
MKSHW = "	- +	  Creating		-"
DLSHW = "	- ~	  Downloading		-"
EXSHW = "	- .	  Executing		-"
GCRUN = echo ">\n$(G_C)---------->\tCompiling$(RESET_C)\n"
CLRUN = echo ">\n$(R_C)---------->\tCleaning$(RESET_C)\n"
FCRUN = echo ">\n$(R_C)---------->\tForce Cleaning$(RESET_C)\n"
NORMR = echo ">\n$(Y_C)---------->\tNorminette$(RESET_C)"
GCSUC = echo "$(G_C)==========>\tSUCCESS$(RESET_C)"
CLSUC = echo "$(R_C)==========>\tDONE$(RESET_C)"
NORMD = echo "$(G_C)==========>\tDONE$(RESET_C)"

.PHONY: all norme clean fclean re test

DEBUG =

ifeq ($(DEBUG), g)
	CFLAG = -g
else ifeq ($(DEBUG), fsanitize)
	CFLAG = -fsanitize=address
else
	CFLAG = -Wall -Wextra -Werror
endif

# Rules
make:
	$(MSG)
	@$(MAKE) --no-print-directory all

all: libm $(BUILD) $(NAME)

$(NAME): $(OBJ) $(BUILD_NUMBER_FILE)
	@$(ECHO) $(GCFIL) $(NAME)
	@$(CMPLO) $(NAME) $(OBJ) $(LIB)
	@$(GCSUC)
	@echo "---\nCFLAG\t- >$(B_C)\t$(CFLAG)$(RESET_C)\n---"
	@echo "\n$(G_C)[$(BUILD_BRANCH)]\t=>\t$(RESET_C)$@ v.$(BUILD_VERSION)_$(BUILD_NUMBER)_$(BUILD_DATE) is ready !"
	@cp $(NAME) $(B_PATH)$(NAME)_$(BUILD_VERSION)_$(BUILD_NUMBER)_$(BUILD_DATE)

$(OBJ): $(O_PATH)%.o: $(S_PATH)%.c $(HDR)
	@$(CMPLC) -DBUILDV=$(BUILD_VERSION) -DBUILDN=$(BUILD_NUMBER) -DDATE=$(BUILD_DATE) $< -o $@
	@$(ECHO) $(GCFIL) $<

$(BUILD_NUMBER_FILE): $(OBJ)
	@if ! test -f $(BUILD_NUMBER_FILE); then echo 0 > $(BUILD_NUMBER_FILE); fi
	@echo $$(($$(cat $(BUILD_NUMBER_FILE)) + 1)) > $(BUILD_NUMBER_FILE)

$(PATHS):
	@$(GCRUN)
	@$(MKDIR) $(PATHS)
	@$(foreach var,$(PATHS), $(ECHO) $(MKSHW) $(var);)

norme:
	@$(NORMR)
	@$(NORME) $(SRC) $(H_PATH)$(HNAME)
	@$(NORMD)

clean: libco
	@$(CLRUN)
	@for i in $(OBJ); do $(RM_RF) $$i; $(ECHO) $(RMSHW) $$i; done
	@$(CLSUC)

fclean: libc
	@$(FCRUN)
	@for i in $(OBJ); do $(RM_RF) $$i; $(ECHO) $(RMSHW) $$i; done
	@for i in $(PATHS); do $(RM_RF) $$i; $(ECHO) $(RMSHW) $$i; done
	@$(RM_RF) $(NAME)
	@$(ECHO) $(RMSHW) $(NAME)
	@$(CLSUC)

libm:
	@make -C $(L_PATH)

libco:
	@make clean -C $(L_PATH)

libc:
	@make fclean -C $(L_PATH)

re:
	@$(MAKE) --no-print-directory fclean all

endif
