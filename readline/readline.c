#include "../minishell.h"

void    init_term()
{
    char    *term_type;
    int     ret;

    term_type = getenv("TERM");
    if (term_type == NULL)
    {
        ft_putstr_fd ("TERM must be set (see 'env').\n", 1);
        exit (0);
    }
    ret = tgetent(NULL, term_type);
    if (ret == -1)
    {
        ft_putstr_fd("Could not access to the termcap database..\n", 1);
        exit (0);
    }
    else if (ret == 0)
    {
        ft_putstr_fd("Terminal type 'TERM' is not defined in termcap database (or have too few informations).\n", 1);
        exit (0);
    }
}

void    get_coord_cursor(t_rdl *rdl)
{
    int     i;
    char *buff;
    char    ch;

    buff = (char *)malloc(sizeof(char) * 20);
    i = 0;
    ch = 0;
    write(0, "\033[6n", 4);
    while(ch != 'R')
	{
	    read(0, &ch, 1);
	    buff[i] = ch;
        i++;
 	}
    i = 2;
    if (ft_isdigit(buff[i]))
        rdl->start.y = ft_atoi(&buff[i]);
    while (ft_isdigit(buff[i]))
        i++;
    rdl->start.x = ft_atoi(&buff[i + 1]);
    free(buff);
}

void    initial_terminal(struct termios *oldattr)
{
    struct termios attr;
    tcgetattr(0, oldattr);
    attr = *oldattr;
    attr.c_lflag &= ~(ECHO | ICANON | ISIG);
    tcsetattr(0, TCSANOW, &attr);
}

int is_key(int key_pressed)
{
	if (key_pressed == KEYCODE_R)
		return (0);
	else if (key_pressed == KEYCODE_L)
		return (0);
	else if (key_pressed == KEYCODE_HOME)
		return (0);
	else if (key_pressed == KEYCODE_END)
		return (0);
	else if (key_pressed == CTRL_L)
		return (0);
	else if (key_pressed == CTRL_U)
		return (0);
    return (1);
}


void    puts_c(t_hst *tmp)
{
    int i;
    
    i = 0;
    while(i < tmp->curpos && tmp->old_buff[i])
    {
        ft_putchar_fd(tmp->old_buff[i], 0);
        i++; 
    }
}
int ft_put(int c)
{
  return (write(0, &c, 1));
}
void    print_line(t_rdl *rdl, t_hst *tmp)
{
    tputs(tgoto(tgetstr("cm", NULL), rdl->start.x - 1, rdl->start.y - 1), 0, &ft_put);
    tputs(tgetstr("cd", NULL), 0, &ft_put);
    puts_c(tmp);
}

int     up_or_down(t_rdl *rdl, int pressed_key, t_hst **tmp)
{
    if (pressed_key != KEYCODE_U && pressed_key != KEYCODE_D)
        return (0);
    else if (pressed_key == KEYCODE_U)
    {
        if ((*tmp)->prev == NULL)
            return(0);
        *tmp = (*tmp)->prev;
        print_line(rdl, *tmp);
    }
    else if (pressed_key == KEYCODE_D)
    {
        if ((*tmp)->next == NULL)
            return(0);
       *tmp = (*tmp)->next;
        if((*tmp)->next == NULL)
        {
            free((*tmp)->curr_buff);
            (*tmp)->curr_buff = ft_strdup((*tmp)->old_buff);
        }
        print_line(rdl, *tmp);
    }
    return (1);
}

void    delete_char(t_hst *tmp)
{
    char *temp;

    ft_putstr_fd("\033[1D\033[K", 0);
    tmp->curpos--;
    tmp->old_buff[tmp->curpos] = 0;
    temp = ft_strdup(tmp->old_buff);
    free(tmp->old_buff);
    tmp->old_buff = temp;
}

char    *c_in_char(int c)
{
    char *str;

    if (!(str = (char *)malloc(2 * sizeof(char))))
	    return (NULL);
    str[0] = c;
    str[1] = '\0';
    return(str);
}

void    add_char(t_rdl *rdl, t_hst *tmp, int c)
{
    char *swap;

    tmp->curpos++;
    char *c_str = c_in_char(c);
    swap = ft_strjoin(tmp->old_buff, c_str);
    free(tmp->old_buff);
    tmp->old_buff = swap;
    free(c_str);
    print_line(rdl, tmp);
}


