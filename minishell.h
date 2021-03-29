#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
# include "./libft/libft.h"


# define NEWLINE -101
# define UN_PIPE -102
# define UN_LR -103
# define UN_RR -104
# define UN_DR -105
# define UN_SC -106
# define UN_DSC -107
# define UN_DPIPE -108

typedef struct s_env
{
	char *ident;
	char *value;
	char equal;

	struct s_env *prev;
	struct s_env *next;
} t_env;

typedef struct s_file
{
    char       type;
    char       *name_file;
    struct s_file      *next;
}              t_file;

typedef struct s_node
{
    char    *cmd;
    char    **args;
    t_file  *file;
    struct s_node *link;
}              t_node;

typedef struct s_var
{
    t_env   *envar;
	char    *home;
    int     flag;
    int     flg_s_q;
    int     flg_d_q;
    int     flg_s_c;
    int     flg_p;
    int     errno;
    int     flg_d_r;
    int     flg_r_r;
    int     flg_l_r;
    int     flg_e_d;
    int     flg_d;
    int     flg_b_s;
    char    *input;
    char    *str;
    char    *tmp1;
    char    *tmp2;
    char    *tmp3;
    int     flagi;
    char    **sc_sp;
    t_node  *node;
}               t_var;


void    ft_initial();
void    caracter(char c, int i);
int    right_red(int i);
int    left_red(int i);
int    double_redr(int *i);
int    pip(int i);
void    semi_colone();
int     behind_s_c(int i);
void    double_quote(int i);
void    simple_quote(int i);
void    b_slash(int i);
void    off_flags();
int		char_off(int c);
int     sum_flag();
void    hundle_end();
int     sum_all_flag();
void    off_bs(int i);
t_var   *get_struct_var(t_var *var);


void    divid_input();
void    stock_cmd(char *str);
void    print_tab2d(char **tab);

// void    search_file();
void    get_file(int i, t_file *file);
void    search_files(t_node *node);
void    print_lst_files(t_node *node);
// void    get_file(int i);

void ft_lstadd_back_m(t_env **alst, t_env *new);
int ft_lstsize_m(t_env *lst);
t_env *ft_lstnew_m(void *ident, void *value, char equal);
t_env *ft_lstlast_m(t_env *lst);
void ft_lstdelone_m(t_env *lst);
void	free_tab(char **tab);
#endif
