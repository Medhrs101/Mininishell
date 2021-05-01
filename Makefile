NAME = minishell
LIB = minishell.a
MAIN = minishell.c
SRC =./exec/echo_main.c \
	./exec/unset.c \
	./exec/pipe_handle.c \
	./exec/sig_handel.c \
	./exec/start.c \
	./exec/redirection.c \
	./exec/env_main.c \
	./exec/exec_cmd.c \
	./exec/export_main.c \
	./exec/ls_maker.c  \
	./exec/pwd_main.c \
	./exec/cd_main.c \
	./readline/lst_tools.c \
	./readline/readline_tools.c \
	./readline/delete_print.c \
	./readline/hundle_pressed_key.c \
	./readline/readline.c \
	./parss/divid_input.c \
	./parss/minishell_utils.c \
	./parss/mns_utils_1.c \
	./parss/search_files.c \
	./parss/redirections.c \
	./parss/pip_sc.c \
	./parss/parss_lst_utils.c \
	./parss/mns_utils_4.c \
	./parss/mns_utils_3.c \
	./parss/mns_utils_2.c \
	./parss/hundle_input.c \
	./parss/hundle_dolar.c
	
# MAIN = test.c
# SRC = minishell_utils.c

LIBFT = ./libft/libft.a

OBJ = $(SRC:.c=.o)

# FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME) : $(OBJ) 
	ar rcs $(LIB) $(OBJ)
	cd ./libft && make
	gcc -lncurses $(FLAGS) $(MAIN) $(LIB) $(LIBFT) -o $(NAME)
	# ./minishell

%.o: %.c
	gcc $(FLAGS) -o $@ -c $<

clean:
	@cd ./libft && make -s fclean
	@rm -rf $(OBJ) $(LIB)

fclean: clean
	@rm -f $(NAME)

re: fclean all