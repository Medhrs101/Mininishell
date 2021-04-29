/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarji <ymarji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 15:26:47 by ymarji            #+#    #+#             */
/*   Updated: 2021/04/29 14:20:41 by ymarji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <limits.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/errno.h>
#include <string.h>
#include "./libft/libft.h"

#include <termcap.h>
// #include <term.h>
#include <termios.h>
#include <curses.h>

# define KEY_DEL 0x7E335B1B

#define KEYCODE_R 0x435b1b // Left Arrow Key
#define KEYCODE_L 0x445b1b // Right Arrow Key
#define KEYCODE_U 0x415b1b // Up Arrow Key
#define KEYCODE_D 0x425b1b // Down Arrow Key
#define KEYCODE_HOME 0x485b1b
#define KEYCODE_END 0x465b1b
// #define KEYCODE_DEL 0x7e335b1b
// #define KEYCODE_DEL "\x1b\x5b\x33\x7e"

// #define KEYCODE_Q 0x71 // Q Key

#define CTRL_U 0x15
#define CTRL_L 0xc
#define CTRL_D 0x4
#define CTRL_C 0x3

#define STDIN  0
#define STDOUT 1
#define STDERR 2
#define ENVI 5544
#define EXPRT 5545
#define NEWLINE -101
#define UN_PIPE -102
#define UN_LR -103
#define UN_RR -104
#define UN_DR -105
#define UN_SC -106
#define UN_DSC -107
#define UN_DPIPE -108


typedef struct s_hundle_input
{
    int     i;
    int     s;
    int     d;
    int     r;
    int     bs_erno;
    int     end;
    char    *dolar;
    char    *v_dolar; 
    char    *tmp1;
    char    *tmp2;
    char    *tmp3;  
}              t_hp;

typedef struct s_hst
{
    char *old_buff;
    char *curr_buff;
    int curpos;
    struct s_hst   *prev;
    struct s_hst   *next;
}              t_hst;

typedef struct s_coord
{
    int x;
    int y;
}              t_coord;

typedef struct  s_rdl
{
    t_hst   *head;
    t_coord start;
    t_coord size_win;
    size_t  curpos;
    
}               t_rdl;

typedef struct s_const
{
    int     exit_stat;
    pid_t   pid;
} t_const;

typedef struct s_env
{
    char *ident;
    char *value;
    char equal;

    struct s_env *prev;
    struct s_env *next;
} t_env;

typedef struct s_global
{
    t_env *envar;
    char *home;
    int pid;
    int exit_stat;
    int stdi;
    int stdo;
} t_global;

typedef struct s_file
{
    char type;
    char *name_file;
    struct s_file *next;
} t_file;

typedef struct s_node
{
    char *cmd;
    char **args;
    t_file *file;
    struct s_node *link;
} t_node;

typedef struct s_var
{
    // t_env   *envar;
    t_global *m_gl;
    char *home;
    int shlvl;
    int stdo;
    int stdi;
    int out_fd;
    int in_fd;
    int app_fd;
    int flag;
    int flg_s_q;
    int flg_d_q;
    int flg_s_c;
    int flg_p;
    int erno;
    int flg_d_r;
    int flg_r_r;
    int flg_l_r;
    int flg_e_d;
    int flg_d;
    int flg_b_s;
    char *input;
    char *str;
    char *tmp1;
    char *tmp2;
    char *tmp3;
    int flagi;
    char **sc_sp;
    char **p_sp;
    char *val;
    t_node *node;
} t_var;

//readline
void    init_term();
void    initial_terminal(struct termios *oldattr);
void    print_prompt();
void    ft_readline(t_rdl * rdl);
char    *c_in_char(int c);
void    add_char(t_rdl *rdl, t_hst *tmp, int c);
int     hundle_back_n(t_rdl *rdl, t_hst **tmp, t_var *v);
int     hundle_ctrl_c_d(t_rdl *rdl, t_hst **tmp, int pressed_key);
int     up_or_down(t_rdl *rdl, int pressed_key, t_hst **tmp);
void    puts_c(t_hst *tmp);
int     ft_put(int c);
void    print_line(t_rdl *rdl, t_hst *tmp);
void    delete_char(t_hst *tmp);
void    init_term();
void    exchange_nodes(t_hst **tmp);
void    delete_node(t_rdl *rdl, t_hst *tmp);
void    swap_curr_old(t_hst **tmp);
t_hst   *get_new_node();
void    insert_at_head(t_rdl *rdl, t_hst *new_node);
void    insert_at_tail(t_rdl *rdl, t_hst *new_node);
// void    Print_doubly_lst(t_rdl *rdl);
// void    Reverse_printf_doubly_lst(t_rdl *rdl);

//////

// void execute(t_global *m_gl, char *line);
void execute(t_global *m_gl, t_node *node);
void init(t_global *m_gl);
void modify_path(t_env *env_l);
void env_copy(t_global *m_gl, char **env_t);
// int check_built(t_global *m_gl, char **cmd);
int check_built(t_global *m_gl, t_node *node);
int ft_strcmp(const char *s1, const char *s2);
void exec_main(t_global *m_gl, t_node *node);
void echo_main(t_global *m_gl, char **tab);
void cd_main(t_global *m_gl, char **tab);
int check_opt_echo(char **tab);
int ls(void);
void pwd_main(t_global *m_gl, char **tab);
// int out_red(t_var *var);
int	 out_red(t_var	*var, t_node *node);
void ft_lstadd_back_m(t_env **alst, t_env *new);
int ft_lstsize_m(t_env *lst);
// t_env *ft_lstnew_m(void *content, int type);
t_env *ft_lstnew_m(void *ident, void *value, char equal);
t_env *ft_lstlast_m(t_env *lst);
char *get_path(t_global *m_gl, char *cmd);
void export_main(t_global *m_gl, char **tab);
char **env_tab(t_global *m_gl);
void env_main(t_global *m_gl, char **tab);
int count_tab(char **tab);

void ft_deletenode(t_env **head_ref, t_env *del);
int unset(t_global *m_gl, char **tab);


int ident_val(char *str);

void print_err(char *str, char *arg, int errnb);
void change_value(char *ident, char *value);
int c_split(char const *str, char c);
void	piping(t_var *var);

void	pip_or_not(t_var *var);

void	handle_sigint(int sig);
void	handle_sigquit(int sig);

// ---------------------------------- PARSE PART ------------------------------------------

void free_tab(char **tab);
void hundle_syntax(t_var *var, int *i);
int check_line();


int print_error(int erno);
void print_tab2d(char **tab);
void hundle_end();
void double_quote(int i);
void simple_quote(int i);


void ft_initial();
int sum_all_flag();
int sum_flag();
int char_off(int c);
void off_flags();

t_var *get_struct_var(t_var *var);
void off_bs(int i);
void caracter(char c, int i);
void    hp_initial(t_hp *t);
int     is_red(int c);

int right_red(int i);
int left_red(int i);
int double_redr(int *i);

int behind_s_c(int i);
void semi_colone();
int pip(int i);
void b_slash(int i);

void v_dolar_not_null(t_var *v, int j, t_hp *t);
void v_dolar_null(t_var *v, int j, t_hp *t);
int     end_dolar(char *tb, int i);
void     dolar_hundle(int j, t_hp *t);
int    dolar_work(char *tb, t_hp *t);

void    bs_hundle(char *tb, t_hp *t);
int     bs_work(char *tb, t_hp *t);
void    hundle_s_d(t_var *v, int j, t_hp *t);
int    hundle_input(int j, t_var *v);

int     is_redirection(int c, int d, t_hp *t);
void    inverse_input(int i);
void    override(char *tb, int i);
int		isdigit(int c);
int     ft_argchr(char *str);

void    inverse_args(char **tb);
char    *get_v_dolar(char *v_dolar);
void    inverse_file(char *tab);
char   *inverse_dolar(char *dolar);


char *get_v_dolar(char *v_dolar);
void divid_input();
void stock_cmd(char *str, t_var *v);

void    join_cmd_list(t_node *node);
void    print_lst();
t_node    *create_node(t_node *node);
void    clear_lst_files(t_node *node);
void    clear_lst_cmd_args();

// void    search_file();
void get_file(t_var *v, int i, t_file *file);
void search_files(t_node *node);
void inverse(char *tab);
void print_lst_files(t_node *node);
// void    get_file(int i);

// void ft_lstadd_back_m(t_env **alst, t_env *new);
// int ft_lstsize_m(t_env *lst);
// t_env *ft_lstnew_m(void *ident, void *value, char equal);
// t_env *ft_lstlast_m(t_env *lst);
// void ft_lstdelone_m(t_env *lst);
t_const con;

#endif