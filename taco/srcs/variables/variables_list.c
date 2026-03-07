#include "../../incs/minishell.h"

void	append_shell_var(t_variable **head, t_variable *new)
{
	t_variable	*tmp;

	tmp = *head;
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
