/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qsort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 05:53:45 by teando            #+#    #+#             */
/*   Updated: 2025/04/29 20:42:22 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_utils.h"
#include <stddef.h>

static void	qsort_swap(void *x, void *y, size_t size)
{
	unsigned char	temp;
	unsigned char	*a;
	unsigned char	*b;
	size_t			i;

	a = (unsigned char *)x;
	b = (unsigned char *)y;
	if (x == y)
		return ;
	i = 0;
	while (i < size)
	{
		temp = a[i];
		a[i] = b[i];
		b[i] = temp;
		i++;
	}
}

static void	*median_of_three(char *a, char *b, char *c, int (*cmp)(const void *,
			const void *))
{
	if (cmp(a, b) < 0)
	{
		if (cmp(b, c) < 0)
			return (b);
		if (cmp(a, c) < 0)
			return (c);
		return (a);
	}
	if (cmp(b, c) > 0)
		return (b);
	if (cmp(a, c) < 0)
		return (a);
	return (c);
}

static size_t	part_loop(char *base, size_t nmemb, size_t size,
		int (*cmp)(const void *, const void *))
{
	size_t	i;
	size_t	j;
	char	*pivot;

	pivot = base;
	i = 1;
	j = nmemb - 1;
	while (1)
	{
		while (i < nmemb && cmp(base + i * size, pivot) < 0)
			i++;
		while (j > 0 && cmp(base + j * size, pivot) > 0)
			j--;
		if (i >= j)
			break ;
		qsort_swap(base + i * size, base + j * size, size);
		i++;
		j--;
	}
	qsort_swap(base, base + j * size, size);
	return (j);
}

static size_t	partition(char *base, size_t nmemb, size_t size,
		int (*cmp)(const void *, const void *))
{
	char	*pivot;

	pivot = median_of_three(base, base + (nmemb / 2) * size, base + (nmemb - 1)
			* size, cmp);
	qsort_swap(base, pivot, size);
	return (part_loop(base, nmemb, size, cmp));
}

void	ft_qsort(void *base, size_t nmemb, size_t size, int (*cmp)(const void *,
			const void *))
{
	size_t	p;
	char	*arr;

	if (nmemb <= 1 || size == 0)
		return ;
	arr = (char *)base;
	p = partition(arr, nmemb, size, cmp);
	if (p > 0)
		ft_qsort(arr, p, size, cmp);
	ft_qsort(arr + (p + 1) * size, nmemb - p - 1, size, cmp);
}
