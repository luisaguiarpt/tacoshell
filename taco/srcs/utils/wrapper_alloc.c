/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper_alloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 15:09:51 by josepedr          #+#    #+#             */
/*   Updated: 2026/03/09 15:09:55 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

/*
static void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		((unsigned char *)s)[i++] = (unsigned char)c;
	return (s);
}

static void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*ptr;

	if (nmemb == 0 || size == 0)
		return (NULL);
	if (nmemb > SIZE_MAX / size)
		return (NULL);
	ptr = malloc(size * nmemb);
	if (!ptr)
		return (NULL);
	ptr = ft_memset(ptr, 0, nmemb * size);
	return (ptr);
}
*/

void	*wr_calloc(size_t nmemb, size_t size, t_shell *shell)
{
	void	*ptr;

	ptr = ft_calloc(nmemb, size);
	if (!ptr)
	{
		shell->exit_status = ENOMEM;
		exit_clean(shell, EXIT_FAILURE);
	}
	return (ptr);
}
