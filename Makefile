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
	LIBRARIES += -L/opt/homebrew/Cellar/readline/8.2.13
	INCLUDE_FLAGS += -I/opt/homebrew/Cellar/readline/8.2.13/include
endif

#---------------------VPATH------------------------#

vpath %.c $(DIR_SRC):$(DIR_SRC)/parsing
vpath %.c $(DIR_SRC):$(DIR_SRC)/execution
vpath %.c $(DIR_UTILS):$(DIR_UTILS)/extra
vpath %.c $(DIR_UTILS):$(DIR_UTILS)/ft_string_ptr
vpath %.c $(DIR_UTILS):$(DIR_UTILS)/libft

#---------------------SOURCE------------------------#s
SRCS				=	main.c \
						print.c \
						init_mini.c \
						errors.c \
						parsing.c \
						fill_cmd_struct.c \
						get_cmd_bin.c \
						get_cmd_args.c \
						get_cmd_type.c \
						get_cmd_redirection.c \
						quotes.c \
						dollar_handle.c \
						dollar_utils.c \
						wildcards_sub.c \
						wildcards_files.c \
						wildcards_affixes.c \
						wildcards_utils.c \
						wildcards_io.c \
						is_valid_redirections.c \
						is_valid_pipes.c \
						is_valid_backslash.c \
						ft_get_env.c \
						get_current_workdir.c \
						get_new_env_row.c \
						set_env.c \
						update_old_pwd_env.c \
						update_pwd_env.c \
						exec_mini.c \
						fd_backup_utils.c \
						file_redirections.c \
						pipeline.c \
						wait_for_children.c \
						minishell_exit.c

UTILS				=	contain_char.c \
						append_space_to_string.c \
						contain_quotes.c \
						contain_string_at_specific_index.c \
						enquote_str.c \
						epurstring.c \
						double_array_len.c \
						ft_strcmp_alpha.c \
						is_only_spaces.c \
						is_only_specific_char.c \
						is_quote.c \
						is_space.c \
						is_angle_bracket.c \
						is_valid_arithmetic_exit.c \
						join_n_strings.c\
						join_three_strings.c \
						print_error.c \
						start_with.c \
						sort_array.c \
						ft_atoi.c \
						ft_bzero.c \
						ft_isdigit.c \
						ft_calloc.c \
						ft_itoa.c \
						ft_memchr.c \
						ft_memcmp.c \
						ft_memcpy.c \
						ft_memmove.c \
						ft_memset.c \
						ft_putchar_fd.c \
						ft_putnbr_fd.c \
						ft_putstr_fd.c \
						ft_sized_strdup.c \
						ft_split.c \
						ft_strchr.c \
						ft_strcmp.c \
						ft_strdup.c \
						ft_strjoin.c \
						ft_strlcpy.c \
						ft_strlen.c \
						ft_strncmp.c \
						ft_strnstr.c \
						ft_strtrim.c \
						ft_substr.c \
						ft_toupper.c \
						ft_tolower.c \
						get_debug_fd.c \
						get_next_line.c \
						string_array_create_key.c \
						string_array_find_string.c \
						string_array_len.c \
						string_array_print.c \
						string_array_push.c \
						string_build.c 
						

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

INCLUDE_FLAGS		+=	-I$(DIR_INCLUDE)
LIBRARIES			+=	-lreadline

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

$(DIR_BIN)/utils/%.o: $(DIR_UTILS)/extra/%.c | $(DIR_BIN)/utils
	@$(CC) $(CFLAGS) $(INCLUDE_FLAGS) -c $< -o $@

$(DIR_BIN)/utils/%.o: $(DIR_UTILS)/ft_string_ptr/%.c | $(DIR_BIN)/utils
	@$(CC) $(CFLAGS) $(INCLUDE_FLAGS) -c $< -o $@

$(DIR_BIN)/utils/%.o: $(DIR_UTILS)/libft/%.c | $(DIR_BIN)/utils
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


#------------------------test---------------------------------#

SRC_WITHOUT_MAIN = $(filter-out $(DIR_BIN)/src/main.o, $(SRC_OBJ))

test: $(SRC_OBJ) $(UTILS_OBJ) $(BUILTINS_OBJ) | $(DIR_BIN)
	@$(CC) $(SRC_WITHOUT_MAIN) $(UTILS_OBJ) $(BUILTINS_OBJ) ./test_jojo/test.c $(CFLAGS) $(LIBRARIES) -o test.out
