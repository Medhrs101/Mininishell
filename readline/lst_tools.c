#include "../minishell.h"

t_hst *get_new_node()
{
    t_hst *new_node = (t_hst *)malloc(sizeof(t_hst));
    new_node->next = NULL;
    new_node->curpos = 0;
    new_node->curr_buff = (char *)malloc(sizeof(char) * 2);
    new_node->old_buff = (char *)malloc(sizeof(char) * 2);
    new_node->prev = NULL;
    return(new_node);
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
