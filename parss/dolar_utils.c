#include "../minishell.h"

int	dolar_null_in_start(t_var *v, int j, t_hp *t)
{
	if (t->i == 0 && !v->sc_sp[j][t->i + ft_strlen(t->dolar) + 1])
	{
		free(t->dolar);
		v->tmp1 = ft_strdup("");
		free(v->sc_sp[j]);
		v->sc_sp[j] = v->tmp1;
		return (0);
	}
	return (1);
}
