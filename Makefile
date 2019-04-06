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
ECHO = echo "`expr "   [\`expr $C '*' 100 / $T\`" : '.*\(....\)$$'`%]"
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
BUILD_VERSION = $$(cat $(BUILD_NUMBER_FILE))

# Dir/Files Path

S_PATH = srcs/
H_PATH = includes/
B_PATH = build/
O_PATH = build/objs/
L_PATH = libft/

DB_PATH = build/objs/db/
CR_PATH = build/objs/core/
MS_PATH = build/objs/misc/

OBJP = "$(O_PATH){core,db,misc}*.o"

# Files

SRC += $(S_PATH)core/minishell.c

SRC += $(S_PATH)misc/build.c

# Objects and Headers

OBJ = $(patsubst $(S_PATH)%.c, $(O_PATH)%.o, $(SRC))
HDR = $(H_PATH)$(HNAME)
LIB = $(L_PATH)$(LNAME)

# Variables

C_GCC = gcc $(CFLAG)
CMPLC = $(C_GCC) -c -I$(H_PATH)
CMPLO = $(C_GCC) -o
BUILD = $(B_PATH) $(O_PATH) $(DB_PATH) $(MS_PATH) $(CR_PATH)
AR_RC = ar rcma
RANLI = ranlib
RM_RF = /bin/rm -rf
MKDIR = mkdir -p
NORME = norminette
GCFIL = "\t- >\tCompiling\t-"
GCLAR = "\t- }\tArchiving\t-"
GCLIN = "\t- =t\Linking\t-"
GCIND = "\t- *\tIndexing\t-"
RMSHW = "\t- -\tRemoving\t-"
MKSHW = "\t- +\tCreating\t-"
DLSHW = "\t- ~\tDownloading\t-"
EXSHW = "\t- .\tExecuting\t-"
GCRUN = echo "$(G_C)===========>\tCompilation\t RUNNING$(RESET_C)"
GCSUC = "$(G_C)====>\tCompilation\t SUCCESS$(RESET_C)"
CLRUN = echo "$(R_C)===========>\tCleanup\t\t RUNNING$(RESET_C)"
CLSUC = "$(R_C)====>\tCleanup\t\t SUCCESS$(RESET_C)"
FCRUN = echo "$(R_C)===========>\tForce Cleanup\t RUNNING$(RESET_C)"
FCSUC = "$(R_C)====>\tForce Cleanup\t SUCCESS$(RESET_C)"
NORMR = echo "$(Y_C)===========>\tNorminette\t RUNNING$(RESET_C)"
NORMD = "$(G_C)====>\tNorminette\t DONE$(RESET_C)"
TESTR = echo "$(M_C)===========>\tTESTS\t\t RUNNING$(RESET_C)"
TESTD = "$(M_C)====>\tTESTS\t\t DONE$(RESET_C)"
GCC_O = "$(B_C)====>\tCompiled with\t- $(CFLAG)$(RESET_C)"

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
	@$(ECHO) $(GCC_O)
	@$(ECHO) $(GCSUC)
	@echo "\n$(G_C)>>>>>>>>>>>>\t$(RESET_C)$@ v.$(BUILD_VERSION)_$(BUILD_DATE)_$(BUILD_BRANCH) is ready !"
	@cp $(NAME) $(B_PATH)$(NAME)_$(BUILD_VERSION)_$(BUILD_DATE)_$(BUILD_BRANCH)

$(OBJ): $(O_PATH)%.o: $(S_PATH)%.c $(HDR)
	@$(CMPLC) -DBUILD=$(BUILD_VERSION) -DDATE=$(BUILD_DATE) -DBRANCH=$(BUILD_BRANCH) $< -o $@
	@$(ECHO) $(GCFIL) $@

$(BUILD_NUMBER_FILE): $(OBJ)
	@if ! test -f $(BUILD_NUMBER_FILE); then echo 0 > $(BUILD_NUMBER_FILE); fi
	@echo $$(($$(cat $(BUILD_NUMBER_FILE)) + 1)) > $(BUILD_NUMBER_FILE)

$(B_PATH):
	@$(GCRUN)
	@$(MKDIR) $(B_PATH)
	@$(ECHO) $(MKSHW) $(B_PATH)

$(O_PATH):
	@$(MKDIR) $(O_PATH)
	@$(ECHO) $(MKSHW) $(O_PATH)

$(CR_PATH):
	@$(MKDIR) $(CR_PATH)
	@$(ECHO) $(MKSHW) $(CR_PATH)

$(DB_PATH):
	@$(MKDIR) $(DB_PATH)
	@$(ECHO) $(MKSHW) $(DB_PATH)

$(MS_PATH):
	@$(MKDIR) $(MS_PATH)
	@$(ECHO) $(MKSHW) $(MS_PATH)

norme:
	@$(NORMR)
	@$(NORME) $(SRC) $(H_PATH)$(HNAME)
	@$(ECHO) $(NORMD)

clean: libco
	@$(CLRUN)
	@$(RM_RF) $(OBJ)
	@$(ECHO) $(RMSHW) $(OBJP)
	@$(ECHO) $(CLSUC)

fclean: libc
	@$(FCRUN)
	@$(RM_RF) $(OBJ)
	@$(ECHO) $(RMSHW) $(OBJP)
	@$(RM_RF) $(CR_PATH)
	@$(ECHO) $(RMSHW) $(CR_PATH)
	@$(RM_RF) $(DB_PATH)
	@$(ECHO) $(RMSHW) $(DB_PATH)
	@$(RM_RF) $(O_PATH)
	@$(ECHO) $(RMSHW) $(O_PATH)
	@$(RM_RF) $(MS_PATH)
	@$(ECHO) $(RMSHW) $(MS_PATH)
	@$(RM_RF) $(B_PATH)
	@$(ECHO) $(RMSHW) $(B_PATH)
	@$(RM_RF) $(NAME)
	@$(ECHO) $(RMSHW) $(NAME)
	@$(ECHO) $(FCSUC)

libm:
	@make -C $(L_PATH)

libco:
	@make clean -C $(L_PATH)

libc:
	@make fclean -C $(L_PATH)

#test:
#	@$(TESTR)
#	@git clone -q https://github.com/acuD1/$(TNAME).git $(B_PATH)test
#	@$(ECHO) $(DLSHW) $(TNAME)
#	@echo "$(Y_C)STILL IN BETA : Go to build/test and modify Makefile \
#		manually fear each test_*.c and run make re (IF TEST AVAILABLE)$(RESET_C)"
#	@$(ECHO) $(TESTD)

re:
	@$(MAKE) --no-print-directory fclean all

endif
