/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarji <ymarji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 15:26:47 by ymarji            #+#    #+#             */
/*   Updated: 2021/04/19 11:35:30 by ymarji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/errno.h>
#include <string.h>
#include "./libft/libft.h"
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

typedef struct s_const
{
    int exit_stat;
    int pid;
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
    int status;
    t_node *node;
} t_var;

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
void ft_lstdelone_m(t_env *lst);
char *get_path(t_global *m_gl, char *cmd);
void export_main(t_global *m_gl, char **tab);
char **env_tab(t_global *m_gl);
void env_main(t_global *m_gl, char **tab);
int count_tab(char **tab);

void ft_deletenode(t_env **head_ref, t_env *del);
int unset(t_global *m_gl, char **tab);

void free_tab(char **tab);
int ident_val(char *str);

void print_err(char *str, char *arg, int errnb);
void change_value(char *ident, char *value);
int c_split(char const *str, char c);
void	piping(t_var *var);

void	pip_or_not(t_var *var);
// ---------------------------------- PARSE PART ------------------------------------------

void ft_initial();
void caracter(char c, int i);
int right_red(int i);
int left_red(int i);
int double_redr(int *i);
int pip(int i);
void semi_colone();
int behind_s_c(int i);
void double_quote(int i);
void simple_quote(int i);
void b_slash(int i);
void off_flags();
int char_off(int c);
int sum_flag();
void hundle_end();
int sum_all_flag();
void off_bs(int i);
t_var *get_struct_var(t_var *var);
char *get_v_dolar(char *v_dolar);

void divid_input();
void stock_cmd(char *str);
void print_tab2d(char **tab);

// void    search_file();
void get_file(int i, t_file *file);
void search_files(t_node *node);
void inverse(char *tab);
void inverse_args(char **tab);
void print_lst_files(t_node *node);
// void    get_file(int i);

// void ft_lstadd_back_m(t_env **alst, t_env *new);
// int ft_lstsize_m(t_env *lst);
// t_env *ft_lstnew_m(void *ident, void *value, char equal);
// t_env *ft_lstlast_m(t_env *lst);
// void ft_lstdelone_m(t_env *lst);
// void	free_tab(char **tab);
t_const con;

#endif