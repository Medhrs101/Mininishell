NAME = minishell
LIB = minishell.a
MAIN = minishell.c
SRC = minishell_utils.c mns_utils_1.c divid_input.c \
	search_files.c ls_maker.c 

# MAIN = test.c
# SRC = minishell_utils.c

LIBFT = ./libft/libft.a

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME) : $(OBJ) 
	ar rcs $(LIB) $(OBJ)
	cd ./libft && make
	gcc $(FLAGS) $(MAIN) $(LIB) $(LIBFT) -o $(NAME)

%.o: %.c
	gcc $(FLAGS) -o $@ -c $<

clean:
	@cd ./libft && make -s fclean
	@rm -rf $(OBJ) $(LIB)

fclean: clean
	@rm -f $(NAME)

re: fclean all