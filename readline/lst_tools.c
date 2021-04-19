#include "../minishell.h"

t_hst *get_new_node()
{
    t_hst *new_node = (t_hst *)malloc(sizeof(t_hst));
    new_node->next = NULL;
    new_node->size_bf = 2;
    new_node->curpos = 0;
    new_node->curr_buff = (char *)malloc(sizeof(char) * new_node->size_bf);
    new_node->old_buff = (char *)malloc(sizeof(char) * new_node->size_bf);
    new_node->prev = NULL;
    return(new_node);
}

void insert_at_head(t_rdl *rdl, t_hst *new_node)
{
    if (rdl->head == NULL)
    {
        rdl->head = new_node;
        return ;
    }
    rdl->head->prev = new_node;
    new_node->next = rdl->head;
    rdl->head = new_node;
}

void    insert_at_tail(t_rdl *rdl, t_hst *new_node)
{
    t_hst *tmp = rdl->head;
    if (rdl->head == NULL)
    {
        rdl->head = new_node;
        return ;
    }
    while (tmp->next)
    {
        tmp = tmp->next;
    }
    tmp->next = new_node;
    new_node->prev = tmp;
}

void   Print_doubly_lst(t_rdl *rdl)
{
    t_hst *tmp = rdl->head;
    ft_putendl_fd("-----Forward_D_lst-----\n", 1);
    while(tmp)
    {
        // printf("old_buff = <%s>\n",tmp->k, tmp->curpos, tmp->old_buff);
        printf("curps = %d, curr_buff = <%s>\n",tmp->curpos, tmp->curr_buff);
        tmp = tmp->next;
    }
    ft_putendl_fd("-----Forward_D_lst-----\n", 1);
}

void    Reverse_printf_doubly_lst(t_rdl *rdl)
{
    t_hst *tmp = rdl->head;
    if (tmp == NULL)
        return;
    while(tmp->next)
        tmp = tmp->next;
    ft_putendl_fd("-----Reverse_D_lst-----\n", 1);
    while(tmp)
    {
        printf("old_buff = <%s> curr_buff = <%s>\n", tmp->old_buff, tmp->curr_buff);
        tmp = tmp->next;
    }
    ft_putendl_fd("-----Reverse_D_lst-----\n", 1);
}