void    exchange_nodes(t_hst **tmp)
{
    int curpos = (*tmp)->curpos;
    char *old_buff = NULL;
    old_buff = ft_strdup((*tmp)->old_buff);
    free((*tmp)->old_buff);
    (*tmp)->old_buff = ft_strdup((*tmp)->curr_buff);
    (*tmp)->curpos = ft_strlen((*tmp)->old_buff);
    while((*tmp)->next)
        *tmp = (*tmp)->next;
    (*tmp)->curpos = curpos;
    free((*tmp)->old_buff);
    (*tmp)->old_buff = old_buff;
}

void delete_node(t_rdl *rdl, t_hst *tmp)
{
    free(tmp->curr_buff);
    free(tmp->old_buff);
    if (rdl->head == NULL || tmp == NULL)
        return;
    if (rdl->head == tmp)
        rdl->head = tmp->next;
    if (tmp->next != NULL)
        tmp->next->prev = tmp->prev;
    if (tmp->prev != NULL)
        tmp->prev->next = tmp->next;
    free(tmp);
    return;
}

void    delete_last_node(t_rdl *rdl, t_hst *temp)
{
    t_hst *tmp;
    
    tmp = rdl->head;
    tmp->curpos = 0;
    while(tmp->next)
        tmp = tmp->next;
    tmp->prev->next = temp->next;
    free(temp);
}

void   fill_file(int fd, t_rdl *rdl)
{
    t_hst *tmp;
    
    tmp = rdl->head;
    while(tmp)
    {
        ft_putendl_fd(tmp->curr_buff, fd);
        tmp = tmp->next;
    }
}

void swap_curr_old(t_hst **tmp)
{
    while((*tmp)->prev)
    {
        free((*tmp)->old_buff);
        (*tmp)->old_buff = ft_strdup((*tmp)->curr_buff);
        (*tmp)->curpos = ft_strlen((*tmp)->curr_buff);
        (*tmp) = (*tmp)->prev;
    }
    free((*tmp)->old_buff);
    (*tmp)->old_buff = ft_strdup((*tmp)->curr_buff);
    (*tmp)->curpos = ft_strlen((*tmp)->curr_buff);
    while((*tmp)->next)
        *tmp = (*tmp)->next;
}

int   hundle_ctrl_c_d(t_rdl *rdl, t_hst **tmp, int pressed_key)
{
    if ((*tmp)->next != NULL)
        exchange_nodes(tmp);
    delete_node(rdl, *tmp);
    ft_putchar_fd('\n', 0);
    if (pressed_key == CTRL_C)
        return(0);
    else
        exit(0);
    return(1);
}

int    hundle_back_n(t_rdl *rdl, t_hst **tmp, t_var *v)
{
    (*tmp)->old_buff[(*tmp)->curpos] = 0;
    if(!(*tmp)->old_buff[0])
    {
        exchange_nodes(tmp);
        delete_node(rdl, *tmp);
        ft_putchar_fd('\n', 0);
        return(0);
    }
    if ((*tmp)->next != NULL)
        exchange_nodes(tmp);
    free((*tmp)->curr_buff);
    (*tmp)->curr_buff = ft_strdup((*tmp)->old_buff);
    swap_curr_old(tmp);
    v->input = ft_strdup((*tmp)->curr_buff);
    ft_putchar_fd('\n', 0);
    return(0);
}

void    get_input(t_rdl *rdl, t_hst *tmp)
{
    t_var *v;
    
    v = get_struct_var(NULL);
    int pressed_key = 0;
    insert_at_tail(rdl, tmp);
    while (tmp->next)
        tmp = tmp->next;
    while(1)
    {
        pressed_key = 0;
        read(0, &pressed_key, 4);
        if (up_or_down(rdl, pressed_key, &tmp))
            continue;
        else if (ft_isprint(pressed_key))
            add_char(rdl, tmp, pressed_key);
        else if (pressed_key == CTRL_D && !tmp->curpos)
            hundle_ctrl_c_d(rdl, &tmp, pressed_key);
        else if (pressed_key == CTRL_C && !hundle_ctrl_c_d(rdl, &tmp, pressed_key))
            break;
        else if (pressed_key == 127 && tmp->old_buff[0])
            delete_char(tmp);
        else if (pressed_key == '\n' && !hundle_back_n(rdl, &tmp, v))
            break;
    }
}

void    ft_readline(t_rdl *rdl)
{
    t_hst *tmp = get_new_node();
    struct termios oldattr;
    initial_terminal(&oldattr);
    get_coord_cursor(rdl);
    get_input(rdl, tmp);
    tcsetattr(0, TCSANOW, &oldattr);
}