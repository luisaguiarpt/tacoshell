#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stddef.h>

void	*ft_realloc(void *ptr, size_t size);
void	*ft_memmove(void *dst, void *src, size_t n);
void	*ft_stradd(char *dst, const char *src);
void	*ft_calloc(size_t nmemb, size_t size);
size_t	ft_strlen(char *str);
void	*ft_memset(void *s, int c, size_t n);

//int	main(int ac, char **av)
//{
//	char	*line;
//	char	*buffer;
//	size_t	buf_size;
//	
//	buf_size = 0;
//	buffer = NULL;
//	while ((line = readline("$> ")) != NULL)
//	{
//		buf_size += ft_strlen(line);
//		buffer = ft_realloc(buffer, buf_size + 1);
//		buffer = ft_stradd(buffer, line);
//	}
//	printf("%s\n", buffer);
//}

// This function simulates realloc, but copies the existing memory to a new location
// with the new size
// @return: new -> the new pointer to the memory with the new size
// @input: pointer -> pointer to the buffer to copy
// @input: size -> size of the new allocated memory
void	*ft_realloc(void *ptr, size_t size)
{
	void	*new;

	// check if size is zero (same as a free)
	if (size == 0)
	{
		free (ptr);
		return (NULL);
	}
	// create the new buffer that will have the size size
	new = ft_calloc(sizeof(char), size);
	if (!new)
	{
		if (ptr)
			free(ptr);
		exit(EXIT_FAILURE);
	}
	if (ptr)
	{
		ft_memmove(new, ptr, ft_strlen((char *)ptr) + 1);
		free(ptr);
	}	
	return (new);
}

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i++] = (unsigned char)c;
	}
	return (s);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*ptr;

	ptr = malloc(size * nmemb);
	if (!ptr)
		return (NULL);
	ptr = ft_memset(ptr, 0, nmemb * size);
	return (ptr);
}

// This function adds n bytes from src to the end of dst
void	*ft_stradd(char *dst, const char *src)
{
	size_t	i;
	size_t	dst_n;

	if (src == NULL || dst == NULL)
		return (NULL);
	i = 0;
	dst_n = ft_strlen(dst);
	while (src[i])
	{
		dst[dst_n + i] = src[i];
		i++;
	}
	dst[dst_n + i] = 0;
	return (dst);
}

void	*ft_memmove(void *dst, void *src, size_t n)
{
	size_t	i;
	unsigned char	*uc_dst;
	unsigned char	*uc_src;

	uc_dst = (unsigned char *)dst;
	uc_src = (unsigned char *)src;
	if (n == 0 || src == NULL || dst == NULL)
		return (NULL);
	if (src == dst)
		return (dst);
	i = 0;
	while (src > dst && i < n)
	{
		uc_dst[i] = uc_src[i];
		i++;
	}
	while (src < dst && i < n)
	{
		uc_dst[n - i - 1] = uc_src[n - i - 1];
		i++;
	}
	return (dst);
}

size_t	ft_strlen(char *str)
{
	size_t	size;
	
	size = 0;
	if (str == NULL)
		return (0);
	while (str[size])
		size++;
	return (size);
}
