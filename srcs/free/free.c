#include "../headers/tacoshell.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array[i]);
	free(array);
}

void	full_free(t_core *core)
{
	free_core(core);
}

void	*free_mem_arr(char **arr, int index)
{
	int i;

	i = 0;
	if (!arr)
		return (NULL);
	while (i < index)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

void	free_tokens(t_token *head)
{
    t_token *next;

    while (head)
    {
        next = head->next;
        free(head);
        head = next;
    }
}
