#--------------------TARGETS------------------------#

NAME = minishell

#------------------DIRECTORIES----------------------#

DIR_BIN			=	./bin
DIR_INCLUDE		=	./includes
DIR_SRC			=	./src
DIR_BUILTINS	=	./builtins
DIR_UTILS		=	./utils
DIR_LIBFT		=	$(DIR_INCLUDE)/libft

#-----------------COMP FLAGS------------------------#

UNAME := $(shell uname)
CC		= gcc
CFLAGS	= -Wall -Werror -Wextra -g
ifeq ($(UNAME), Darwin)
CFLAGS += -g -fsanitize=address
endif

#---------------------VPATH------------------------#

vpath %.c $(DIR_SRC):$(DIR_SRC)/parsing

#---------------------SOURCE------------------------#

SRCS				=	main.c \
						print.c \
						init_mini.c \
						dollar_sign.c \
						fill_cmd_struct.c \
						get_cmd_args.c \
						get_cmd_bin.c \
						get_cmd_type.c \
						parsing.c \
						quotes.c 

UTILS				=	contain_char.c \
						contain_quotes.c \
						contain_string_at_specific_index.c \
						enquote_str.c \
						epurstring.c \
						is_only_spaces.c \
						is_quote.c \
						is_space.c 

BUILTINS			=	cd.c \
						echo.c \
						env.c \
						exit.c \
						export.c \
						pwd.c \
						unset.c 

#---------------------OBJECTS------------------------#

SRC_OBJ				=	$(addprefix $(DIR_BIN)/src/, $(SRCS:.c=.o))
UTILS_OBJ			=	$(addprefix $(DIR_BIN)/utils/, $(UTILS:.c=.o))
BUILTINS_OBJ		=	$(addprefix $(DIR_BIN)/builtins/, $(BUILTINS:.c=.o))
ALL_OBJ				=	$(SRC_OBJ) $(UTILS_OBJ) $(BUILTINS_OBJ)

#------------------INCLUDE FLAGS---------------------#

INCLUDE_FLAGS		=	-I$(DIR_INCLUDE) -I$(DIR_LIBFT)/include
LIBRARY_PATH		=	-L$(DIR_LIBFT)
LIBRARIES			=	 -lft -l readline

#---------------------TARGETS------------------------#

all:	$(NAME)

$(NAME): $(ALL_OBJ) | $(DIR_BIN)
	@make -s -C $(DIR_LIBFT)
	@make -s bonus -C $(DIR_LIBFT)
	@$(CC) $(ALL_OBJ) $(CFLAGS) $(LIBRARY_PATH) $(LIBRARIES) -o $@

$(DIR_BIN)/src/%.o: $(DIR_SRC)/parsing/%.c | $(DIR_BIN)/src
	@$(CC) $(CFLAGS) $(INCLUDE_FLAGS) -c $< -o $@

$(DIR_BIN)/src/%.o: $(DIR_SRC)/%.c | $(DIR_BIN)/src
	@$(CC) $(CFLAGS) $(INCLUDE_FLAGS) -c $< -o $@

$(DIR_BIN)/utils/%.o: $(DIR_UTILS)/%.c | $(DIR_BIN)/utils
	@$(CC) $(CFLAGS) $(INCLUDE_FLAGS) -c $< -o $@

$(DIR_BIN)/builtins/%.o: $(DIR_BUILTINS)/%.c | $(DIR_BIN)/builtins
	@$(CC) $(CFLAGS) $(INCLUDE_FLAGS) -c $< -o $@

$(DIR_BIN):
	@mkdir -p $@

$(DIR_BIN)/src:
	@mkdir -p $@

$(DIR_BIN)/utils:
	@mkdir -p $@

$(DIR_BIN)/builtins:
	@mkdir -p $@

#-----------------------clean functions------------------------#

clean:
	@make -s clean -C $(DIR_LIBFT)
	@rm -rf $(DIR_BIN)

fclean: clean
	@make -s fclean -C $(DIR_LIBFT)
	@rm -rf $(NAME)

re: fclean all

.PHONY: re clean fclean all