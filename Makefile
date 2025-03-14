#--------------------TARGETS------------------------#

NAME = minishell

#------------------DIRECTORIES----------------------#

DIR_BIN			=	./bin
DIR_INCLUDE		=	./includes
DIR_SRC			=	./src
DIR_BUILTINS	=	./builtins
DIR_UTILS		=	./utils

#-----------------COMP FLAGS------------------------#

UNAME := $(shell uname)
CC		= gcc
CFLAGS	= -Wall -Werror -Wextra -g
ifeq ($(UNAME), Darwin)
CFLAGS += -g -fsanitize=address
endif

#---------------------VPATH------------------------#

vpath %.c $(DIR_SRC):$(DIR_SRC)/parsing
vpath %.c $(DIR_SRC):$(DIR_SRC)/execution

#---------------------SOURCE------------------------#

SRCS				=	main.c \
						print.c \
						init_mini.c \
						dollar_sign.c \
						fill_cmd_struct.c \
						get_cmd_args.c \
						get_cmd_bin.c \
						get_cmd_type.c \
						get_cmd_redirection.c \
						parsing.c \
						quotes.c \
						is_valid_redirections.c \
						is_valid_pipes.c \
						execute_command.c

UTILS				=	contain_char.c \
						contain_quotes.c \
						contain_string_at_specific_index.c \
						enquote_str.c \
						epurstring.c \
						is_only_spaces.c \
						is_quote.c \
						is_space.c \
						is_angle_bracket.c \
						ft_atoi.c \
						ft_calloc.c \
						ft_split.c \
						ft_strchr.c \
						ft_strdup.c \
						ft_strjoin.c \
						ft_strlen.c \
						ft_strncmp.c \
						ft_strnstr.c \
						ft_strtrim.c \
						ft_substr.c \
						get_next_line.c

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

INCLUDE_FLAGS		=	-I$(DIR_INCLUDE)
LIBRARIES			=	-lreadline

# For macOS, add readline paths if needed
ifeq ($(UNAME), Darwin)
LIBRARIES += -L/usr/local/opt/readline/lib
INCLUDE_FLAGS += -I/usr/local/opt/readline/include
endif

#---------------------TARGETS------------------------#

all:	$(NAME)

$(NAME): $(ALL_OBJ) | $(DIR_BIN)
	@$(CC) $(ALL_OBJ) $(CFLAGS) $(LIBRARIES) -o $@

$(DIR_BIN)/src/%.o: $(DIR_SRC)/parsing/%.c | $(DIR_BIN)/src
	@$(CC) $(CFLAGS) $(INCLUDE_FLAGS) -c $< -o $@

$(DIR_BIN)/src/%.o: $(DIR_SRC)/execution/%.c | $(DIR_BIN)/src
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
	@rm -rf $(DIR_BIN)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: re clean fclean all
